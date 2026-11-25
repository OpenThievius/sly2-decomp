#include "dprize.h"
/* the pool object of a clone (class derived from BASIC id 7): the clue it carries sits at 0x100 */
struct POOLO : LO {
    u8 unknown_0x50[0xB0];
    /* 0x100 */ s32 idClue; /* reader: SetCluebottleState */
};
extern "C" {
void *NewEmitter(int);
void SetEmitterUnpositioned(void *, void *);
QW PosLoWorld(DPRIZE *);
void *SpawnSwHitFx(void *, int, QW, void *);
POOLO *PpoolFromLoClone(DPRIZE *);
int FIsBasicDerivedFrom(POOLO *, int);
void SetClueFound(int, int);
void ShowClueBlot(void *);
void SetDprizeDprizes(DPRIZE *, int);
extern char B_003DD490[];
}
void SetCluebottleState(DPRIZE *pbottle, int state)
{
    if (state == pbottle->dprizes)
        return;
    if (state == 1) {
        MSGSINK *owner = (MSGSINK *)pbottle->aoidploB[1].plo;
        if (owner != 0) {
            SINKMSG notice;
            notice.aw[0] = state;
            notice.aw[1] = (int)pbottle;
            owner->Notify(notice.aw);
        } else {
            SetEmitterUnpositioned(NewEmitter(0x29), 0);
        }
        state = 2;
        char *sw = B_003DD490;
        QW pos = PosLoWorld(pbottle);
        SpawnSwHitFx(sw, 0, pos, pbottle);
        pbottle->HandleSpliceEvent(5, 0, 0, 0, 0);
        POOLO *ppool = PpoolFromLoClone(pbottle);
        if (ppool != 0 && FIsBasicDerivedFrom(ppool, 7) != 0) {
            POOLO *pclue = PpoolFromLoClone(pbottle);
            SetClueFound(pclue->idClue, 1);
            pclue->Remove();
            ShowClueBlot(sw);
        }
    }
    SetDprizeDprizes(pbottle, state);
}
