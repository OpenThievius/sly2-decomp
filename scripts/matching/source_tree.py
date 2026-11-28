#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""source_tree.py - a small reader of one C or C++ function for the meaning-keeping searches (tsearch.py, sitesearch.py).

  from source_tree import Source
  source = Source(text)                 # the last function definition of the text, or Source(text, function='Name')
  source.body                           # its statements as a tree (Statement), every node with its first and last token
  source.effects(statement)             # what a statement reads and writes: locals by name, memory as a whole, calls

mutate.py and rules.py rewrite lines with regular expressions; a rewrite that reorders or regroups statements then cannot tell whether a
statement reads what another writes (docs/IDEAS.md, "Make the neighbourhood search keep meaning": a store moved past its own use in fmodf,
`a * b + c` commuted into `a * c + b` in asinf). This module parses the function well enough to answer that question conservatively:

  * a local (a parameter or a declared variable whose address is never taken and that is not an array) is tracked by name;
  * everything else (globals, members, anything behind a pointer, an address-taken local) is one memory: any write to it conflicts with any
    read or write of it, since nothing here knows what aliases what;
  * a call reads and writes all memory and is ordered against every other call;
  * a statement that transfers control (return, break, continue, goto, a label, a case) is never moved and never moved across.

It is not a compiler front end. What it cannot parse raises ParseError, and the searches then skip that rewrite instead of guessing."""
import os
import re

HERE = os.path.dirname(os.path.abspath(__file__))
LAB = os.path.normpath(os.path.join(HERE, '..', '..'))

TYPE_KEYWORDS = {'void', 'char', 'short', 'int', 'long', 'float', 'double', 'signed', 'unsigned', 'bool', '_Bool', 'wchar_t'}
QUALIFIERS = {'const', 'volatile', 'static', 'register', 'struct', 'class', 'union', 'enum', 'inline', 'extern', 'typename', 'auto'}
PROJECT_TYPES = {'s8', 'u8', 's16', 'u16', 's32', 'u32', 's64', 'u64', 's128', 'u128', 'f32', 'f64', 'QW', 'M2C_UNK', 'size_t'}
STATEMENT_KEYWORDS = {'if', 'else', 'while', 'do', 'for', 'switch', 'case', 'default', 'return', 'break', 'continue', 'goto', 'sizeof',
                      'new', 'delete', 'this', 'operator', 'true', 'false'}
PUNCTUATORS = sorted(['>>=', '<<=', '...', '->*', '<?=', '>?=', '->', '++', '--', '<<', '>>', '<=', '>=', '==', '!=', '&&', '||', '+=', '-=',
                      '*=', '/=', '%=', '&=', '|=', '^=', '::', '<?', '>?'], key=len, reverse=True)
ASSIGNMENT_OPERATORS = {'=', '+=', '-=', '*=', '/=', '%=', '&=', '|=', '^=', '<<=', '>>=', '<?=', '>?='}
BINARY_PRECEDENCE = {'*': 13, '/': 13, '%': 13, '+': 12, '-': 12, '<<': 11, '>>': 11, '<?': 10, '>?': 10, '<': 9, '>': 9, '<=': 9, '>=': 9,
                     '==': 8, '!=': 8, '&': 7, '^': 6, '|': 5, '&&': 4, '||': 3}
COMMUTATIVE = {'+', '*', '&', '|', '^', '==', '!='}
CONTROL_KINDS = {'return', 'break', 'continue', 'goto', 'label', 'case', 'asm'}


class ParseError(Exception):
    """The text is outside what this reader understands; the caller skips the rewrite."""


class Token:
    __slots__ = ('kind', 'text', 'start', 'end')

    def __init__(self, kind, text, start, end):
        self.kind, self.text, self.start, self.end = kind, text, start, end

    def __repr__(self):
        return f'{self.kind}:{self.text}'


TOKEN_PATTERN = re.compile(r'''
    (?P<space>\s+)
  | (?P<line_comment>//[^\n]*)
  | (?P<block_comment>/\*.*?\*/)
  | (?P<number>(?:0[xX][0-9A-Fa-f]+|\d+\.?\d*(?:[eE][+-]?\d+)?|\.\d+(?:[eE][+-]?\d+)?)[uUlLfF]*)
  | (?P<identifier>[A-Za-z_][A-Za-z_0-9]*)
  | (?P<string>"(?:[^"\\\n]|\\.)*")
  | (?P<character>'(?:[^'\\\n]|\\.)*')
''', re.VERBOSE | re.DOTALL)


def tokenize(text):
    """The tokens of a text; comments, whitespace and preprocessor lines are left out."""
    tokens = []
    position = 0
    line_start = True
    length = len(text)
    while position < length:
        if line_start:
            probe = position
            while probe < length and text[probe] in ' \t':
                probe += 1
            if probe < length and text[probe] == '#':
                while probe < length and (text[probe] != '\n' or text[probe - 1] == '\\'):
                    probe += 1
                position = probe
                continue
        match = TOKEN_PATTERN.match(text, position)
        if match:
            kind = match.lastgroup
            if kind == 'space':
                line_start = '\n' in match.group()
                position = match.end()
                continue
            line_start = False
            if kind not in ('line_comment', 'block_comment'):
                tokens.append(Token(kind, match.group(), match.start(), match.end()))
            position = match.end()
            continue
        line_start = False
        for punctuator in PUNCTUATORS:
            if text.startswith(punctuator, position):
                tokens.append(Token('punctuator', punctuator, position, position + len(punctuator)))
                position += len(punctuator)
                break
        else:
            tokens.append(Token('punctuator', text[position], position, position + 1))
            position += 1
    return tokens


_header_types = None


def header_types():
    """Type names declared in data/matching/include (struct, class, union, enum and typedef names), read once."""
    global _header_types
    if _header_types is None:
        names = set()
        directory = os.path.join(LAB, 'data', 'matching', 'include')
        probe = HERE
        while not os.path.isdir(directory) and os.path.dirname(probe) != probe:  # a copy of the script outside the repository's scripts/
            probe = os.path.dirname(probe)
            directory = os.path.join(probe, 'data', 'matching', 'include')
        for root, _, files in os.walk(directory):
            for name in files:
                if name.endswith('.h'):
                    with open(os.path.join(root, name), encoding='utf-8', errors='replace') as handle:
                        names |= declared_type_names(handle.read())
        _header_types = names
    return _header_types


def declared_type_names(text):
    """Type names a text declares; comments and strings are dropped first (a header comment's "class table" names no type)."""
    text = re.sub(r'//[^\n]*|/\*.*?\*/|"(?:[^"\\\n]|\\.)*"', ' ', text, flags=re.S)
    text = re.sub(r'^\s*#(?:[^\n]*\\\n)*[^\n]*', ' ', text, flags=re.M)  # macro parameters are not types
    names = set(re.findall(r'\b(?:struct|class|union|enum)\s+([A-Za-z_]\w*)', text))
    names |= set(re.findall(r'\btypedef\b[^;{]*?\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*;', text))
    names |= set(re.findall(r'\btypedef\b[^;]*?\(\s*\*\s*([A-Za-z_]\w*)\s*\)', text))
    for match in re.finditer(r'\btypedef\s+(?:struct|union|enum)\s*\w*\s*\{', text):  # typedef struct { ... } NAME;
        depth, index = 1, match.end()
        while index < len(text) and depth:
            depth += {'{': 1, '}': -1}.get(text[index], 0)
            index += 1
        name = re.match(r'\s*([A-Za-z_]\w*)', text[index:])
        if name:
            names.add(name.group(1))
    return names


class Node:
    """An expression: kind (name, number, string, call, index, member, unary, postfix, cast, binary, assign, ternary, comma, sizeof,
    paren), its operator text, its children and its first and last token."""
    __slots__ = ('kind', 'operator', 'children', 'first', 'last')

    def __init__(self, kind, operator, children, first, last):
        self.kind, self.operator, self.children, self.first, self.last = kind, operator, children, first, last

    def walk(self):
        yield self
        for child in self.children:
            if child is not None:
                yield from child.walk()

    def __repr__(self):
        return f'Node({self.kind} {self.operator!r} {self.children})'


class ExpressionParser:
    def __init__(self, source, first, last):
        self.source, self.tokens = source, source.tokens
        self.position, self.last = first, last

    def peek(self, offset=0):
        index = self.position + offset
        return self.tokens[index].text if index <= self.last else None

    def take(self, expected=None):
        if self.position > self.last:
            raise ParseError('expression ends early')
        token = self.tokens[self.position]
        if expected is not None and token.text != expected:
            raise ParseError(f'expected {expected}, found {token.text} at line {self.source.line_number(token.start)}')
        self.position += 1
        return self.position - 1

    def parse_all(self):
        node = self.comma()
        if self.position <= self.last:
            raise ParseError(f'unparsed {self.tokens[self.position].text} at line {self.source.line_number(self.tokens[self.position].start)}')
        return node

    def comma(self):
        node = self.assignment()
        while self.peek() == ',':
            self.take()
            right = self.assignment()
            node = Node('comma', ',', [node, right], node.first, right.last)
        return node

    def assignment(self):
        node = self.ternary()
        if self.peek() in ASSIGNMENT_OPERATORS:
            operator = self.tokens[self.take()].text
            right = self.assignment()
            return Node('assign', operator, [node, right], node.first, right.last)
        return node

    def ternary(self):
        node = self.binary(1)
        if self.peek() == '?':
            self.take()
            middle = self.comma()
            self.take(':')
            right = self.assignment()
            return Node('ternary', '?', [node, middle, right], node.first, right.last)
        return node

    def binary(self, minimum):
        node = self.unary()
        while True:
            operator = self.peek()
            precedence = BINARY_PRECEDENCE.get(operator)
            if precedence is None or precedence < minimum:
                return node
            self.take()
            right = self.binary(precedence + 1)
            node = Node('binary', operator, [node, right], node.first, right.last)

    def is_type_start(self, offset):
        text = self.peek(offset)
        return text is not None and (text in TYPE_KEYWORDS or text in QUALIFIERS or self.source.is_type_name(text))

    def cast_end(self):
        """The index of the `)` closing a cast that starts at the current `(`, or None."""
        index = self.position + 1
        saw_type = False
        while index <= self.last:
            text = self.tokens[index].text
            if text == ')':
                break
            if text in TYPE_KEYWORDS or text in QUALIFIERS or self.source.is_type_name(text):
                saw_type = True
            elif text in ('*', '&', '::', '<', '>', ',') or (self.tokens[index].kind == 'identifier' and text not in self.source.variables_seen):
                pass
            else:
                return None
            index += 1
        if index > self.last or index == self.position + 1:
            return None
        if not saw_type and self.tokens[index - 1].text not in ('*', '&'):
            single = index == self.position + 2 and self.tokens[index - 1].text not in self.source.functions_named()
            if not (single and following_is_operand_start(self.tokens, index + 1, self.last)):
                return None
        following = self.tokens[index + 1] if index + 1 <= self.last else None
        if following is None:
            return None
        if following.kind in ('identifier', 'number', 'string', 'character') or following.text in ('(', '*', '&', '-', '+', '!', '~', '++', '--'):
            return index
        return None

    def unary(self):
        text = self.peek()
        if text in ('-', '+', '!', '~', '*', '&', '++', '--'):
            first = self.take()
            operand = self.unary()
            return Node('unary', text, [operand], first, operand.last)
        if text in ('new', 'delete'):
            first = self.take()
            if self.peek() == '[':
                self.position = self.source.matching(self.position) + 1
            last = first
            while self.position <= self.last and self.peek() not in (',', ';', ')', '?', ':') and BINARY_PRECEDENCE.get(self.peek()) is None and self.peek() not in ASSIGNMENT_OPERATORS:
                if self.peek() in ('(', '['):
                    self.position = self.source.matching(self.position)
                last = self.take()
            return Node('call', text, [], first, last)
        if text == 'sizeof':
            first = self.take()
            if self.peek() == '(':
                close = self.source.matching(self.position)
                self.position = close + 1
                return Node('sizeof', 'sizeof', [], first, close)
            operand = self.unary()
            return Node('sizeof', 'sizeof', [operand], first, operand.last)
        if text == '(':
            close = self.cast_end()
            if close is not None:
                first = self.position
                self.position = close + 1
                operand = self.unary()
                return Node('cast', self.source.text_of(first + 1, close - 1), [operand], first, operand.last)
        return self.postfix(self.primary())

    def primary(self):
        if self.position > self.last:
            raise ParseError('missing operand')
        token = self.tokens[self.position]
        if token.text == '(':
            first = self.take()
            inner = self.comma()
            last = self.take(')')
            return Node('paren', '()', [inner], first, last)
        if token.kind in ('number', 'string', 'character'):
            first = last = self.take()
            while token.kind == 'string' and self.position <= self.last and self.tokens[self.position].kind == 'string':
                last = self.take()
            return Node('string' if token.kind == 'string' else 'number', token.text, [], first, last)
        if token.kind == 'identifier' and token.text not in STATEMENT_KEYWORDS - {'this', 'true', 'false'}:
            first = self.take()
            last = first
            while self.peek() == '::' and self.position + 1 <= self.last and self.tokens[self.position + 1].kind == 'identifier':
                self.take()
                last = self.take()
            return Node('name', self.source.text_of(first, last), [], first, last)
        raise ParseError(f'unexpected {token.text} at line {self.source.line_number(token.start)}')

    def argument(self):
        """One call argument; a type written as a macro argument (`M2C_FIELD(x, s32 *, 4)`) becomes an opaque `type` node."""
        start = self.position
        try:
            return self.assignment()
        except ParseError:
            self.position = start
            while self.position <= self.last and self.peek() not in (',', ')'):
                if self.peek() in ('(', '['):
                    self.position = self.source.matching(self.position)
                self.take()
            if self.position == start:
                raise
            return Node('type', self.source.text_of(start, self.position - 1), [], start, self.position - 1)

    def postfix(self, node):
        while True:
            text = self.peek()
            if text == '(':
                arguments = []
                self.take()
                if self.peek() != ')':
                    arguments.append(self.argument())
                    while self.peek() == ',':
                        self.take()
                        arguments.append(self.argument())
                last = self.take(')')
                node = Node('call', '()', [node] + arguments, node.first, last)
            elif text == '[':
                self.take()
                index = self.comma()
                last = self.take(']')
                node = Node('index', '[]', [node, index], node.first, last)
            elif text in ('.', '->'):
                self.take()
                if self.peek() is None or self.tokens[self.position].kind != 'identifier':
                    raise ParseError('member name expected')
                last = self.take()
                node = Node('member', text, [node, Node('name', self.tokens[last].text, [], last, last)], node.first, last)
            elif text in ('++', '--'):
                last = self.take()
                node = Node('postfix', text, [node], node.first, last)
            else:
                return node


def following_is_operand_start(tokens, index, last):
    """True when the token after a parenthesised name starts an operand that a cast can apply to (a name, a number, a parenthesis)."""
    return index <= last and (tokens[index].kind in ('identifier', 'number') or tokens[index].text == '(')


class Statement:
    """A statement: kind, first and last token, and its parts (for example `condition` as a Node, `then`, `otherwise`, `body` as
    statements, `statements` of a block, `declarators` of a declaration)."""

    def __init__(self, kind, first, last, **parts):
        self.kind, self.first, self.last, self.parts = kind, first, last, parts

    def children(self):
        found = []
        for key in ('init', 'then', 'otherwise', 'body'):
            value = self.parts.get(key)
            if isinstance(value, Statement):
                found.append(value)
        found.extend(self.parts.get('statements', ()))
        return found

    def walk(self):
        yield self
        for child in self.children():
            yield from child.walk()

    def __repr__(self):
        return f'Statement({self.kind} {self.first}-{self.last})'


class Declarator:
    __slots__ = ('name', 'name_token', 'stars', 'dimensions', 'initializer', 'first', 'last')

    def __init__(self, name, name_token, stars, dimensions, initializer, first, last):
        self.name, self.name_token, self.stars, self.dimensions = name, name_token, stars, dimensions
        self.initializer, self.first, self.last = initializer, first, last


class Effects:
    """What a piece of code reads and writes: `reads`/`writes` are tracked locals by name, `memory_read`/`memory_write` everything else,
    `call` a call, `control` a transfer of control (return, break, continue, goto, a label, a case), `side_effect` any write or call."""

    def __init__(self):
        self.reads, self.writes = set(), set()
        self.memory_read = self.memory_write = self.call = self.control = False

    def merge(self, other):
        self.reads |= other.reads
        self.writes |= other.writes
        self.memory_read |= other.memory_read
        self.memory_write |= other.memory_write
        self.call |= other.call
        self.control |= other.control
        return self

    @property
    def side_effect(self):
        return bool(self.writes) or self.memory_write or self.call

    def conflicts(self, other):
        """True when running the two in the other order could give another result."""
        if self.control or other.control:
            return True
        if self.writes & (other.reads | other.writes) or other.writes & self.reads:
            return True
        if (self.memory_write or self.call) and (other.memory_read or other.memory_write or other.call):
            return True
        if (other.memory_write or other.call) and (self.memory_read or self.call):
            return True
        return False


class Function:
    def __init__(self, name, header_first, open_brace, close_brace, parameter_open):
        self.name, self.header_first, self.open_brace, self.close_brace = name, header_first, open_brace, close_brace
        self.parameter_open = parameter_open


class Source:
    """One function of a source text, parsed. `function` picks a definition by name (the plain name before `(`, or `Class::name`);
    the default is the last definition of the text, the near miss itself in our one-function sources."""

    def __init__(self, text, function=None):
        self.text = text
        self.tokens = tokenize(text)
        self.local_types = declared_type_names(text)
        self._matching = self.pair_brackets()
        self.functions = self.find_functions()
        if not self.functions:
            raise ParseError('no function definition')
        chosen = [candidate for candidate in self.functions if function in (None, candidate.name, candidate.name.split('::')[-1])]
        if not chosen:
            raise ParseError(f'no definition of {function}')
        self.function = chosen[-1]
        self.parameters = self.read_parameters()
        self.variables = {name for name, _ in self.parameters}
        self.declarations = {}
        self.variables_seen = set(self.variables)
        self.body = self.parse_block(self.function.open_brace)
        self.variables = self.variables_seen
        self.address_taken = self.find_address_taken()

    # --- tokens and text

    def pair_brackets(self):
        pairs, stack = {}, []
        for index, token in enumerate(self.tokens):
            if token.text in ('(', '[', '{'):
                stack.append(index)
            elif token.text in (')', ']', '}'):
                if not stack:
                    raise ParseError('unbalanced brackets')
                opener = stack.pop()
                pairs[opener], pairs[index] = index, opener
        if stack:
            raise ParseError('unbalanced brackets')
        return pairs

    def matching(self, index):
        try:
            return self._matching[index]
        except KeyError:
            raise ParseError('no matching bracket') from None

    def text_of(self, first, last):
        """The source text from token `first` to token `last`, both included (comments inside kept)."""
        if last < first:
            return ''
        return self.text[self.tokens[first].start:self.tokens[last].end]

    def span(self, item):
        """(start, end) character offsets of a Statement or Node."""
        return self.tokens[item.first].start, self.tokens[item.last].end

    def source_of(self, item):
        start, end = self.span(item)
        return self.text[start:end]

    def line_span(self, statement):
        """(start, end) of the whole lines a statement stands on, the newline included, or None when it shares a line with other code."""
        start, end = self.span(statement)
        line_start = self.text.rfind('\n', 0, start) + 1
        line_end = self.text.find('\n', end)
        line_end = len(self.text) if line_end < 0 else line_end + 1
        if self.text[line_start:start].strip() or re.sub(r'//.*|/\*.*?\*/', '', self.text[end:line_end]).strip():
            return None
        return line_start, line_end

    def indent_of(self, statement):
        start = self.tokens[statement.first].start
        line_start = self.text.rfind('\n', 0, start) + 1
        prefix = self.text[line_start:start]
        return prefix if not prefix.strip() else re.match(r'\s*', prefix).group()

    def line_number(self, offset):
        return self.text.count('\n', 0, offset) + 1

    def is_type_name(self, text):
        return text in PROJECT_TYPES or text in self.local_types or text in header_types()

    # --- functions

    def find_functions(self):
        found = []
        depth = 0
        index = 0
        transparent = []
        while index < len(self.tokens):
            token = self.tokens[index]
            if token.text == '{':
                before = self.tokens[index - 1] if index else None
                if before is not None and before.kind == 'string' or (before is not None and before.kind == 'identifier' and index >= 2 and self.tokens[index - 2].text == 'namespace'):
                    transparent.append(depth)
                    index += 1
                    continue
                if depth == (transparent[-1] if transparent else 0):
                    definition = self.function_at(index)
                    if definition:
                        found.append(definition)
                        index = definition.close_brace + 1
                        continue
                depth += 1
            elif token.text == '}':
                if transparent and transparent[-1] == depth:
                    transparent.pop()
                else:
                    depth -= 1
            index += 1
        return found

    def function_at(self, brace):
        """A Function when the `{` at `brace` opens a function body, else None."""
        index = brace - 1
        while index >= 0 and self.tokens[index].text in ('const', 'throw'):
            index -= 1
        if index < 0 or self.tokens[index].text != ')':
            return None
        opener = self.matching(index)
        name_index = opener - 1
        if name_index < 0 or self.tokens[name_index].kind != 'identifier' or self.tokens[name_index].text in STATEMENT_KEYWORDS:
            return None
        name = self.tokens[name_index].text
        first = name_index
        while first >= 2 and self.tokens[first - 1].text == '::' and self.tokens[first - 2].kind == 'identifier':
            first -= 2
            name = self.tokens[first].text + '::' + name
        header = first
        while header > 0 and self.tokens[header - 1].text not in (';', '}', '{', ')') and self.tokens[header - 1].kind != 'string':
            header -= 1
        return Function(name, header, brace, self.matching(brace), opener)

    def read_parameters(self):
        """[(name, type text)] of the target function's parameters (unnamed ones left out)."""
        opener = self.function.parameter_open
        closer = self.matching(opener)
        parameters = []
        start = opener + 1
        depth = 0
        for index in range(opener + 1, closer + 1):
            text = self.tokens[index].text
            if text in ('(', '['):
                depth += 1
            elif text in (')', ']') and index != closer:
                depth -= 1
            if (text == ',' and depth == 0) or index == closer:
                part = list(range(start, index))
                names = [position for position in part if self.tokens[position].kind == 'identifier']
                if names and len(part) > 1:
                    name_position = names[-1]
                    name = self.tokens[name_position].text
                    if not (name in TYPE_KEYWORDS or self.is_type_name(name)):
                        type_text = (self.text_of(part[0], name_position - 1) + ' ' + self.text_of(name_position + 1, part[-1])).strip()
                        parameters.append((name, type_text))
                start = index + 1
        return parameters

    # --- statements

    def parse_block(self, brace):
        closer = self.matching(brace)
        statements = []
        index = brace + 1
        while index < closer:
            statement = self.parse_statement(index, closer)
            statements.append(statement)
            index = statement.last + 1
        return Statement('block', brace, closer, statements=statements)

    def end_of(self, index, limit):
        """The index of the `;` that ends the simple statement starting at `index`."""
        while index < limit:
            text = self.tokens[index].text
            if text in ('(', '[', '{'):
                index = self.matching(index) + 1
                continue
            if text == ';':
                return index
            index += 1
        raise ParseError('statement without ;')

    def condition_at(self, index):
        """(Node, index of the closing parenthesis) for `( expression )` starting at `index`."""
        if self.tokens[index].text != '(':
            raise ParseError('( expected')
        closer = self.matching(index)
        return self.expression(index + 1, closer - 1), closer

    def parse_statement(self, index, limit):
        token = self.tokens[index]
        text = token.text
        if text == '{':
            return self.parse_block(index)
        if text == ';':
            return Statement('empty', index, index)
        if text == 'if':
            condition, closer = self.condition_at(index + 1)
            then = self.parse_statement(closer + 1, limit)
            otherwise = None
            if then.last + 1 < limit and self.tokens[then.last + 1].text == 'else':
                otherwise = self.parse_statement(then.last + 2, limit)
            return Statement('if', index, (otherwise or then).last, condition=condition, then=then, otherwise=otherwise)
        if text == 'while':
            condition, closer = self.condition_at(index + 1)
            body = self.parse_statement(closer + 1, limit)
            return Statement('while', index, body.last, condition=condition, body=body)
        if text == 'do':
            body = self.parse_statement(index + 1, limit)
            if self.tokens[body.last + 1].text != 'while':
                raise ParseError('do without while')
            condition, closer = self.condition_at(body.last + 2)
            if self.tokens[closer + 1].text != ';':
                raise ParseError('do-while without ;')
            return Statement('do', index, closer + 1, condition=condition, body=body)
        if text == 'for':
            opener = index + 1
            closer = self.matching(opener)
            first_semicolon = self.end_of(opener + 1, closer)
            second_semicolon = self.end_of(first_semicolon + 1, closer)
            init = self.parse_statement(opener + 1, first_semicolon + 1) if first_semicolon > opener + 1 else None
            condition = self.expression(first_semicolon + 1, second_semicolon - 1) if second_semicolon > first_semicolon + 1 else None
            step = self.expression(second_semicolon + 1, closer - 1) if closer > second_semicolon + 1 else None
            body = self.parse_statement(closer + 1, limit)
            return Statement('for', index, body.last, init=init, condition=condition, step=step, body=body)
        if text == 'switch':
            condition, closer = self.condition_at(index + 1)
            body = self.parse_statement(closer + 1, limit)
            return Statement('switch', index, body.last, condition=condition, body=body)
        if text == 'case':
            colon = index + 1
            while colon < limit and self.tokens[colon].text != ':':
                colon += 1
            return Statement('case', index, colon, value=self.expression(index + 1, colon - 1))
        if text == 'default' and self.tokens[index + 1].text == ':':
            return Statement('case', index, index + 1, value=None)
        if text in ('asm', '__asm__', '__asm'):
            return Statement('asm', index, self.end_of(index, limit))
        if text in ('break', 'continue'):
            return Statement(text, index, self.end_of(index, limit))
        if text == 'goto':
            return Statement('goto', index, self.end_of(index, limit), target=self.tokens[index + 1].text)
        if text == 'return':
            end = self.end_of(index, limit)
            value = self.expression(index + 1, end - 1) if end > index + 1 else None
            return Statement('return', index, end, value=value)
        if token.kind == 'identifier' and self.tokens[index + 1].text == ':' and text not in STATEMENT_KEYWORDS:
            return Statement('label', index, index + 1, name=text)
        end = self.end_of(index, limit)
        if self.looks_like_declaration(index, end):
            return self.parse_declaration(index, end)
        return Statement('expression', index, end, expression=self.expression(index, end - 1))

    def looks_like_declaration(self, index, end):
        tokens = self.tokens
        position = index
        saw_type = False
        while position < end and (tokens[position].text in QUALIFIERS or tokens[position].text in TYPE_KEYWORDS):
            saw_type = True
            position += 1
        if position >= end:
            return False
        if tokens[position].kind == 'identifier' and not saw_type:
            name = tokens[position].text
            following = tokens[position + 1].text if position + 1 < end else ';'
            if name in self.variables_seen or name in STATEMENT_KEYWORDS:
                return False
            if following == '::' or following == '<':
                return self.is_type_name(name)
            if following in ('*', '&'):
                if self.is_type_name(name):
                    return True
                probe = position + 1
                while probe < end and tokens[probe].text in ('*', '&'):
                    probe += 1
                # `T *name = ...;` with an unknown T: as an expression it would assign to a product, which is not C.
                return probe + 1 <= end and tokens[probe].kind == 'identifier' and tokens[probe + 1].text in ('=', ';', ',', '[')
            return tokens[position + 1].kind == 'identifier' if position + 1 < end else False
        return saw_type

    def parse_declaration(self, index, end):
        tokens = self.tokens
        position = index
        while tokens[position].text in QUALIFIERS or tokens[position].text in TYPE_KEYWORDS:
            position += 1
        if tokens[position].text == '{' or (tokens[position].kind == 'identifier' and tokens[position + 1].text == '{'):
            position = self.matching(position if tokens[position].text == '{' else position + 1) + 1
        elif tokens[position].kind == 'identifier' and not (tokens[position - 1].text in TYPE_KEYWORDS and position > index and tokens[position + 1].text in (';', '=', ',', '[', '(')):
            if position == index or tokens[position - 1].text in QUALIFIERS:
                position += 1
                while tokens[position].text == '::' or (tokens[position].text == '<'):
                    if tokens[position].text == '<':
                        depth = 0
                        while True:
                            depth += {'<': 1, '>': -1}.get(tokens[position].text, 0)
                            position += 1
                            if depth == 0:
                                break
                    else:
                        position += 2
        base_last = position - 1
        declarators = []
        while position < end:
            first = position
            stars = ''
            while tokens[position].text in ('*', '&', 'const'):
                stars += tokens[position].text if tokens[position].text != 'const' else ' const '
                position += 1
            if tokens[position].kind != 'identifier':
                raise ParseError(f'declarator name expected at line {self.line_number(tokens[position].start)}')
            name_token = position
            name = tokens[position].text
            position += 1
            dimensions = ''
            while tokens[position].text in ('__attribute__', 'asm', '__asm__'):
                position = self.matching(position + 1) + 1
            while tokens[position].text == '[':
                closer = self.matching(position)
                dimensions += self.text_of(position, closer)
                position = closer + 1
            initializer = None
            while tokens[position].text in ('__attribute__', 'asm', '__asm__'):
                position = self.matching(position + 1) + 1
            if tokens[position].text == '=':
                start = position + 1
                depth = 0
                while position < end:
                    text = tokens[position].text
                    if text in ('(', '[', '{'):
                        position = self.matching(position)
                    elif text == ',' and depth == 0:
                        break
                    position += 1
                if tokens[start].text != '{':
                    initializer = self.expression(start, position - 1)
                else:
                    initializer = Node('braces', '{}', [], start, position - 1)
            elif tokens[position].text == '(':
                closer = self.matching(position)
                initializer = Node('construct', '()', [], position, closer)
                position = closer + 1
            declarators.append(Declarator(name, name_token, stars.strip(), dimensions, initializer, first, position - 1))
            self.variables_seen.add(name)
            if tokens[position].text == ',':
                position += 1
            elif position != end:
                raise ParseError(f'unexpected token in a declaration at line {self.line_number(tokens[position].start)}')
        statement = Statement('declaration', index, end, base=self.text_of(index, base_last), base_last=base_last, declarators=declarators)
        for declarator in declarators:
            self.declarations[declarator.name] = (statement, declarator)
        return statement

    def expression(self, first, last):
        if last < first:
            raise ParseError('empty expression')
        return ExpressionParser(self, first, last).parse_all()

    # --- names and effects

    def find_address_taken(self):
        taken = set()
        for index in range(self.function.open_brace, self.function.close_brace):
            token = self.tokens[index]
            if token.text == '&' and self.tokens[index + 1].kind == 'identifier':
                previous = self.tokens[index - 1]
                if previous.kind in ('identifier', 'number') or previous.text in (')', ']'):
                    continue
                taken.add(self.tokens[index + 1].text)
        for name, (_, declarator) in self.declarations.items():
            if declarator.dimensions:
                taken.add(name)
        for name, type_text in self.parameters:
            if '&' in type_text:
                taken.add(name)
        for name, (statement, declarator) in self.declarations.items():
            if '&' in declarator.stars:
                taken.add(name)
        return taken

    def tracked(self, name):
        """True for a local tracked by name: a parameter or declared variable, never address-taken, not an array."""
        return name in self.variables and name not in self.address_taken

    def type_of_local(self, name):
        """The declared type of a local or parameter as text (`int`, `VECTOR *`), or None."""
        if name in self.declarations:
            statement, declarator = self.declarations[name]
            base = re.sub(r'\b(static|register|extern|inline)\b\s*', '', statement.parts['base']).strip()
            return (base + (' ' + declarator.stars if declarator.stars else '')).strip()
        for parameter, type_text in self.parameters:
            if parameter == name:
                return type_text
        return None

    def node_effects(self, node, effects=None):
        effects = effects if effects is not None else Effects()
        if node is None:
            return effects
        kind = node.kind
        if kind == 'name':
            if self.tracked(node.operator):
                effects.reads.add(node.operator)
            elif node.operator not in ('true', 'false', 'this') and node.operator not in self.functions_named():
                effects.memory_read = True
        elif kind == 'assign':
            self.write_effects(node.children[0], effects, node.operator != '=')
            self.node_effects(node.children[1], effects)
        elif kind in ('postfix',) or (kind == 'unary' and node.operator in ('++', '--')):
            self.write_effects(node.children[0], effects, True)
        elif kind == 'call' and node.children and node.children[0].kind == 'name' and node.children[0].operator == 'M2C_FIELD':
            effects.memory_read = True
            self.node_effects(node.children[1], effects)
        elif kind == 'call':
            effects.call = effects.memory_read = effects.memory_write = True
            callee = node.children[0] if node.children else None
            if callee is not None and callee.kind != 'name':
                self.node_effects(callee, effects)
            for argument in node.children[1:]:
                self.node_effects(argument, effects)
        elif kind == 'member':
            base = node.children[0]
            if node.operator == '.' and base.kind == 'name' and self.tracked(base.operator):
                effects.reads.add(base.operator)
            else:
                effects.memory_read = True
                self.node_effects(base, effects)
        elif kind == 'index' or (kind == 'unary' and node.operator == '*'):
            effects.memory_read = True
            for child in node.children:
                self.node_effects(child, effects)
        elif kind == 'unary' and node.operator == '&':
            operand = node.children[0]
            if operand.kind != 'name':
                self.address_effects(operand, effects)
        elif kind in ('sizeof', 'type'):
            pass
        else:
            for child in node.children:
                self.node_effects(child, effects)
        return effects

    def address_effects(self, node, effects):
        """`&x->m`, `&a[i]`: the address is computed, nothing is read through it."""
        if node.kind == 'member':
            if node.operator == '->':
                self.node_effects(node.children[0], effects)
            else:
                self.address_effects(node.children[0], effects)
        elif node.kind == 'index':
            base = node.children[0]
            if base.kind == 'name' and base.operator in self.declarations and self.declarations[base.operator][1].dimensions:
                pass
            else:
                self.node_effects(base, effects)
            self.node_effects(node.children[1], effects)
        elif node.kind == 'paren':
            self.address_effects(node.children[0], effects)
        else:
            self.node_effects(node, effects)

    def write_effects(self, target, effects, also_read):
        if target.kind == 'paren':
            return self.write_effects(target.children[0], effects, also_read)
        if target.kind == 'name' and self.tracked(target.operator):
            effects.writes.add(target.operator)
            if also_read:
                effects.reads.add(target.operator)
            return
        if target.kind == 'member' and target.operator == '.' and target.children[0].kind == 'name' and self.tracked(target.children[0].operator):
            effects.writes.add(target.children[0].operator)
            effects.reads.add(target.children[0].operator)
            return
        effects.memory_write = True
        if also_read:
            effects.memory_read = True
        if target.kind == 'name':
            return
        if target.kind == 'call' and target.children and target.children[0].kind == 'name' and target.children[0].operator == 'M2C_FIELD':
            self.node_effects(target.children[1], effects)
            return
        if target.kind == 'member':
            if target.operator == '->':
                self.node_effects(target.children[0], effects)
            else:
                self.address_effects(target.children[0], effects)
        elif target.kind == 'index':
            self.address_effects(target, effects)
        elif target.kind == 'unary' and target.operator == '*':
            self.node_effects(target.children[0], effects)
        else:
            self.node_effects(target, effects)

    def functions_named(self):
        if not hasattr(self, '_function_names'):
            names = {definition.name.split('::')[-1] for definition in self.functions}
            names |= set(re.findall(r'\b([A-Za-z_]\w*)\s*\([^;{}()]*(?:\([^()]*\)[^;{}()]*)*\)\s*(?:const\s*)?;', self.text))
            self._function_names = names
        return self._function_names

    def effects(self, statement):
        """The Effects of a statement and everything inside it."""
        effects = Effects()
        kind = statement.kind
        if kind in CONTROL_KINDS:
            effects.control = True
        if kind == 'declaration':
            for declarator in statement.parts['declarators']:
                if self.tracked(declarator.name):
                    effects.writes.add(declarator.name)
                else:
                    effects.memory_write = True
                if declarator.initializer is not None:
                    if declarator.initializer.kind in ('braces', 'construct'):
                        effects.call = effects.memory_read = effects.memory_write = True
                    else:
                        self.node_effects(declarator.initializer, effects)
            if re.search(r'\bstatic\b', statement.parts['base']):
                effects.control = True
            return effects
        for key in ('condition', 'step', 'expression', 'value'):
            node = statement.parts.get(key)
            if isinstance(node, Node):
                self.node_effects(node, effects)
        for child in statement.children():
            effects.merge(self.effects(child))
        return effects

    def names_in(self, item):
        """Every identifier token text between an item's first and last token."""
        return {self.tokens[index].text for index in range(item.first, item.last + 1) if self.tokens[index].kind == 'identifier'}

    def uses(self, name, first=None, last=None):
        """Token indexes where `name` appears as a plain identifier (not after `.`/`->`/`::`) inside the function, or in [first, last]."""
        first = self.function.open_brace if first is None else first
        last = self.function.close_brace if last is None else last
        found = []
        for index in range(first, last + 1):
            token = self.tokens[index]
            if token.kind == 'identifier' and token.text == name and self.tokens[index - 1].text not in ('.', '->', '::'):
                found.append(index)
        return found

    def parent_map(self):
        """{id(statement): (parent statement, position in the parent's list or key)} over the function body."""
        parents = {}
        for statement in self.body.walk():
            for key in ('init', 'then', 'otherwise', 'body'):
                value = statement.parts.get(key)
                if isinstance(value, Statement):
                    parents[id(value)] = (statement, key)
            for position, child in enumerate(statement.parts.get('statements', ())):
                parents[id(child)] = (statement, position)
        return parents

    def blocks(self):
        """Every block of the function, the body first."""
        return [statement for statement in self.body.walk() if statement.kind == 'block']

    def loops_around(self, token_index):
        return [statement for statement in self.body.walk() if statement.kind in ('while', 'do', 'for') and statement.first <= token_index <= statement.last]


def apply_edits(text, edits):
    """Apply [(start, end, replacement)] (character offsets in `text`, not overlapping)."""
    for start, end, replacement in sorted(edits, key=lambda edit: (edit[0], edit[1]), reverse=True):
        text = text[:start] + replacement + text[end:]
    return text


def parenthesize(source, node):
    """The node's text, in parentheses unless it is already a primary expression."""
    text = source.source_of(node)
    if node.kind in ('name', 'number', 'string', 'paren', 'call', 'index', 'member', 'postfix'):
        return text
    return f'({text})'


def strip_parentheses(node):
    while node.kind == 'paren':
        node = node.children[0]
    return node


def normalized(text):
    """A text with comments and whitespace runs folded: two rewrites that differ only in layout are one candidate."""
    return re.sub(r'\s+', ' ', re.sub(r'//[^\n]*|/\*.*?\*/', '', text, flags=re.S)).strip()
