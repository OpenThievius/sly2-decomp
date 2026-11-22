// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
#include "so.h"
#include "murray.h"
struct CARRY { char pad[0x180]; SO *so; };
extern "C" void func_00205D10();
extern "C" int FIsBasicDerivedFrom(void *, int);
void func_001B81B8(MURRAY *m, int f)
{
    func_00205D10();
    if (f) {
        CARRY *c = (CARRY *)m->ploCarried;
        if (c) {
            SO *o = c->so;
            if (o) {
                m->field_0xF1C = o;
                o->Slot21(0);
                if (FIsBasicDerivedFrom(m->field_0xF1C, 0x33)) {
                    STEP *h = (STEP *)m->field_0xF1C;
                    h->Slot87(f);
                }
            }
        }
    } else {
        SO *o = m->field_0xF1C;
        if (o) {
            o->Slot21(1);
            if (FIsBasicDerivedFrom(m->field_0xF1C, 0x33)) {
                STEP *h = (STEP *)m->field_0xF1C;
                h->Slot87(0);
            }
            m->field_0xF1C = 0;
        }
    }
}
