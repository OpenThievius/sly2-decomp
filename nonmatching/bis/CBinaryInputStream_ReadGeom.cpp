#include "alloc.h"
#include "bis.h"
struct GEOMEDGE {
    s16 ivertA;
    s16 ivertB;
    s16 iplane;
    u16 iplaneOther;
    GEOMEDGE *pedgePrev;
    GEOMEDGE *pedgeNext;
};
struct GEOMPLANE {
    float normal[3];
    s32 dist;
    GEOMEDGE *pedgeFirst;
    GEOMEDGE *pedgeList;
    s32 pad18;
    s32 iface;
};
struct GEOM {
    s32 cvert;
    QW *avert;
    s32 cplane;
    GEOMPLANE *aplane;
    s32 cedge;
    GEOMEDGE *aedge;
};
extern "C" {
void *PvAllocSwImpl__Fi(ALLOCREQ *);
void *PvAllocSwClearImpl__Fi(ALLOCREQ *);
void BuildPlane(GEOMPLANE *pplane, QW pos0, QW pos1, QW pos2);
}
extern "C" void CBinaryInputStream_ReadGeom(CBinaryInputStream *pbis, GEOM *pgeom)
{
    union {
        ALLOCREQ allocreq;
        int aivert[3];
    } scratch;
#define allocreq scratch.allocreq
    int ivert = 0;
    int cvert = pbis->U16Read();
    allocreq.cb = cvert * 0x10;
    allocreq.cbAlign = 0x10;
    pgeom->cvert = cvert;
    pgeom->avert = (QW *)PvAllocSwImpl__Fi(&allocreq);
    if (pgeom->cvert > 0) {
        do {
            pbis->ReadVector((VECTOR *)(pgeom->avert + ivert));
            ivert++;
        } while (ivert < pgeom->cvert);
    }
    pgeom->cplane = pbis->U16Read();
    allocreq.cb = pgeom->cplane << 5;
    allocreq.cbAlign = 0x10;
    pgeom->aplane = (GEOMPLANE *)PvAllocSwClearImpl__Fi(&allocreq);
    int cedge = pbis->U16Read();
    allocreq.cbAlign = 0x10;
    pgeom->cedge = cedge;
    allocreq.cb = cedge * 0x10;
    GEOMEDGE *pedge;
    pedge = pgeom->aedge = (GEOMEDGE *)PvAllocSwClearImpl__Fi(&allocreq);
    int iplane;
    for (iplane = 0; iplane < pgeom->cplane; iplane++) {
        {
            GEOMPLANE *pplane = pgeom->aplane + iplane;
            scratch.aivert[0] = pbis->U16Read();
            scratch.aivert[1] = pbis->U16Read();
            scratch.aivert[2] = pbis->U16Read();
            QW *avert = pgeom->avert;
            BuildPlane(pplane, avert[scratch.aivert[0]], avert[scratch.aivert[1]], avert[scratch.aivert[2]]);
            pplane->iface = scratch.aivert[0];
            for (int ifloat = 3; ifloat >= 0; ifloat--)
                pbis->F32Read();
            int cedgePlane = pbis->U8Read();
            for (int iedge = 0; iedge < cedgePlane; iedge++) {
                GEOMEDGE *pedgeNew = pedge;
                pedge++;
                pedgeNew->ivertA = pbis->U16Read();
                int ivertB = pbis->U16Read();
                pedgeNew->iplane = iplane;
                pedgeNew->ivertB = ivertB;
                pedgeNew->iplaneOther = pbis->U16Read();
                if (iedge == 0)
                    pplane->pedgeFirst = pedgeNew;
                else
                    pedgeNew[-1].pedgePrev = pedgeNew;
                GEOMPLANE *pplaneOther = pgeom->aplane + pedgeNew->iplaneOther;
                pedgeNew->pedgeNext = pplaneOther->pedgeList;
                pplaneOther->pedgeList = pedgeNew;
            }
        }
    }
}
