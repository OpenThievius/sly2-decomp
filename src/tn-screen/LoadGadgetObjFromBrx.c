/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

/* the physics block (phys.h's PHYS) of a gadget object, up to the two floats LoadGadgetObjFromBrx sets */
struct GADGETPHYS {
    u8 unknown_0x0[0xD4];
    f32 field_0xD4; /* set to 2.0 */
    f32 field_0xD8; /* set to 2.0 */
};

/* the gadget object (gadgetobj.h's GADGETOBJ, an SO) as LoadGadgetObjFromBrx reads it: SO::pphys (a local view: gadgetobj.h's C view
   does not declare SO's fields, and PHYS's two words have this one reader) */
struct GADGETOBJLOADVIEW {
    u8 unknown_0x0[0xE8];
    struct GADGETPHYS *pphys; /* SO::pphys */
};

void CSo_LoadFromBrx(struct GADGETOBJLOADVIEW *);
void LoadGadgetObjFromBrx(struct GADGETOBJLOADVIEW *gadget) {
    CSo_LoadFromBrx(gadget);
    if (gadget->pphys != 0) {
        gadget->pphys->field_0xD4 = 2.0f;
        gadget->pphys->field_0xD8 = 2.0f;
    }
}
