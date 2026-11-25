#include "sly2.h"
#include "murray.h"
#include "carry.h"
extern "C" void SetMurrayState(MURRAY *, int);
extern "C" int FAsegaGone(void *);
void UpdateMurrayLift(MURRAY *m)
{
    for (;;) {
        int a = m->field_0x1450;
        switch (a) {
        case -1: break;
        case 1:
            if (m->field_0x1448) {
                if (!m->ploCarried) {
                    SetMurrayState(m, 0);
                } else {
                    u64 bit = (((CARRY *)m->ploCarried)->pso->grfo >> 60) & 1;
                    if (!bit) {
                        SetMurrayState(m, 0);
                        m->ploCarried = 0;
                    }
                }
            }
            break;
        case 2:
            if (FAsegaGone(m->field_0x1030))
                SetMurrayState(m, 5);
            break;
        }
        if (m->field_0x1450 == a || m->field_0x1450 == -1)
            return;
    }
}
