#include "loot.h"
extern "C" void HandleLoMessage(LOOT *, int, void *);
extern "C" void SetLootState(LOOT *, int);
extern "C" void HandleLootMessage(LOOT *ploot, int msgid, void *pv)
{
    HandleLoMessage(ploot, msgid, pv);
    switch (msgid) {
    case 4:
        if (ploot->state == 5)
            SetLootState(ploot, 0);
        break;
    case 8:
        if (pv == ploot->psender) {
            switch (ploot->state) {
            case 2: SetLootState(ploot, 4); break;
            case 3: SetLootState(ploot, 1); break;
            }
        }
        break;
    }
}
