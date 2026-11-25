#include "geom.h"
#include "so.h"
extern "C" {
void func_001F6978(SO *so, int oid)
{
    for (int index = 0; index < so->field_0xB8; index++) {
        GLOBENTRY *entry = &so->field_0xC0[index];
        if (entry->oid == oid) {
            GEOM *geom = entry->pgeom;
            entry->grf &= ~0x800;
            if (geom) geom->grf &= ~(1L << 50);
        }
    }
}
}
