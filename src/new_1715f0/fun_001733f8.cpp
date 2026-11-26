#include "types.h"
#include "guardspawner.h"
struct Aux { u8 unknown_0x0[0x54]; void *data; };
extern "C" char B_003DD490;
extern "C" void PostLoLoad(GUARDSPAWNER *);
extern "C" void *PloFindSwObject_thunk(void *, int, int, int);
extern "C" void *PloNew(int, int, int, int);
extern "C" void AddScriptRun(void *, int, int, int);
extern "C" void *PvAllocSwClearImpl__Fi(void *);
extern "C" void func_001A6CA8(GUARDSPAWNER *, int);
extern "C" void func_001733F8(GUARDSPAWNER *spawner)
{
    int req[2];
    int index = 0;
    PostLoLoad(spawner);
    for (; index < spawner->count; index++) {
        GUARDSPAWNPOINT *point = &spawner->points[index];
        switch (point->kind) {
        case 1: {
            point->plo = (LO *)PloFindSwObject_thunk(&B_003DD490, 5, point->oid, 0);
            void *aux = PloNew(0x71, 0, 0x2CB, -1);
            AddScriptRun(aux, point->oid, 1, -1);
            void *data = ((Aux *)aux)->data;
            point->ploAux = aux;
            point->auxData = data;
            break;
        }
        case 0:
        case 2:
            point->plo = (LO *)PloFindSwObject_thunk(&B_003DD490, 5, point->oid, 0);
            break;
        }
    }
    req[0] = spawner->cSlotMax * 0x30;
    req[1] = 0x10;
    spawner->slots = (GUARDSPAWNSLOT *)PvAllocSwClearImpl__Fi(req);
    func_001A6CA8(spawner, 1);
    unsigned flags = spawner->grfSw;
    if (!(flags & 1)) {
        *(unsigned *)flags |= 2;
    } else {
        spawner->grfSw = flags | 2;
    }
}
