#include "sly2.h"
#include "pathzone.h"
struct LINK { u8 unknown_0x0[0x10]; PATHZONE *region; u8 unknown_0x14[0xC]; char sub[1]; };
#include "phys.h"
#include "so.h"
int FFindDlEntry(void *, void *);
void RemoveDlEntry(void *, void *);
void AppendDlEntry(void *, void *);
void ResetPathzoneQuery(void *, void *);
void func_001F37C8(SO *so, PATHZONE *region)
{
    LINK *link = so->pphys->plink;
    PATHZONE *old = link->region;
    if (old == region) return;
    if (old) {
        if (FFindDlEntry(&old->dlItem, link))
            RemoveDlEntry(&old->dlItem, link);
    }
    if (region) {
        if (FFindDlEntry(&region->dlItem, link)) {
            link->region = region;
            return;
        }
        AppendDlEntry(&region->dlItem, link);
        ResetPathzoneQuery(region, link->sub);
    }
    link->region = region;
}
