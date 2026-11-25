// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
#include "oxa.h"
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
/* slot 49 is SO's Slot49(int), but retail calls it here without an argument: kept as the vtable call, through a view of the object */
struct VTSLOT49 { u8 unknown_0x0[0x188]; short delta; void (*fn)(void *); };
struct SOVIEW { u8 unknown_0x0[0xC]; VTSLOT49 *vptr; };
extern "C" {
void RemoveAloHierarchy(void *);
void RemoveAloFromRenderTree(void *);
void RemoveDlEntry(void *, void *);
extern char B_003E11AC[];
}
extern "C" void func_001F3E00(SO *palo)
{
    VECTOR vector;
    RemoveAloHierarchy(palo);
    RemoveAloFromRenderTree(palo);
    LO *plo = (LO *)palo->dlChild.head;
    if (plo != palo->ploChildEnd) {
        do {
            plo->RemoveAloHierarchy();
            plo = plo->ploNext;
        } while (plo != palo->ploChildEnd);
    }
    if (palo->poxa != 0) {
        if (palo->poxa->owner == palo) {
            VTSLOT49 *vt = ((SOVIEW *)palo)->vptr;
            vt->fn((char *)palo + vt->delta);
            RemoveDlEntry(B_003E11AC, palo->poxa);
        }
    }
}
