#include "sly2.h"
#include "cref.h"
struct MATRIX { QW row[4]; };
struct MATBOX { MATRIX matrix; int cref; };
struct SLOTHEAP;
extern SLOTHEAP B_004521A0;
extern "C" void *PvAllocSlotheapImpl(SLOTHEAP *);

CRef *CRef_SetMatrixPtr(CRef *self, MATRIX *pmatrix)
{
    self->Decref();
    self->m_tagk = TAGK_Matrix;
    MATBOX *pbox = (MATBOX *)PvAllocSlotheapImpl(&B_004521A0);
    pbox->cref = 0;
    self->m_tag.m_pmatrix = (MATRIX4 *)pbox;
    pbox->cref = pbox->cref + 1;
    ((MATBOX *)self->m_tag.m_pmatrix)->matrix = *pmatrix;
    return self;
}
