// SPDX-License-Identifier: GPL-3.0-or-later
typedef void (*CtorFn)(void);
extern CtorFn D_002C85C0[];

/* Runs the constructor list backwards. Its first word is the entry count, or -1 when the list
   is zero-terminated instead. Written as a statement macro, the usual form for one: the extra
   loop level it adds weights the allocator's reference counts the way retail's registers need. */
#define RUN_CONSTRUCTOR_LIST(list)                                      \
    do {                                                                \
        unsigned long count = (unsigned long)(list)[0];                 \
        unsigned int index;                                             \
        if (count == (unsigned long)-1) {                               \
            for (count = 0; (list)[count + 1] != 0; count++) {          \
            }                                                           \
        }                                                               \
        for (index = count; index >= 1; index--) {                      \
            (list)[index]();                                            \
        }                                                               \
    } while (0)

void func_0023B728(void) {
    RUN_CONSTRUCTOR_LIST(D_002C85C0);
}
