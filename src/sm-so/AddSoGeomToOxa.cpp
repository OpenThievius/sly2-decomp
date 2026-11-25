#include "sly2.h"
#include "so.h"
#include "oxa.h"
#include "geom.h"
extern "C" {
void EnsureSoOxa(SO *);
int FFindDlEntry(DL *, GEOM *);
void AppendDlEntry(DL *, GEOM *);
void func_001F4BF8(SO *);
void func_001F38A8(GEOM *);
void func_001F5078(SO *);
}

extern "C" void AddSoGeomToOxa(SO *pso, GEOM *pgeom)
{
    EnsureSoOxa(pso);
    if (FFindDlEntry(&pso->poxa->dlGeom, pgeom)) {
        return;
    }
    AppendDlEntry(&pso->poxa->dlGeom, pgeom);
    pgeom->generationBound = -1;
    XF *pxf = pgeom->pxf;
    pgeom->matWorld = pxf->matWorld;
    pgeom->generationMat = pxf->generation;
    func_001F4BF8(pso);
    func_001F38A8(pgeom);
    if (!pso->FIsLocked()) {
        func_001F5078(pso);
    }
}
