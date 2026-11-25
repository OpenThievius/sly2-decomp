// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "alloc.h"

// A line segment of an edge clipped against geometry: both ends' positions, normals, parameters and indices.
struct LSG {
    QW apos[2];
    QW anormal[2];
    float as[2];
    int unk48;
    int aiface[2];
    void *pedge;
    u8 unknown_0x58[0x8];
};

extern "C" {
void *CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
void *PvAllocStackImpl__Fi(ALLOCREQ *);
void CopyAb__FPvT0Ui(void *, void *, unsigned);
}

static inline ALLOCREQ *Aligned(ALLOCREQ *request)
{
    request->cbAlign = 0x10;
    return request;
}

// Merges two sorted segment lists into alsgResult: mode 0 keeps their union, mode 1 their intersection.
extern "C" int ClsgMergeAlsg(int clsg0, LSG *alsg0, int clsg1, LSG *alsg1, int clsgMax, LSG *alsgResult, int mode)
{
    char frame[0x10];
    ALLOCREQ req;
    LSG *aplsg[2];
    int cIn;
    CStackFrame_Construct(frame);
    req.cb = clsgMax * sizeof(LSG);
    LSG *alsg = (LSG *)PvAllocStackImpl__Fi(Aligned(&req));
    int iend0 = 0;
    int iend1 = 0;
    aplsg[0] = alsg0;
    aplsg[1] = alsg1;
    int fIn = 0;
    LSG *plsgEnd0 = alsg0 + clsg0;
    LSG *plsgEnd1 = alsg1 + clsg1;
    LSG *plsg = alsg;
    switch (mode) {
    case 0:
        cIn = 1;
        break;
    case 1:
        cIn = 2;
        break;
    }
    while (aplsg[0] < plsgEnd0 || aplsg[1] < plsgEnd1) {
        float s0 = (aplsg[0] < plsgEnd0) ? aplsg[0]->as[iend0] : 3.4028235e38f;
        float s1 = (aplsg[1] < plsgEnd1) ? aplsg[1]->as[iend1] : 3.4028235e38f;
        int iend;
        LSG **pplsg;
        if (s0 <= s1) {
            iend = iend0;
            iend0 = 1 - iend;
            pplsg = &aplsg[0];
        } else {
            iend = iend1;
            iend1 = 1 - iend;
            pplsg = &aplsg[1];
        }
        int fInNew = cIn <= iend0 + iend1;
        LSG *plsgSrc = *pplsg;
        if (fInNew != fIn) {
            if (fInNew) {
                plsg->as[0] = plsgSrc->as[0];
                plsg->apos[0] = plsgSrc->apos[0];
                plsg->anormal[0] = plsgSrc->anormal[0];
                plsg->aiface[0] = plsgSrc->aiface[0];
            } else {
                plsg->as[1] = plsgSrc->as[1];
                plsg->apos[1] = plsgSrc->apos[1];
                plsg->anormal[1] = plsgSrc->anormal[1];
                plsg->aiface[1] = plsgSrc->aiface[1];
                plsg++;
                if (plsg - alsg > clsgMax) {
                    plsg--;
                    break;
                }
            }
            fIn = fInNew;
        }
        if (iend == 1)
            *pplsg = plsgSrc + 1;
    }
    int clsg = plsg - alsg;
    CopyAb__FPvT0Ui(alsgResult, alsg, clsg * sizeof(LSG));
    CStackFrame_Destructor(frame, 2);
    return clsg;
}
