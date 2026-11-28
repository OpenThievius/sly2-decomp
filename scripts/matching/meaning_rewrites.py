#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""meaning_rewrites.py - rewrites of a near miss that keep what the function computes, for tsearch.py and sitesearch.py.

  python3 scripts/matching/meaning_rewrites.py SOURCE [--only NAME,...]     prints every rewrite's label and its diff
  python3 scripts/matching/meaning_rewrites.py --list                       the rewrites and what each does

mutate.py and rules.py hold the rewrites our searches already had. sly1-decomp's tools/tsearch.py (AGPL-3.0, read for its ideas only;
nothing here is its code) has a larger library; these are the ones ours lacked (docs/contributing/search-tools.md has the inventory).
Each rewrite reads the function with source_tree.py and refuses itself where it cannot show that the meaning is kept: it never moves a
statement past one that reads what it writes (or writes what it reads), never reorders memory accesses across a store or a call, never
duplicates a side effect, and changes no expression's value order beyond swapping the two operands of one commutative operator (exact in
IEEE arithmetic; the PS2's FPU has no NaN, which the negated-comparison forms rely on). Every rewrite is a function `name(source)` that
returns [(label, [(start, end, replacement)])], edits in character offsets of the source text."""
import argparse
import difflib
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from source_tree import (COMMUTATIVE, ParseError, Source, apply_edits, normalized, parenthesize, strip_parentheses,  # noqa: E402
                         BINARY_PRECEDENCE, PROJECT_TYPES, TYPE_KEYWORDS)

MOVE_DISTANCE = 4          # how far move_statement carries a statement up or down its block
FLIPPED = {'<': '>', '>': '<', '<=': '>=', '>=': '<=', '==': '==', '!=': '!='}
NEGATED = {'<': '>=', '>=': '<', '>': '<=', '<=': '>', '==': '!=', '!=': '=='}
FLOAT_WORDS = ('float', 'double', 'f32', 'f64')
BOOLEAN_OPERATORS = {'<', '>', '<=', '>=', '==', '!=', '&&', '||'}


# --- helpers shared by the rewrites

def line_text(source, statement):
    """(start, end, text) of the whole lines of a statement, or None when it shares a line."""
    span = source.line_span(statement)
    return (span[0], span[1], source.text[span[0]:span[1]]) if span else None


def reindent(text, old, new):
    return '\n'.join(new + line[len(old):] if line.startswith(old) else line for line in text.split('\n'))


def declaration(type_text, name, value=None):
    """`T name = value;` written the way our sources write it (`T *name`, not `T * name`)."""
    type_text = re.sub(r'\s*\*\s*', '*', type_text).replace('*', ' *').replace(' * *', ' **').strip()
    type_text = re.sub(r' \*( \*)+', lambda match: ' ' + '*' * (match.group().count('*')), type_text)
    joined = f'{type_text}{name}' if type_text.endswith('*') else f'{type_text} {name}'
    return f'{joined} = {value};' if value is not None else f'{joined};'


def unit_indent(source):
    """The indentation step of the function (four spaces unless its first statement says otherwise)."""
    statements = source.body.parts['statements']
    if statements:
        indent = source.indent_of(statements[0])
        if indent:
            return indent
    return '    '


def arm_statements(arm):
    return arm.parts['statements'] if arm.kind == 'block' else [arm]


def has_side_effect(source, node):
    effects = source.node_effects(node)
    return effects.side_effect


def is_pure(source, node):
    """No call, no write: evaluating it again or earlier changes nothing by itself."""
    return node is not None and not has_side_effect(source, node)


def escapes(source, statement, inside_loop=False, inside_switch=False):
    """True when a statement can leave by return, goto or a label, or by a break or continue that is not caught inside it."""
    kind = statement.kind
    if kind in ('return', 'goto', 'label'):
        return True
    if kind == 'break' and not (inside_loop or inside_switch):
        return True
    if kind == 'continue' and not inside_loop:
        return True
    loop = inside_loop or kind in ('while', 'do', 'for')
    switch = inside_switch or kind == 'switch'
    return any(escapes(source, child, loop, switch) for child in statement.children())


def holds_case_label(statement):
    return any(child.kind == 'case' for child in statement.walk() if child is not statement) and statement.kind != 'switch'


def has_labels(source):
    """True when the function holds a label: a goto can enter a block from outside, so the rewrites that regroup statements (arms, cases,
    loop bodies) refuse themselves there instead of reasoning about every path."""
    return any(statement.kind == 'label' for statement in source.body.walk())


def fresh_name(source, base):
    used = {token.text for token in source.tokens if token.kind == 'identifier'}
    if base not in used:
        return base
    number = 2
    while f'{base}{number}' in used:
        number += 1
    return f'{base}{number}'


def ends_in_exit(statement):
    """The statement always leaves: its last statement is a return, break, continue or goto."""
    if statement.kind == 'block':
        items = statement.parts['statements']
        return bool(items) and ends_in_exit(items[-1])
    if statement.kind == 'if' and statement.parts['otherwise'] is not None:
        return ends_in_exit(statement.parts['then']) and ends_in_exit(statement.parts['otherwise'])
    return statement.kind in ('return', 'break', 'continue', 'goto')


def statements_text(source, statements, indent):
    """The statements' text, one per line, each re-indented to `indent`."""
    return '\n'.join(indent + reindent(source.source_of(item), source.indent_of(item), indent).lstrip() for item in statements)


def value_kind(source, node):
    """'float', 'integer' or None (unknown) for a value: the conversions of a ternary must not differ from those of two assignments."""
    node = strip_parentheses(node)
    if node.kind == 'number':
        text = node.operator.lower()
        return 'float' if ('.' in text or text.endswith('f')) and not text.startswith('0x') else 'integer'
    if node.kind == 'name':
        declared = source.type_of_local(node.operator)
        if declared:
            if '*' in declared:
                return 'pointer'
            return 'float' if any(word in declared for word in FLOAT_WORDS) else 'integer'
    if node.kind == 'cast':
        return 'float' if any(word in node.operator for word in FLOAT_WORDS) else ('pointer' if '*' in node.operator else 'integer')
    if node.kind == 'unary' and node.operator == '-':
        return value_kind(source, node.children[0])
    return None


def same_kind(source, first, second):
    first_kind, second_kind = value_kind(source, first), value_kind(source, second)
    return first_kind == second_kind


def assignment_of(statement, operator='='):
    """(target node, value node) of an expression statement `target = value;`, else None."""
    if statement is None or statement.kind != 'expression':
        return None
    node = strip_parentheses(statement.parts['expression'])
    if node.kind == 'assign' and node.operator == operator:
        return node.children[0], node.children[1]
    return None


def single(arm):
    """The one statement of an arm (a bare statement or a block of one), else None."""
    items = arm_statements(arm)
    return items[0] if len(items) == 1 else None


def is_simple_lvalue(source, node):
    """A name, or members and indexes of names and literals: no call, no write, safe to evaluate twice."""
    node = strip_parentheses(node)
    if node.kind == 'name':
        return True
    if node.kind == 'member':
        return is_simple_lvalue(source, node.children[0])
    if node.kind == 'index':
        return is_simple_lvalue(source, node.children[0]) and strip_parentheses(node.children[1]).kind in ('name', 'number')
    if node.kind == 'unary' and node.operator == '*':
        return is_simple_lvalue(source, node.children[0])
    return False


def reads_target(source, node, target):
    """True when `node` may read the place `target` names."""
    effects = source.node_effects(node)
    target = strip_parentheses(target)
    if target.kind == 'name' and source.tracked(target.operator):
        return target.operator in effects.reads
    return effects.memory_read or effects.call or bool(source.node_effects(target).reads & effects.writes)


def flip_comparison(source, node):
    """`a < b` written `b > a` (the same test), or None."""
    node = strip_parentheses(node)
    if node.kind == 'binary' and node.operator in FLIPPED and node.operator not in ('==', '!='):
        left, right = node.children
        return f'{operand_text(source, right, node.operator)} {FLIPPED[node.operator]} {operand_text(source, left, node.operator)}'
    return None


def negation(source, node):
    """The negated test as text: a comparison with the opposite operator (exact on the PS2, which has no NaN), else `!(...)`."""
    node = strip_parentheses(node)
    if node.kind == 'binary' and node.operator in NEGATED:
        left, right = node.children
        return f'{source.source_of(left)} {NEGATED[node.operator]} {source.source_of(right)}'
    if node.kind == 'unary' and node.operator == '!':
        return source.source_of(strip_parentheses(node.children[0]))
    return f'!{parenthesize(source, node)}'


def operand_text(source, node, operator):
    """An operand's text for a binary operator, in parentheses where precedence needs them."""
    text = source.source_of(node)
    inner = strip_parentheses(node)
    if node.kind == 'paren':
        return text
    if inner.kind in ('assign', 'ternary', 'comma') or (inner.kind == 'binary' and BINARY_PRECEDENCE[inner.operator] <= BINARY_PRECEDENCE[operator]):
        return f'({text})'
    return text


def element_type(source, name):
    """The element type of an array or pointer named `name` (a local, a parameter or an extern of the file), or None."""
    declared = source.type_of_local(name)
    if declared is not None:
        if name in source.declarations and source.declarations[name][1].dimensions:
            return declared
        if declared.endswith('*'):
            return declared[:-1].strip()
        return None
    match = re.search(rf'\bextern\s+(?:"C"\s+)?([\w\s\*]+?)\s*\b{re.escape(name)}\s*\[', source.text)
    if match:
        return re.sub(r'\bconst\b\s*', '', match.group(1)).strip() or None
    return None


def struct_fields(source):
    """{struct name: {field: type}} of the structs and classes the source defines itself (one declarator per line)."""
    if hasattr(source, '_struct_fields'):
        return source._struct_fields
    found = {}
    for match in re.finditer(r'\b(?:struct|class|union)\s+(\w+)\s*(?::[^{;]*)?\{', source.text):
        start = match.end()
        depth, index = 1, start
        while index < len(source.text) and depth:
            depth += {'{': 1, '}': -1}.get(source.text[index], 0)
            index += 1
        fields = {}
        for line in re.sub(r'//[^\n]*|/\*.*?\*/', '', source.text[start:index - 1], flags=re.S).split(';'):
            field = re.match(r'\s*((?:const\s+|unsigned\s+|signed\s+|struct\s+)*\w+(?:\s*\*+)?)\s*(\**)\s*(\w+)\s*$', line)
            if field and field.group(1) not in ('return', 'virtual'):
                fields[field.group(3)] = (field.group(1) + field.group(2)).strip()
        found[match.group(1)] = fields
    source._struct_fields = found
    return found


def expression_type(source, node):
    """The type of a value as text when the source shows it (a cast, a local, a member of a struct the file defines), else None."""
    node = strip_parentheses(node)
    if node.kind == 'cast':
        return node.operator.strip()
    if node.kind == 'name':
        return source.type_of_local(node.operator)
    if node.kind == 'unary' and node.operator == '*':
        inner = expression_type(source, node.children[0])
        return inner[:-1].strip() if inner and inner.endswith('*') else None
    if node.kind == 'index':
        base = strip_parentheses(node.children[0])
        if base.kind == 'name':
            return element_type(source, base.operator)
        inner = expression_type(source, base)
        return inner[:-1].strip() if inner and inner.endswith('*') else None
    if node.kind == 'member':
        base_type = expression_type(source, node.children[0])
        if not base_type:
            return None
        base_type = re.sub(r'\b(const|struct|class|union)\b', '', base_type).strip()
        if node.operator == '->':
            if not base_type.endswith('*'):
                return None
            base_type = base_type[:-1].strip()
        fields = struct_fields(source).get(base_type)
        return fields.get(node.children[1].operator) if fields else None
    return None


def plain_scalar_type(type_text):
    """True for a type that a declaration can split from its initialiser without a constructor: a builtin, a project integer, a pointer."""
    if not type_text or '&' in type_text or re.search(r'\bconst\b', type_text):
        return False
    if type_text.endswith('*'):
        return True
    words = re.sub(r'\b(static|register)\b', '', type_text).split()
    return bool(words) and all(word in TYPE_KEYWORDS or word in PROJECT_TYPES - {'QW'} for word in words)


# --- the rewrites

def move_statement(source):
    """A statement moved up or down its block past statements it does not depend on (at most MOVE_DISTANCE places): neither reads what the
    other writes, and no two of them touch memory where one writes it. Sly 1 toolchain notes: docs/toolchain/sched1.md (the order of
    independent statements decides sched1's ties)."""
    found = []
    for block in source.blocks():
        items = block.parts['statements']
        effects = [source.effects(item) for item in items]
        for position, item in enumerate(items):
            lines = line_text(source, item)
            if not lines or effects[position].control or item.kind in ('case', 'label', 'empty'):
                continue
            for direction in (-1, 1):
                other = position + direction
                while 0 <= other < len(items) and abs(other - position) <= MOVE_DISTANCE:
                    if effects[other].control or effects[position].conflicts(effects[other]) or items[other].kind == 'case':
                        break
                    target = line_text(source, items[other])
                    if not target:
                        break
                    insert_at = target[0] if direction < 0 else target[1]
                    found.append((f'move_statement@{source.line_number(lines[0])} {"up" if direction < 0 else "down"} {abs(other - position)}',
                                  [(lines[0], lines[1], ''), (insert_at, insert_at, lines[2])]))
                    other += direction
    return found


def no_continue(source, body):
    return not any(item.kind == 'continue' for item in loop_level_statements(body))


def loop_level_statements(statement):
    """The statements of a loop body that belong to that loop (not to an inner loop)."""
    yield statement
    for child in statement.children():
        if child.kind not in ('while', 'do', 'for'):
            yield from loop_level_statements(child)


def loop_forms(source):
    """`while (c)` against `for (; c;)`; `x = a; while (c) { ...; step; }` against `for (x = a; c; step)` (no continue in the body: a
    while's continue skips the step a for runs); a for loop whose first test is known true (constant bounds) as `init; do { ... step; }
    while (c);`. Sly 1 toolchain notes: docs/toolchain/loops.md (the loop notes and the rotated loop)."""
    if has_labels(source):
        return []
    found = []
    parents = source.parent_map()
    for statement in source.body.walk():
        if statement.kind == 'while':
            condition = source.source_of(statement.parts['condition'])
            closer = statement.parts['condition'].last + 1
            found.append((f'loop_forms@{line_of(source, statement)} while as for', [(source.tokens[statement.first].start, source.tokens[closer].end, f'for (; {condition};)')]))
            parent = parents.get(id(statement))
            body = statement.parts['body']
            if parent and parent[0].kind == 'block' and parent[1] > 0 and body.kind == 'block' and body.parts['statements'] and no_continue(source, body):
                before = parent[0].parts['statements'][parent[1] - 1]
                initial = assignment_of(before)
                last = body.parts['statements'][-1]
                step = last.parts.get('expression') if last.kind == 'expression' else None
                if initial and step is not None and strip_parentheses(initial[0]).kind == 'name' and line_text(source, before) and line_text(source, last):
                    name = strip_parentheses(initial[0]).operator
                    step_effects = source.node_effects(step)
                    if step_effects.writes == {name} and not step_effects.memory_write and not step_effects.call:
                        start = line_text(source, before)
                        header = f'for ({source.source_of(before.parts["expression"])}; {condition}; {source.source_of(step)})'
                        found.append((f'loop_forms@{line_of(source, statement)} while with init and step as for',
                                      [(start[0], start[1], ''), (source.tokens[statement.first].start, source.tokens[closer].end, header),
                                       (line_text(source, last)[0], line_text(source, last)[1], '')]))
        if statement.kind == 'for':
            init, condition, step, body = (statement.parts[key] for key in ('init', 'condition', 'step', 'body'))
            closer = source.matching(statement.first + 1)
            if init is None and step is None and condition is not None:
                found.append((f'loop_forms@{line_of(source, statement)} for as while', [(source.tokens[statement.first].start, source.tokens[closer].end, f'while ({source.source_of(condition)})')]))
            if init is not None and init.kind == 'expression' and condition is not None and step is not None and body.kind == 'block' and no_continue(source, body):
                if known_true_at_entry(source, init, condition):
                    indent = source.indent_of(statement)
                    step_text = unit_indent(source)
                    inner = statements_text(source, body.parts['statements'], indent + step_text)
                    text = (f'{source.source_of(init)}\n{indent}do {{\n' + (inner + '\n' if inner else '') + f'{indent}{step_text}{source.source_of(step)};\n'
                            f'{indent}}} while ({source.source_of(condition)});')
                    found.append((f'loop_forms@{line_of(source, statement)} for with a known first test as do-while', [(source.tokens[statement.first].start, source.tokens[statement.last].end, text)]))
    return found


def line_of(source, item):
    return source.line_number(source.tokens[item.first].start)


def literal_value(node):
    node = strip_parentheses(node)
    negative = False
    if node.kind == 'unary' and node.operator == '-':
        negative, node = True, strip_parentheses(node.children[0])
    if node.kind != 'number':
        return None
    try:
        value = int(node.operator.rstrip('uUlL'), 0)
    except ValueError:
        return None
    return -value if negative else value


def known_true_at_entry(source, init, condition):
    """`i = A; i < B` with literal A and B whose test holds the first time."""
    assignment = assignment_of(init)
    if not assignment or strip_parentheses(assignment[0]).kind != 'name':
        return False
    start = literal_value(assignment[1])
    node = strip_parentheses(condition)
    if start is None or node.kind != 'binary' or node.operator not in ('<', '<=', '>', '>=', '!='):
        return False
    left, right = (strip_parentheses(child) for child in node.children)
    name = strip_parentheses(assignment[0]).operator
    if left.kind == 'name' and left.operator == name:
        bound = literal_value(right)
        operator = node.operator
    elif right.kind == 'name' and right.operator == name:
        bound = literal_value(left)
        operator = FLIPPED[node.operator]
    else:
        return False
    if bound is None:
        return False
    return {'<': start < bound, '<=': start <= bound, '>': start > bound, '>=': start >= bound, '!=': start != bound}[operator]


def ternary_assignment(source):
    """`if (c) x = a; else x = b;` against `x = c ? a : b;`; `x = a; if (c) x = b;` against `x = c ? b : a;` (a and c without side
    effects, c not reading x); `if (c) return a; return b;` against `return c ? a : b;`. Only where a and b are values of one kind (two
    integers or two floats), so the ternary's conversions are the assignments'. Sly 1 toolchain notes: docs/toolchain/jump.md (if-conversion
    and the movz/movn forms)."""
    found = []
    parents = source.parent_map()
    for statement in source.body.walk():
        if statement.kind == 'if':
            condition = statement.parts['condition']
            then, otherwise = statement.parts['then'], statement.parts['otherwise']
            first = assignment_of(single(then)) if single(then) else None
            if otherwise is not None and first:
                second = assignment_of(single(otherwise)) if single(otherwise) else None
                if second and normalized(source.source_of(first[0])) == normalized(source.source_of(second[0])) and is_simple_lvalue(source, first[0]) \
                        and same_kind(source, first[1], second[1]):
                    text = f'{source.source_of(first[0])} = {parenthesize(source, condition)} ? {source.source_of(first[1])} : {source.source_of(second[1])};'
                    found.append((f'ternary_assignment@{line_of(source, statement)} if/else as ternary', [(*source.span(statement), text)]))
            parent = parents.get(id(statement))
            if otherwise is None and first and parent and parent[0].kind == 'block' and parent[1] > 0:
                before = parent[0].parts['statements'][parent[1] - 1]
                initial = assignment_of(before)
                if initial and normalized(source.source_of(initial[0])) == normalized(source.source_of(first[0])) and is_simple_lvalue(source, first[0]) \
                        and is_pure(source, initial[1]) and is_pure(source, condition) and not reads_target(source, condition, first[0]) \
                        and same_kind(source, first[1], initial[1]):
                    text = f'{source.source_of(first[0])} = {parenthesize(source, condition)} ? {source.source_of(first[1])} : {source.source_of(initial[1])};'
                    start = source.span(before)[0]
                    found.append((f'ternary_assignment@{line_of(source, statement)} store and conditional store as ternary', [(start, source.span(statement)[1], text)]))
            single_then = single(then)
            if otherwise is None and single_then is not None and single_then.kind == 'return' and single_then.parts['value'] is not None and parent and parent[0].kind == 'block':
                items = parent[0].parts['statements']
                following = items[parent[1] + 1] if parent[1] + 1 < len(items) else None
                if following is not None and following.kind == 'return' and following.parts['value'] is not None and same_kind(source, single_then.parts['value'], following.parts['value']):
                    text = f'return {parenthesize(source, condition)} ? {source.source_of(single_then.parts["value"])} : {source.source_of(following.parts["value"])};'
                    found.append((f'ternary_assignment@{line_of(source, statement)} two returns as a ternary', [(source.span(statement)[0], source.span(following)[1], text)]))
        if statement.kind in ('expression', 'return'):
            node = statement.parts.get('expression') if statement.kind == 'expression' else statement.parts.get('value')
            if node is None:
                continue
            node = strip_parentheses(node)
            indent = source.indent_of(statement)
            step = unit_indent(source)
            if statement.kind == 'expression' and node.kind == 'assign' and node.operator == '=' and strip_parentheses(node.children[1]).kind == 'ternary' and is_simple_lvalue(source, node.children[0]):
                ternary = strip_parentheses(node.children[1])
                target = source.source_of(node.children[0])
                if same_kind(source, ternary.children[1], ternary.children[2]):
                    text = (f'if ({source.source_of(strip_parentheses(ternary.children[0]))})\n{indent}{step}{target} = {source.source_of(ternary.children[1])};\n'
                            f'{indent}else\n{indent}{step}{target} = {source.source_of(ternary.children[2])};')
                    found.append((f'ternary_assignment@{line_of(source, statement)} ternary as if/else', [(*source.span(statement), text)]))
            if statement.kind == 'return' and node.kind == 'ternary' and same_kind(source, node.children[1], node.children[2]):
                text = (f'if ({source.source_of(strip_parentheses(node.children[0]))})\n{indent}{step}return {source.source_of(node.children[1])};\n'
                        f'{indent}return {source.source_of(node.children[2])};')
                found.append((f'ternary_assignment@{line_of(source, statement)} ternary return as two returns', [(*source.span(statement), text)]))
    return found


def early_return(source):
    """`if (c) { ...; return; } else { B }` against `if (c) { ...; return; } B` (the else dropped or added); in a void function, a final
    `if (c) { REST }` against `if (!c) return; REST`. Sly 1 toolchain notes: docs/toolchain/jump.md (which arm falls through, cross-jumping)."""
    if has_labels(source):
        return []
    found = []
    parents = source.parent_map()
    step = unit_indent(source)
    void_function = re.match(r'\s*(?:static\s+|inline\s+|extern\s+"C"\s+)*void\s+[\w:~]+\s*\(', source.text_of(source.function.header_first, source.function.parameter_open) + '(') is not None \
        or re.search(r'\bvoid\s+(?:\w+::)?\w+\s*$', source.text_of(source.function.header_first, source.function.parameter_open - 1)) is not None
    for statement in source.body.walk():
        if statement.kind != 'if':
            continue
        parent = parents.get(id(statement))
        if not parent or parent[0].kind != 'block':
            continue
        then, otherwise = statement.parts['then'], statement.parts['otherwise']
        indent = source.indent_of(statement)
        items = parent[0].parts['statements']
        if otherwise is not None and ends_in_exit(then) and otherwise.kind != 'if':
            else_start = source.tokens[then.last].end
            inner = statements_text(source, arm_statements(otherwise), indent)
            found.append((f'early_return@{line_of(source, statement)} else dropped after an exit', [(else_start, source.span(otherwise)[1], '\n' + inner)]))
        if otherwise is None and ends_in_exit(then) and then.kind == 'block' and parent[1] + 1 < len(items):
            rest = items[parent[1] + 1:]
            if not any(item.kind in ('declaration', 'label', 'case') for item in rest):
                inner = statements_text(source, rest, indent + step)
                found.append((f'early_return@{line_of(source, statement)} rest of the block as an else', [(source.span(statement)[1], source.span(rest[-1])[1], f' else {{\n{inner}\n{indent}}}')]))
        if void_function and parent[0] is source.body and parent[1] == len(items) - 1 and otherwise is None and then.kind == 'block':
            inner = statements_text(source, then.parts['statements'], indent)
            text = f'if ({negation(source, statement.parts["condition"])})\n{indent}{step}return;\n{inner}'
            found.append((f'early_return@{line_of(source, statement)} final if as an early return', [(*source.span(statement), text)]))
        single_then = single(then)
        if void_function and parent[0] is source.body and otherwise is None and single_then is not None and single_then.kind == 'return' and single_then.parts['value'] is None \
                and parent[1] + 1 < len(items):
            rest = items[parent[1] + 1:]
            if not any(item.kind in ('declaration', 'label', 'case') for item in rest):
                inner = statements_text(source, rest, indent + step)
                text = f'if ({negation(source, statement.parts["condition"])}) {{\n{inner}\n{indent}}}'
                found.append((f'early_return@{line_of(source, statement)} early return as a final if', [(source.span(statement)[0], source.span(rest[-1])[1], text)]))
    return found


def compound_assignment(source):
    """`x = x op y` against `x op= y` for every binary operator (x without side effects). Sly 1 toolchain notes: docs/toolchain/cse.md (one
    expression, one pseudo)."""
    found = []
    for statement in source.body.walk():
        if statement.kind != 'expression':
            continue
        node = strip_parentheses(statement.parts['expression'])
        if node.kind != 'assign':
            continue
        target, value = node.children
        if not is_simple_lvalue(source, target):
            continue
        value_inner = strip_parentheses(value)
        if node.operator == '=' and value_inner.kind == 'binary' and value_inner.operator in BINARY_PRECEDENCE and value_inner.operator not in BOOLEAN_OPERATORS | {'<?', '>?'} \
                and normalized(source.source_of(value_inner.children[0])) == normalized(source.source_of(target)):
            text = f'{source.source_of(target)} {value_inner.operator}= {source.source_of(value_inner.children[1])}'
            found.append((f'compound_assignment@{line_of(source, statement)} x = x {value_inner.operator} y as {value_inner.operator}=', [(*source.span(node), text)]))
        elif node.operator not in ('=', '<?=', '>?=') and node.operator[:-1] in BINARY_PRECEDENCE:
            operator = node.operator[:-1]
            text = f'{source.source_of(target)} = {source.source_of(target)} {operator} {operand_text(source, value, operator) if strip_parentheses(value).kind == "binary" and BINARY_PRECEDENCE[strip_parentheses(value).operator] <= BINARY_PRECEDENCE[operator] else source.source_of(value)}'
            if strip_parentheses(value).kind in ('assign', 'ternary', 'comma'):
                text = f'{source.source_of(target)} = {source.source_of(target)} {operator} ({source.source_of(value)})'
            found.append((f'compound_assignment@{line_of(source, statement)} {node.operator} as x = x {operator} y', [(*source.span(node), text)]))
    return found


def commute_operands(source):
    """The two operands of one commutative operator (+ * & | ^ == !=) swapped, both free of side effects; a comparison written the other way
    round (a < b as b > a). Parsed, so `a * b + c` is (a * b) + c and becomes `c + a * b`, never `a * c + b` (the asinf polynomial that
    mutate.py's commute broke, docs/IDEAS.md). Swapping two operands of one IEEE add or multiply gives the same value. Sly 1 toolchain notes:
    docs/toolchain/regalloc.md (operand order is the order of the instruction's registers)."""
    found = []
    for statement in source.body.walk():
        for key in ('condition', 'step', 'expression', 'value'):
            root = statement.parts.get(key)
            if root is None or not hasattr(root, 'walk'):
                continue
            for node in root.walk():
                if node.kind != 'binary':
                    continue
                left, right = node.children
                if node.operator in COMMUTATIVE and is_pure(source, left) and is_pure(source, right):
                    text = f'{operand_text(source, right, node.operator)} {node.operator} {operand_text(source, left, node.operator)}'
                    found.append((f'commute_operands@{source.line_number(source.tokens[node.first].start)} {node.operator}', [(*source.span(node), text)]))
                elif node.operator in ('<', '>', '<=', '>=') and is_pure(source, left) and is_pure(source, right):
                    found.append((f'commute_operands@{source.line_number(source.tokens[node.first].start)} {node.operator} flipped', [(*source.span(node), flip_comparison(source, node))]))
    return found


def declaration_placement(source):
    """A declaration (scalar or pointer type, one name) hoisted to the top of the function or of its block, its initialiser left in place
    as an assignment; a declaration without initialiser sunk into its first assignment in the same block. Sly 1 toolchain notes:
    docs/toolchain/regalloc.md (a pseudo's number follows its first appearance)."""
    found = []
    parents = source.parent_map()
    body_items = source.body.parts['statements']
    top_insert = None
    for item in body_items:
        if item.kind != 'declaration':
            break
        top_insert = item
    for statement in source.body.walk():
        if statement.kind != 'declaration' or len(statement.parts['declarators']) != 1:
            continue
        declarator = statement.parts['declarators'][0]
        type_text = source.type_of_local(declarator.name)
        if declarator.dimensions or not plain_scalar_type(type_text) or len(source.uses(declarator.name)) < 1:
            continue
        if sum(1 for other in source.body.walk() if other.kind == 'declaration' and any(item.name == declarator.name for item in other.parts['declarators'])) != 1:
            continue
        parent = parents.get(id(statement))
        lines = line_text(source, statement)
        if not parent or parent[0].kind != 'block' or not lines:
            continue
        indent = source.indent_of(statement)
        remainder = f'{indent}{declarator.name} = {source.source_of(declarator.initializer)};\n' if declarator.initializer is not None else ''
        if declarator.initializer is not None and declarator.initializer.kind in ('braces', 'construct'):
            continue
        declaration_line = declaration(type_text, declarator.name)
        targets = []
        if parent[0] is not source.body or parent[1] > body_items.index(top_insert) + 1 if top_insert else parent[0] is not source.body or parent[1] > 0:
            targets.append(('function top', source.body))
        block_items = parent[0].parts['statements']
        leading = 0
        while leading < len(block_items) and block_items[leading].kind == 'declaration':
            leading += 1
        if parent[0] is not source.body and parent[1] > leading:
            targets.append(('block top', parent[0]))
        for where, block in targets:
            items = block.parts['statements']
            anchor = None
            for item in items:
                if item.kind != 'declaration':
                    break
                anchor = item
            anchor_lines = line_text(source, anchor) if anchor else None
            if anchor is not None and anchor_lines is None:
                continue
            insert_at = anchor_lines[1] if anchor_lines else source.tokens[block.first].end + 1
            new_indent = source.indent_of(items[0]) if items else indent
            if source.text[insert_at - 1:insert_at] != '\n':
                continue
            found.append((f'declaration_placement@{line_of(source, statement)} {declarator.name} hoisted to the {where}',
                          [(insert_at, insert_at, f'{new_indent}{declaration_line}\n'), (lines[0], lines[1], remainder)]))
        if declarator.initializer is None:
            following = block_items[parent[1] + 1:]
            for position, item in enumerate(following):
                uses = source.uses(declarator.name, item.first, item.last)
                if not uses:
                    continue
                assignment = assignment_of(item)
                if assignment and strip_parentheses(assignment[0]).kind == 'name' and strip_parentheses(assignment[0]).operator == declarator.name \
                        and len(uses) == 1 and line_text(source, item):
                    text = declaration(type_text, declarator.name, source.source_of(assignment[1]))
                    found.append((f'declaration_placement@{line_of(source, statement)} {declarator.name} sunk into its first assignment',
                                  [(lines[0], lines[1], ''), (*source.span(item), text)]))
                break
    return found


def declared_at(source):
    """The token indexes of every declarator's name: a declaration with an initialiser is not an assignment."""
    return {declarator.name_token for statement, declarator in source.declarations.values()}


def assigned_anywhere(source, name):
    """True when a local is assigned, incremented or has its address taken anywhere after its declaration."""
    declared = declared_at(source)
    for index in source.uses(name):
        if index in declared:
            continue
        following = source.tokens[index + 1].text if index + 1 < len(source.tokens) else ''
        previous = source.tokens[index - 1].text
        if following in ('=', '+=', '-=', '*=', '/=', '%=', '&=', '|=', '^=', '<<=', '>>=', '++', '--') or previous in ('++', '--', '&'):
            return True
    return False


def const_local(source):
    """`const` added to a scalar local or value parameter that is never assigned after its declaration, or removed from one. Sly 1 toolchain
    notes: docs/toolchain/alias-classes.md (a const object's loads move across stores)."""
    found = []
    for name, (statement, declarator) in source.declarations.items():
        if len(statement.parts['declarators']) != 1 or declarator.dimensions or declarator.initializer is None or '&' in declarator.stars:
            continue
        base = statement.parts['base']
        base_first = statement.first
        if re.search(r'\bregister\b', base) or source.tokens[declarator.name_token + 1].text in ('asm', '__asm__'):
            continue
        if re.match(r'\s*const\b', base) and not declarator.stars:
            const_token = next(index for index in range(statement.first, statement.parts['base_last'] + 1) if source.tokens[index].text == 'const')
            found.append((f'const_local@{line_of(source, statement)} const removed from {name}', [(source.tokens[const_token].start, source.tokens[const_token + 1].start, '')]))
        elif 'const' not in base and not assigned_anywhere(source, name) and name not in source.address_taken:
            if declarator.stars:
                insert = source.tokens[declarator.name_token].start
                found.append((f'const_local@{line_of(source, statement)} {name} a const pointer', [(insert, insert, 'const ')]))
            elif plain_scalar_type(source.type_of_local(name)):
                start = source.tokens[base_first].start
                found.append((f'const_local@{line_of(source, statement)} {name} const', [(start, start, 'const ')]))
    return found


def pointer_reference(source):
    """A pointer local only used as `p->m` written as a reference (`T &p = *e;`, `p.m`), and a reference local back as a pointer.
    Sly 1 toolchain notes: docs/toolchain/alias-classes.md (the pointer's pseudo against the object's address)."""
    found = []
    for name, (statement, declarator) in source.declarations.items():
        if len(statement.parts['declarators']) != 1 or declarator.initializer is None or declarator.initializer.kind in ('braces', 'construct'):
            continue
        uses = [index for index in source.uses(name) if index != declarator.name_token]
        if not uses:
            continue
        if declarator.stars == '*' and all(source.tokens[index + 1].text == '->' for index in uses) and not assigned_anywhere(source, name):
            edits = [(source.tokens[declarator.first].start, source.tokens[declarator.name_token].start, '&'),
                     (*source.span(declarator.initializer), f'*{parenthesize(source, declarator.initializer)}')]
            edits += [(source.tokens[index + 1].start, source.tokens[index + 1].end, '.') for index in uses]
            found.append((f'pointer_reference@{line_of(source, statement)} {name} as a reference', edits))
        if declarator.stars == '&' and all(source.tokens[index + 1].text == '.' for index in uses):
            edits = [(source.tokens[declarator.first].start, source.tokens[declarator.name_token].start, '*'),
                     (*source.span(declarator.initializer), f'&{parenthesize(source, declarator.initializer)}')]
            edits += [(source.tokens[index + 1].start, source.tokens[index + 1].end, '->') for index in uses]
            found.append((f'pointer_reference@{line_of(source, statement)} {name} as a pointer', edits))
    return found


def callee_parameter_types(source, callee):
    """[type text] of a callee's parameters from its declaration in the file, or None."""
    for match in re.finditer(rf'(?<![\w.>])({re.escape(callee)})\s*\(([^;{{}}()]*)\)\s*;', source.text):
        prefix = source.text[max(0, match.start() - 80):match.start()]
        if not re.search(r'[\w\*&]\s*$', prefix):
            continue
        parameters = [part.strip() for part in match.group(2).split(',')] if match.group(2).strip() not in ('', 'void') else []
        types = []
        for parameter in parameters:
            text = parameter
            last = re.search(r'([A-Za-z_]\w*)\s*$', parameter)
            if last and len(re.findall(r'[A-Za-z_]\w*', parameter)) > 1 and not (last.group(1) in TYPE_KEYWORDS or last.group(1) in PROJECT_TYPES or source.is_type_name(last.group(1))):
                text = parameter[:last.start()].strip()
            types.append(text)
        return types
    return None


def argument_local(source):
    """A call's argument (no side effects, not a plain name or literal) named by a local of the callee's parameter type, declared just
    before the statement; only where nothing else in the statement has a side effect that the earlier read could cross. Sly 1 toolchain
    notes: docs/toolchain/sched1.md (an argument computed in its own statement issues earlier)."""
    found = []
    parents = source.parent_map()
    for statement in source.body.walk():
        if statement.kind not in ('expression', 'return'):
            continue
        parent = parents.get(id(statement))
        lines = line_text(source, statement)
        if not parent or parent[0].kind != 'block' or not lines:
            continue
        root = statement.parts.get('expression') if statement.kind == 'expression' else statement.parts.get('value')
        if root is None:
            continue
        calls = [node for node in root.walk() if node.kind == 'call' and node.children and node.children[0].kind == 'name']
        if len(calls) != 1:
            continue
        call = calls[0]
        types = callee_parameter_types(source, call.children[0].operator)
        if types is None or len(types) != len(call.children) - 1:
            continue
        others_pure = all(is_pure(source, argument) for argument in call.children[1:])
        if not others_pure:
            continue
        indent = source.indent_of(statement)
        for position, argument in enumerate(call.children[1:]):
            inner = strip_parentheses(argument)
            if inner.kind in ('name', 'number', 'string', 'type') or '...' in types[position] or types[position] == '':
                continue
            name = fresh_name(source, 'argument')
            edits = [(lines[0], lines[0], f'{indent}{declaration(types[position], name, source.source_of(argument))}\n'), (*source.span(argument), name)]
            found.append((f'argument_local@{line_of(source, statement)} argument {position + 1} of {call.children[0].operator}', edits))
    return found


def switch_groups(source, switch):
    """[(labels, statements)] of a switch whose body is a block of `case` groups, or None."""
    body = switch.parts['body']
    if body.kind != 'block':
        return None
    groups = []
    for item in body.parts['statements']:
        if item.kind == 'case':
            if groups and not groups[-1][1]:
                groups[-1][0].append(item)
            else:
                groups.append(([item], []))
        elif not groups:
            return None
        else:
            groups[-1][1].append(item)
    return groups


def level_breaks(statements):
    """The `break` statements among these statements that bind to the statement around them (not to an inner loop or switch)."""
    found = []
    for statement in statements:
        if statement.kind == 'break':
            found.append(statement)
        elif statement.kind not in ('while', 'do', 'for', 'switch'):
            found.extend(level_breaks(statement.children()))
    return found


def chain_values(source, condition, operand):
    """(operand text, [value texts]) when a test is `x == K` or `x == K1 || x == K2` on one operand (the given one, if any), else None."""
    values = []
    for part in split_or(strip_parentheses(condition)):
        part = strip_parentheses(part)
        if part.kind != 'binary' or part.operator != '==' or literal_value(part.children[1]) is None:
            return None
        text = normalized(source.source_of(part.children[0]))
        if operand is not None and text != operand:
            return None
        operand = text
        values.append(source.source_of(part.children[1]))
    return operand, values


def switch_if_chain(source):
    """A switch with no fall-through (each group ends in break, return, continue or goto) on an operand without side effects as an
    if/else-if chain, and a chain of `x == K` tests on one operand as a switch. Sly 1 toolchain notes: docs/toolchain/jump.md (a switch of
    fewer than five cases is a compare tree; an if chain gives bnez and movn)."""
    if has_labels(source):
        return []
    found = []
    step = unit_indent(source)
    for statement in source.body.walk():
        if statement.kind == 'switch':
            condition = statement.parts['condition']
            groups = switch_groups(source, statement)
            if not groups or not is_pure(source, condition):
                continue
            if any(not statements or not ends_in_exit(statements[-1]) for _, statements in groups[:-1]):
                continue
            if any(level_breaks(statements[:-1] if statements and statements[-1].kind == 'break' else statements) for _, statements in groups):
                continue
            indent = source.indent_of(statement)
            operand = parenthesize(source, condition)
            parts, default = [], None
            for labels, statements in groups:
                kept = statements[:-1] if statements and statements[-1].kind == 'break' else statements
                body = statements_text(source, kept, indent + step) if kept else ''
                block = '{\n' + (body + '\n' if body else '') + indent + '}'
                values = [label.parts['value'] for label in labels]
                if any(value is None for value in values):
                    default = block
                    continue
                test = ' || '.join(f'{operand} == {source.source_of(value)}' for value in values)
                parts.append((test, block))
            if not parts:
                continue
            text = ' else '.join(f'if ({test}) {block}' for test, block in parts)
            if default is not None:
                text += f' else {default}'
            found.append((f'switch_if_chain@{line_of(source, statement)} switch as if chain', [(*source.span(statement), text)]))
        if statement.kind == 'if':
            chain, current, operand = [], statement, None
            while current is not None and current.kind == 'if':
                read = chain_values(source, current.parts['condition'], operand)
                if read is None:
                    break
                operand = read[0]
                chain.append((read[1], current.parts['then']))
                current = current.parts['otherwise']
            if len(chain) < 2:
                continue
            arms = [arm for _, arm in chain] + ([current] if current is not None else [])
            if any(level_breaks(arm_statements(arm)) for arm in arms):
                continue
            first_test = strip_parentheses(split_or(strip_parentheses(statement.parts['condition']))[0])
            if not is_pure(source, first_test.children[0]):
                continue
            indent = source.indent_of(statement)
            lines = []
            for values, arm in chain:
                lines.extend(f'{indent}case {value}:' for value in values)
                inner = statements_text(source, arm_statements(arm), indent + step)
                if inner:
                    lines.append(inner)
                if not ends_in_exit(arm):
                    lines.append(f'{indent}{step}break;')
            if current is not None:
                lines.append(f'{indent}default:')
                inner = statements_text(source, arm_statements(current), indent + step)
                if inner:
                    lines.append(inner)
                if not ends_in_exit(current):
                    lines.append(f'{indent}{step}break;')
            text = f'switch ({source.source_of(first_test.children[0])}) {{\n' + '\n'.join(lines) + f'\n{indent}}}'
            found.append((f'switch_if_chain@{line_of(source, statement)} if chain as switch', [(*source.span(statement), text)]))
    return found


def split_or(node):
    if node.kind == 'binary' and node.operator == '||':
        return split_or(strip_parentheses(node.children[0])) + split_or(strip_parentheses(node.children[1]))
    return [node]


def index_uses(source, array, counter, first, last):
    """Token indexes of `array[counter]` (the array name's token) between two tokens, or None when the counter appears any other way."""
    found = []
    for index in source.uses(counter, first, last):
        if not (source.tokens[index - 1].text == '[' and source.tokens[index + 1].text == ']' and source.tokens[index - 2].text == array
                and source.tokens[index - 3].text not in ('.', '->', '::')):
            return None
        found.append(index - 2)
    return found


def pointer_walk(source):
    """A counted loop `for (i = 0; i < n; i++)` over `A[i]` walked with a pointer instead: the counter kept for the test, or dropped when it
    serves only the walk (and is not read after the loop). A and the bound are not written in the body. Sly 1 toolchain notes:
    docs/toolchain/loops.md (strength reduction and the giv a pointer walk replaces)."""
    if has_labels(source):
        return []
    found = []
    for statement in source.body.walk():
        if statement.kind != 'for':
            continue
        init, condition, step, body = (statement.parts[key] for key in ('init', 'condition', 'step', 'body'))
        if init is None or condition is None or step is None or body.kind != 'block':
            continue
        if init.kind == 'expression':
            assignment = assignment_of(init)
        elif init.kind == 'declaration' and len(init.parts['declarators']) == 1 and init.parts['declarators'][0].initializer is not None:
            assignment = (None, init.parts['declarators'][0].initializer)
        else:
            continue
        if assignment is None or literal_value(assignment[1]) != 0:
            continue
        counter = strip_parentheses(assignment[0]).operator if assignment[0] is not None else init.parts['declarators'][0].name
        test = strip_parentheses(condition)
        step_node = strip_parentheses(step)
        if test.kind != 'binary' or test.operator != '<' or strip_parentheses(test.children[0]).kind != 'name' or strip_parentheses(test.children[0]).operator != counter:
            continue
        if not (step_node.kind in ('postfix', 'unary') and step_node.operator == '++' and strip_parentheses(step_node.children[0]).kind == 'name'
                and strip_parentheses(step_node.children[0]).operator == counter):
            continue
        bound = test.children[1]
        body_effects = source.effects(body)
        if not is_pure(source, bound) or source.node_effects(bound).reads & body_effects.writes or (source.node_effects(bound).memory_read and (body_effects.memory_write or body_effects.call)):
            continue
        arrays = {source.tokens[index - 2].text for index in source.uses(counter, body.first, body.last) if source.tokens[index - 1].text == '['}
        if len(arrays) != 1:
            continue
        array = arrays.pop()
        uses = index_uses(source, array, counter, body.first, body.last)
        element = element_type(source, array)
        if not uses or not element or array in body_effects.writes or not stable_base(source, array):
            continue
        cursor = fresh_name(source, 'element')
        edits = []
        for index in uses:
            closer = index + 3
            following = source.tokens[closer + 1].text if closer + 1 < len(source.tokens) else ''
            if following == '.':
                edits.append((source.tokens[index].start, source.tokens[closer + 1].end, f'{cursor}->'))
            else:
                edits.append((source.tokens[index].start, source.tokens[closer].end, f'(*{cursor})'))
        indent = source.indent_of(statement)
        closer = source.matching(statement.first + 1)
        header_kept = f'for ({source.source_of(init).rstrip(";")}; {source.source_of(condition)}; {source.source_of(step)}, {cursor}++)'
        found.append((f'pointer_walk@{line_of(source, statement)} {array}[{counter}] walked by a pointer, counter kept',
                      [(source.tokens[statement.first].start, source.tokens[statement.first].start, f'{declaration(element + " *", cursor, array)}\n{indent}'),
                       (source.tokens[statement.first].start, source.tokens[closer].end, header_kept)] + edits))
        outside = [index for index in source.uses(counter) if not (statement.first <= index <= statement.last)]
        counter_declaration = source.declarations.get(counter)
        if counter_declaration and counter_declaration[0] is not init:
            outside = [index for index in outside if index != counter_declaration[1].name_token]
        if not outside and (counter_declaration is None or counter_declaration[0] is init or len(counter_declaration[0].parts['declarators']) == 1):
            removal = []
            if counter_declaration and counter_declaration[0] is not init:
                lines = line_text(source, counter_declaration[0])
                if not lines or counter_declaration[1].initializer is not None:
                    continue
                removal = [(lines[0], lines[1], '')]
            header_dropped = f'for ({declaration(element + " *", cursor, array)} {cursor} < {array} + {operand_text(source, bound, "+")}; {cursor}++)'
            found.append((f'pointer_walk@{line_of(source, statement)} {array}[{counter}] walked by a pointer, counter dropped',
                          [(source.tokens[statement.first].start, source.tokens[closer].end, header_dropped)] + edits + removal))
    return found


def element_pointer(source):
    """A repeated element `A[i]` (A and i names or literals, read twice or more in a run of statements that writes neither) named by a
    pointer `T *element = &A[i];` declared before the first, its uses then `element->m` or `*element`. Sly 1 toolchain notes:
    docs/toolchain/cse.md (one address, one register)."""
    found = []
    for block in source.blocks():
        items = block.parts['statements']
        for start_position, first in enumerate(items):
            lines = line_text(source, first)
            if not lines or first.kind == 'case':
                continue
            occurrences = {}
            for node in statement_nodes(first):
                if node.kind == 'index' and strip_parentheses(node.children[0]).kind == 'name' and strip_parentheses(node.children[1]).kind in ('name', 'number'):
                    occurrences.setdefault(normalized(source.source_of(node)), node)
            for key, node in occurrences.items():
                array = strip_parentheses(node.children[0]).operator
                index_node = strip_parentheses(node.children[1])
                watched = {array} | ({index_node.operator} if index_node.kind == 'name' else set())
                if not stable_base(source, array) or (index_node.kind == 'name' and index_node.operator in source.variables and not source.tracked(index_node.operator)):
                    continue
                element = element_type(source, array)
                if not element:
                    continue
                matches = []
                for position in range(start_position, len(items)):
                    item = items[position]
                    if item.kind in ('case', 'label'):
                        break
                    effects = source.effects(item)
                    item_matches = [candidate for candidate in statement_nodes(item) if candidate.kind == 'index' and normalized(source.source_of(candidate)) == key]
                    if effects.writes & watched:
                        break
                    matches.extend(item_matches)
                if len(matches) < 2 or any(is_written_place(source, match) for match in matches):
                    continue
                name = fresh_name(source, 'element')
                indent = source.indent_of(first)
                edits = [(lines[0], lines[0], f'{indent}{declaration(element + " *", name, "&" + source.source_of(node))}\n')]
                for match in matches:
                    member = source.tokens[match.last + 1] if match.last + 1 < len(source.tokens) else None
                    address = source.tokens[match.first - 1]
                    if address.text == '&' and source.tokens[match.first - 2].kind != 'identifier' and source.tokens[match.first - 2].text not in (')', ']'):
                        edits.append((address.start, source.tokens[match.last].end, name))
                    elif member is not None and member.text == '.':
                        edits.append((source.tokens[match.first].start, member.end, f'{name}->'))
                    else:
                        edits.append((*source.span(match), f'(*{name})'))
                found.append((f'element_pointer@{line_of(source, first)} {key} named by a pointer ({len(matches)} uses)', edits))
    return found


def stable_base(source, name):
    """True when a name's value cannot change through memory: a tracked local, a local array, or a global array of the file."""
    if source.tracked(name):
        return True
    if name in source.declarations:
        return bool(source.declarations[name][1].dimensions)
    return name not in source.variables


def statement_nodes(statement):
    """Every expression node of a statement and the statements inside it."""
    for item in statement.walk():
        for key in ('condition', 'step', 'expression', 'value'):
            node = item.parts.get(key)
            if node is not None and hasattr(node, 'walk'):
                yield from node.walk()
        if item.kind == 'declaration':
            for declarator in item.parts['declarators']:
                if declarator.initializer is not None and declarator.initializer.kind not in ('braces', 'construct'):
                    yield from declarator.initializer.walk()


def is_written_place(source, node):
    """True when an element is the target of an assignment, an increment or `&`... except `&A[i]` itself which is fine: only writes count."""
    before = source.tokens[node.first - 1].text if node.first else ''
    after = source.tokens[node.last + 1].text if node.last + 1 < len(source.tokens) else ''
    return after in ('=', '+=', '-=', '*=', '/=', '%=', '&=', '|=', '^=', '<<=', '>>=', '++', '--') or before in ('++', '--')


def local_ranges(source):
    """{name: (first use, last use)} of the tracked scalar locals declared once by a one-name declaration."""
    ranges = {}
    for name, (statement, declarator) in source.declarations.items():
        if len(statement.parts['declarators']) != 1 or not source.tracked(name) or not plain_scalar_type(source.type_of_local(name)):
            continue
        uses = [index for index in source.uses(name) if index != declarator.name_token]
        if uses:
            ranges[name] = (uses[0], uses[-1])
    return ranges


def reuse_variable(source):
    """Two locals of one type whose lives do not overlap merged into one (the second's declaration becomes an assignment), and one local
    split in two at a top-level assignment that starts a new life. No loop may hold both lives, and the second must be written before it is
    read. Sly 1 toolchain notes: docs/toolchain/alias-classes.md ("One int for a size, a count and an index") and regalloc.md."""
    found = []
    if any(statement.kind in ('goto', 'label') for statement in source.body.walk()):
        return found
    parents = source.parent_map()
    ranges = local_ranges(source)
    loops = [statement for statement in source.body.walk() if statement.kind in ('while', 'do', 'for')]
    names = sorted(ranges, key=lambda name: ranges[name][0])
    for first_name in names:
        for second_name in names:
            if first_name == second_name or source.type_of_local(first_name) != source.type_of_local(second_name):
                continue
            first_range, second_range = ranges[first_name], ranges[second_name]
            if first_range[1] >= second_range[0]:
                continue
            if any(loop.first <= first_range[1] and loop.last >= second_range[0] and any(loop.first <= use <= loop.last for use in source.uses(first_name)) for loop in loops):
                continue
            first_statement, first_declarator = source.declarations[first_name]
            second_statement, second_declarator = source.declarations[second_name]
            first_parent = parents.get(id(first_statement))
            if not first_parent or not (first_parent[0].first <= second_range[0] and second_range[1] <= first_parent[0].last):
                continue
            lines = line_text(source, second_statement)
            if not lines:
                continue
            if second_declarator.initializer is None:
                following = [index for index in source.uses(second_name) if index != second_declarator.name_token]
                if not following or source.tokens[following[0] + 1].text != '=' or source.tokens[following[0] - 1].text in ('.', '->', '*', '&'):
                    continue
                replacement = ''
            else:
                replacement = f'{source.indent_of(second_statement)}{first_name} = {source.source_of(second_declarator.initializer)};\n'
            edits = [(lines[0], lines[1], replacement)]
            edits += [(source.tokens[index].start, source.tokens[index].end, first_name) for index in source.uses(second_name) if index != second_declarator.name_token]
            found.append((f'reuse_variable@{line_of(source, second_statement)} {second_name} merged into {first_name}', edits))
    body_items = source.body.parts['statements']
    for position, statement in enumerate(body_items):
        assignment = assignment_of(statement)
        if not assignment or strip_parentheses(assignment[0]).kind != 'name':
            continue
        name = strip_parentheses(assignment[0]).operator
        if name not in ranges or name in source.node_effects(assignment[1]).reads:
            continue
        earlier = [index for index in source.uses(name) if index < statement.first and index != source.declarations[name][1].name_token]
        later = [index for index in source.uses(name) if index > statement.last]
        if not earlier or not later or not line_text(source, statement):
            continue
        new_name = fresh_name(source, f'{name}2')
        edits = [(*source.span(statement), f'{source.type_of_local(name)} {new_name} = {source.source_of(assignment[1])};')]
        edits += [(source.tokens[index].start, source.tokens[index].end, new_name) for index in later]
        found.append((f'reuse_variable@{line_of(source, statement)} {name} split from here as {new_name}', edits))
    return found


def test_in_each_arm(source):
    """A test after an if/else whose arms both set the variable it reads (`if (a) x = F(); else x = G(); if (x) S`) written in each arm
    instead, and the reverse: the same last statement of both arms written once after the if. Sly 1 toolchain notes: docs/toolchain/gcse.md
    ("A test written in each arm"); our lessons.md notes the same lever."""
    if has_labels(source):
        return []
    found = []
    parents = source.parent_map()
    step = unit_indent(source)
    for statement in source.body.walk():
        if statement.kind != 'if' or statement.parts['otherwise'] is None or statement.parts['otherwise'].kind == 'if':
            continue
        parent = parents.get(id(statement))
        if not parent or parent[0].kind != 'block':
            continue
        items = parent[0].parts['statements']
        then, otherwise = statement.parts['then'], statement.parts['otherwise']
        indent = source.indent_of(statement)
        following = items[parent[1] + 1] if parent[1] + 1 < len(items) else None
        if following is not None and following.kind == 'if' and line_text(source, following):
            read = source.node_effects(following.parts['condition']).reads
            then_writes, else_writes = source.effects(then).writes, source.effects(otherwise).writes
            if read & then_writes & else_writes:
                tail = reindent(source.source_of(following), source.indent_of(following), indent + step)
                edits = []
                for arm in (then, otherwise):
                    inner = statements_text(source, arm_statements(arm), indent + step)
                    edits.append((*source.span(arm), '{\n' + inner + '\n' + indent + step + tail.lstrip() + '\n' + indent + '}'))
                lines = line_text(source, following)
                edits.append((lines[0], lines[1], ''))
                found.append((f'test_in_each_arm@{line_of(source, statement)} following test written in each arm', edits))
        if then.kind == 'block' and otherwise.kind == 'block' and then.parts['statements'] and otherwise.parts['statements']:
            last_then, last_else = then.parts['statements'][-1], otherwise.parts['statements'][-1]
            if last_then.kind not in ('declaration', 'case', 'label') and normalized(source.source_of(last_then)) == normalized(source.source_of(last_else)):
                then_lines, else_lines = line_text(source, last_then), line_text(source, last_else)
                if then_lines and else_lines:
                    text = '\n' + indent + reindent(source.source_of(last_then), source.indent_of(last_then), indent).lstrip()
                    found.append((f'test_in_each_arm@{line_of(source, statement)} common last statement written once after the if',
                                  [(then_lines[0], then_lines[1], ''), (else_lines[0], else_lines[1], ''), (source.span(statement)[1], source.span(statement)[1], text)]))
    return found


def case_order(source):
    """The order of a switch's groups (none falling through: each ends in break, return, continue or goto) and of the labels of one group;
    a value set just before the switch set in every group instead (a default group added where there is none), and the reverse. Sly 1
    toolchain notes: docs/toolchain/loops.md ("A count set in each arm") and jump.md (the case tree)."""
    if has_labels(source):
        return []
    found = []
    parents = source.parent_map()
    step = unit_indent(source)
    for statement in source.body.walk():
        if statement.kind != 'switch':
            continue
        groups = switch_groups(source, statement)
        if not groups:
            continue
        closed = all(statements and ends_in_exit(statements[-1]) for _, statements in groups)
        body = statement.parts['body']
        group_texts = []
        for labels, statements in groups:
            start = line_text(source, labels[0])
            end = line_text(source, statements[-1] if statements else labels[-1])
            group_texts.append((start, end))
        if closed and all(start and end for start, end in group_texts):
            for position in range(len(groups) - 1):
                first, second = group_texts[position], group_texts[position + 1]
                text_first = source.text[first[0][0]:first[1][1]]
                text_second = source.text[second[0][0]:second[1][1]]
                found.append((f'case_order@{line_of(source, groups[position][0][0])} groups {position + 1} and {position + 2} swapped',
                              [(first[0][0], second[1][1], text_second + text_first)]))
        for labels, _ in groups:
            if len(labels) > 1 and all(line_text(source, label) for label in labels):
                spans = [line_text(source, label) for label in labels]
                rotated = ''.join(span[2] for span in spans[1:] + spans[:1])
                found.append((f'case_order@{line_of(source, labels[0])} labels rotated', [(spans[0][0], spans[-1][1], rotated)]))
        parent = parents.get(id(statement))
        if not closed or not parent or parent[0].kind != 'block':
            continue
        items = parent[0].parts['statements']
        condition = statement.parts['condition']
        indent = source.indent_of(statement)
        label_indent = source.indent_of(groups[0][0][0])
        inner_indent = source.indent_of(groups[0][1][0]) if groups[0][1] else label_indent + step
        if parent[1] > 0:
            before = items[parent[1] - 1]
            assignment = assignment_of(before)
            lines = line_text(source, before)
            if assignment and lines and is_simple_lvalue(source, assignment[0]) and is_pure(source, assignment[1]) and is_pure(source, condition) \
                    and not reads_target(source, condition, assignment[0]):
                text = source.source_of(before)
                edits = [(lines[0], lines[1], '')]
                for labels, _ in groups:
                    at = source.tokens[labels[-1].last].end
                    edits.append((at, at, f'\n{inner_indent}{text}'))
                if not any(label.parts['value'] is None for labels, _ in groups for label in labels):
                    at = source.tokens[body.last].start
                    line_start = source.text.rfind('\n', 0, at) + 1
                    edits.append((line_start, line_start, f'{label_indent}default:\n{inner_indent}{text}\n{inner_indent}break;\n'))
                found.append((f'case_order@{line_of(source, statement)} value set in every group', edits))
        firsts = [statements[0] if statements else None for _, statements in groups]
        if all(first is not None for first in firsts) and any(label.parts['value'] is None for labels, _ in groups for label in labels):
            texts = {normalized(source.source_of(first)) for first in firsts}
            assignment = assignment_of(firsts[0])
            if len(texts) == 1 and assignment and is_pure(source, assignment[1]) and is_pure(source, condition) and not reads_target(source, condition, assignment[0]) \
                    and all(line_text(source, first) for first in firsts):
                edits = [(line_text(source, first)[0], line_text(source, first)[1], '') for first in firsts]
                start = source.span(statement)[0]
                edits.append((start, start, f'{source.source_of(firsts[0])}\n{indent}'))
                found.append((f'case_order@{line_of(source, statement)} value set in every group hoisted before the switch', edits))
    return found


def repeat_expression(source):
    """An expression without side effects written twice or more in a run of statements of one block (a member or element read, or
    arithmetic on one) named once by a local of its type before the first, where no statement of the run writes what it reads. Sly 1
    toolchain notes: docs/toolchain/gcse.md ("One reaching register for every occurrence")."""
    found = []
    for block in source.blocks():
        items = block.parts['statements']
        for start_position, first in enumerate(items):
            lines = line_text(source, first)
            if not lines or first.kind in ('case', 'label'):
                continue
            seen = set()
            for node in statement_nodes(first):
                if node.kind not in ('member', 'index', 'binary') or (node.kind == 'binary' and node.operator in BOOLEAN_OPERATORS):
                    continue
                key = normalized(source.source_of(node))
                if key in seen or not is_pure(source, node):
                    continue
                seen.add(key)
                type_text = expression_type(source, node)
                if node.kind == 'binary':
                    type_text = None
                if not type_text or not plain_scalar_type(type_text):
                    continue
                reads = source.node_effects(node)
                matches = []
                for position in range(start_position, len(items)):
                    item = items[position]
                    if item.kind in ('case', 'label'):
                        break
                    item_matches = [candidate for candidate in statement_nodes(item) if candidate.kind == node.kind and normalized(source.source_of(candidate)) == key
                                    and not is_written_place(source, candidate) and source.tokens[candidate.first - 1].text != '&']
                    effects = source.effects(item)
                    if not changes_value(effects, reads):
                        matches.extend(item_matches)
                        continue
                    # A statement that may change the value: only `target = value;` with no call reads every operand before its one store.
                    assignment = assignment_of(item)
                    if item_matches and assignment and not source.node_effects(assignment[1]).call and not changes_value(source.node_effects(assignment[1]), reads) \
                            and all(assignment[1].first <= candidate.first and candidate.last <= assignment[1].last for candidate in item_matches) \
                            and not source.node_effects(assignment[0]).call:
                        matches.extend(item_matches)
                    break
                if len(matches) < 2:
                    continue
                name = fresh_name(source, 'value')
                indent = source.indent_of(first)
                edits = [(lines[0], lines[0], f'{indent}{type_text} {name} = {source.source_of(node)};\n')]
                edits += [(*source.span(match), name) for match in matches]
                if len({edit[0] for edit in edits[1:]}) != len(edits) - 1:
                    continue
                found.append((f'repeat_expression@{line_of(source, first)} {key} named once ({len(matches)} uses)', edits))
    return found


def changes_value(effects, reads):
    """True when code with these effects may change a value with those reads."""
    return bool(effects.writes & reads.reads) or ((effects.memory_write or effects.call) and reads.memory_read) or effects.control


def inline_constant_local(source):
    """A local set from a literal at its declaration and never changed written as the literal at each use (its declaration removed).
    The other direction (naming a literal) is left out: a local that only holds a literal is steering (docs/contributing/exceptions.md),
    and check_source.py --review flags it. Sly 1 toolchain notes: docs/toolchain/loops.md ("Named constants that lose their registers")."""
    found = []
    for name, (statement, declarator) in source.declarations.items():
        if len(statement.parts['declarators']) != 1 or declarator.initializer is None or declarator.dimensions or declarator.stars:
            continue
        value = literal_text(declarator.initializer)
        type_text = source.type_of_local(name)
        if re.search(r'\bregister\b', statement.parts['base']) or source.tokens[declarator.name_token + 1].text in ('asm', '__asm__'):
            continue
        if value is None or not plain_scalar_type(type_text.replace('const ', '')) or assigned_anywhere(source, name) or name in source.address_taken:
            continue
        if any(word in type_text for word in FLOAT_WORDS) and not re.search(r'[.eE]', value):
            value = f'{value}.0f'
        elif not any(word in type_text for word in FLOAT_WORDS) and re.search(r'[.]', value):
            continue
        uses = [index for index in source.uses(name) if index != declarator.name_token]
        lines = line_text(source, statement)
        if not uses or not lines:
            continue
        edits = [(lines[0], lines[1], '')] + [(source.tokens[index].start, source.tokens[index].end, value if not value.startswith('-') else f'({value})') for index in uses]
        found.append((f'inline_constant_local@{line_of(source, statement)} {name} written as {value}', edits))
    return found


def literal_text(node):
    node = strip_parentheses(node)
    if node.kind == 'number':
        return node.operator
    if node.kind == 'unary' and node.operator == '-' and strip_parentheses(node.children[0]).kind == 'number':
        return '-' + strip_parentheses(node.children[0]).operator
    return None


REWRITES = [move_statement, loop_forms, ternary_assignment, early_return, compound_assignment, commute_operands, declaration_placement, const_local,
            pointer_reference, argument_local, switch_if_chain, pointer_walk, element_pointer, reuse_variable, test_in_each_arm, case_order,
            repeat_expression, inline_constant_local]
BY_NAME = {rewrite.__name__: rewrite for rewrite in REWRITES}

FORBIDDEN = [('inline assembly', re.compile(r'\b(?:asm|__asm__|__asm)\b')), ('a register variable', re.compile(r'\bregister\b')),
             ('volatile', re.compile(r'\bvolatile\b')), ('do { } while (0)', re.compile(r'while\s*\(\s*0\s*\)'))]


def forbidden(old_text, new_text):
    """Why a rewrite is refused before it is compiled: more inline asm, register variables, volatile or run-once loops than its parent, or a
    self-assignment. (search_guard.py's check_source findings are checked by the caller.)"""
    reasons = [what for what, pattern in FORBIDDEN if len(pattern.findall(new_text)) > len(pattern.findall(old_text))]
    for match in re.finditer(r'(?<![\w.>])(\w+(?:(?:\.|->)\w+)*)\s*=\s*(\w+(?:(?:\.|->)\w+)*)\s*;', new_text):
        if match.group(1) == match.group(2):
            reasons.append(f'a self-assignment ({match.group(1)})')
    return reasons


def rewrites(text, only=None, function=None):
    """[(label, new text)] of every rewrite of the function in `text` that applies, parses again and passes forbidden()."""
    try:
        source = Source(text, function)
    except (ParseError, RecursionError, IndexError):
        return []
    found, seen = [], {normalized(text)}
    for rewrite in REWRITES:
        if only and rewrite.__name__ not in only:
            continue
        try:
            candidates = rewrite(source)
        except (ParseError, IndexError, KeyError, ValueError, RecursionError, StopIteration, AttributeError, TypeError):
            continue
        for label, edits in candidates:
            if not edits or overlapping(edits):
                continue
            new = apply_edits(text, edits)
            key = normalized(new)
            if key in seen or forbidden(text, new):
                continue
            try:
                Source(new, function)
            except (ParseError, RecursionError, IndexError):
                continue
            seen.add(key)
            found.append((label, new))
    return found


def overlapping(edits):
    ordered = sorted(edits, key=lambda edit: (edit[0], edit[1]))
    return any(first[1] > second[0] for first, second in zip(ordered, ordered[1:]))


def diff(old, new, name='source'):
    """A unified diff of two sources, for the result files and the review."""
    return ''.join(difflib.unified_diff(old.splitlines(True), new.splitlines(True), f'a/{name}', f'b/{name}', n=2))


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('source', nargs='?')
    parser.add_argument('--only', help='comma-separated rewrite names')
    parser.add_argument('--list', action='store_true', help='the rewrites and what each does')
    arguments = parser.parse_args()
    if arguments.list or not arguments.source:
        for rewrite in REWRITES:
            print(f'{rewrite.__name__:24} {" ".join(rewrite.__doc__.split())}')
        return 0
    with open(arguments.source, encoding='utf-8') as handle:
        text = handle.read()
    for label, new in rewrites(text, set(arguments.only.split(',')) if arguments.only else None):
        print(f'== {label}')
        print(diff(text, new))
    return 0


if __name__ == '__main__':
    sys.exit(main())
