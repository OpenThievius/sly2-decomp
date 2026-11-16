// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
typedef struct { char pad[0x878]; s32 field878; } MpegContext;
u32 func_00252230(MpegContext *, int);
u32 func_00252148(MpegContext *, int);
void func_002544C0(MpegContext *, int);
void func_00254620(MpegContext *);
void func_00254628(MpegContext *);
void func_002540A0(MpegContext *);
void func_00253E68(MpegContext *);
void func_00254678(MpegContext *);
void func_00253FA8(MpegContext *);
void func_00254708(MpegContext *);
void func_00254090(MpegContext *);
void func_002547A0(MpegContext *);
void func_002540B0(MpegContext *);
void func_00254298(MpegContext *);
void func_002542A8(MpegContext *);
typedef struct { void (*handlers[11])(MpegContext *); } MpegHandlerTable;
extern const MpegHandlerTable D_002AC838;
void func_002542B8(MpegContext *context) {
    MpegHandlerTable table = D_002AC838;
    u32 code;
    u32 index;
    func_00254628(context);
    while (func_00252230(context, 0x18) != 1 && context->field878 == 0) {
        func_002544C0(context, 8);
    }
    while ((code = func_00252230(context, 0x20)) == 0x1B5 || code == 0x1B2) {
        if (code == 0x1B5) {
            func_00254620(context);
            index = func_00252148(context, 4);
            index = index > 10 ? 0 : index;
            table.handlers[index](context);
            func_00254628(context);
            while (func_00252230(context, 0x18) != 1 && context->field878 == 0) {
                func_002544C0(context, 8);
            }
        } else {
            func_00254620(context);
            func_00254628(context);
            while (func_00252230(context, 0x18) != 1 && context->field878 == 0) {
                func_002544C0(context, 8);
            }
        }
    }
}
