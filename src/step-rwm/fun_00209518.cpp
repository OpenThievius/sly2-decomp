// SPDX-License-Identifier: GPL-3.0-or-later
/* a reference to an object by kind (0 the object, 1 to 3 a holder): which pointer func_00209518 picks depends on the kind */
struct OBJHOLDER { char unknown_0x0[0x24]; char *field_0x24; char unknown_0x28[0x8]; char *field_0x30; char unknown_0x34[0x4]; char *field_0x38; };
struct OBJREF { int kind; char unknown_0x4[0x4]; OBJHOLDER *pholder; };
extern "C" {
char *func_00209518(OBJREF *pref) {
    switch (pref->kind) {
    case 0: return (char *)pref->pholder;
    case 1: return pref->pholder->field_0x30;
    case 2: return pref->pholder->field_0x38;
    case 3: return pref->pholder->field_0x24;
    }
    return 0;
}
}
