// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly.h"

// the 0x30-byte lead the player's goals pass (JT::PredictLead); only its kind is written here
struct LEAD {
    s32 kind;
    u8 unknown_0x4[0x2C];
};

extern "C" void PredictLoLead(SLY *self, LEAD *plead, float dt);

void PredictSlyLead(SLY *self, LEAD *plead, float dt) {
    PredictLoLead(self, plead, dt);
    switch (self->jts) {
    case 0:
    case 1:
    case 5:
    case 10:
    case 12:
        plead->kind = 1;
        break;
    }
}
