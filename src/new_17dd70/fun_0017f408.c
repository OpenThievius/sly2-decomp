/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

struct BASIC;
struct LO;
struct SW;

s32 FIsBasicDerivedFrom(struct BASIC *pbasic, s32 cid);
struct LO *PloFindSwObject_thunk(struct SW *psw, s32 grffso, s32 oid, struct LO *ploContext);
extern struct SW B_003DD490;

/* ResolveOidEntries: finds the object of each entry's oid in the world and keeps it as the animation (class 0x6D) or the SM (class 0x6F) */
void func_0017F408(struct LO *ploContext, s32 centry, struct ANIMENTRY *aentry) {
    struct ANIMENTRY *pentry;
    s32 cremaining;
    struct LO *plo;

    if (centry > 0) {
        pentry = aentry;
        cremaining = centry;
        do {
            if (pentry->oid != -1) {
                plo = PloFindSwObject_thunk(&B_003DD490, 4, pentry->oid, ploContext);
                if (plo != 0) {
                    if (FIsBasicDerivedFrom((struct BASIC *)plo, 0x6D) != 0) {
                        pentry->aseg = plo;
                    } else if (FIsBasicDerivedFrom((struct BASIC *)plo, 0x6F) != 0) {
                        pentry->sm = plo;
                    }
                }
            }
            cremaining -= 1;
            pentry += 1;
        } while (cremaining != 0);
    }
}
