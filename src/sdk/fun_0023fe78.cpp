// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "ehframe.h"
extern "C" {
struct ParseState {
    char *cursor;
    int field4;
    unsigned char unknown_0x8[8];
    unsigned short field10;
    unsigned char unknown_0x12[0xE];
};
struct ParseResult {
    unsigned char unknown_0x0[4];
    int field4;
    unsigned char unknown_0x8[0x292];
    unsigned short field29A;
    unsigned char unknown_0x29C[0x54];
} __attribute__((aligned(8)));
struct ParseWorkspace {
    ParseResult head;
    long long trailer;
};
EHFDE *func_0023F850(unsigned);
unsigned func_0023F938(EHFDE *, ParseState *);
unsigned func_0023FA40(unsigned, ParseResult *, ParseState *, unsigned *);
int func_0023F240(unsigned, int *);
void *memset(void *, int, unsigned);

ParseResult *func_0023FE78(unsigned limit, ParseResult *output)
{
    unsigned deadline;
    int skipped;
    ParseState state;
    ParseWorkspace workspace;
    EHFDE *chunk = func_0023F850(limit);
    if (chunk == 0)
        return 0;
    unsigned cursor = func_0023F938(chunk, &state);
    if (cursor == 0)
        return 0;
    memset(&workspace, 0, sizeof(ParseWorkspace));
    workspace.head.field29A = state.field10;
    EHCIE *header = (EHCIE *)((char *)chunk - (chunk->cieOffset - 4));
    unsigned end = (uptr)((char *)header + header->length + 4);
    workspace.head.field4 = state.field4;
    if (cursor < end) {
        do {
            cursor = func_0023FA40(cursor, &workspace.head, &state, 0);
        } while (cursor < end);
    }
    cursor = (uptr)(chunk + 1);
    if (*state.cursor == 0x7A)
        cursor = func_0023F240(cursor, &skipped) + skipped;
    end = (uptr)((char *)chunk + chunk->length + 4);
    deadline = chunk->pcBegin;
    if (cursor < end) {
        if (limit >= deadline) {
            do {
                cursor = func_0023FA40(cursor, &workspace.head, &state, &deadline);
            } while (cursor < end && limit >= deadline);
        }
    }
    *output = workspace.head;
    return output;
}
}
