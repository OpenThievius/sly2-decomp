// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "loot.h"
#include "crfodb.h"
#include "sw.h"
extern "C" SW B_003DD490;
int IdlootCrfodb(CRFODB *);
LOOT *PloLeaseCloneObject(void *, int);
void SelectLootDef(LOOT *, int);
void SetLootState(LOOT *, int);
void Crfodb_SpawnLoot(CRFODB *pguard)
{
    SW *psw;
    if (pguard->ploot == 0) {
        psw = &B_003DD490;
        if (psw->ppool != 0) {
            int idLoot = IdlootCrfodb(pguard);
            if (idLoot != -1) {
                LOOT *ploot = PloLeaseCloneObject(psw->ppool, 0);
                pguard->ploot = ploot;
                if (ploot != 0) {
                    SelectLootDef(ploot, idLoot);
                    pguard->ploot->pguard = pguard;
                    SetLootState(pguard->ploot, 1);
                }
            }
        }
    }
}
