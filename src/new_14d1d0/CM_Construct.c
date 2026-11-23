/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

/* The camera manager's constructor, in C: it writes CM's vtable pointer itself, so it uses cplcy.h's C view of CM (the offsets of
   cm.h's). Each policy member is initialised by its class's init function; the last one is a CPLCY whose vtable becomes
   D_002CD378 (ActivateCplookat). */
struct CPLCY *InitCplcy(struct CPLCY *);           /* extern */
void InitCplcyCamobj(struct CPLCY *);              /* extern */
void InitCplook(struct CPLCY *);                   /* extern */
void InitCpman(struct CPLCY *);                    /* extern */
void InitCptn(struct CPLCY *);                     /* extern */
void func_00150728(struct CPLCY *);                /* extern */
void func_00151208(struct CPLCY *);                /* extern */
void func_00151610(struct CPLCY *);                /* extern */
void func_001518C8(struct CPLCY *);                /* extern */
extern void *D_002CA4D0[];
extern void *D_002CD378[];

struct CM *CM_Construct(struct CM *pcm) {
    struct CPLCY *pcplcy;

    pcm->pframe = 0;
    pcplcy = &pcm->cplookat;
    pcm->psidebag = 0;
    pcm->vtable = D_002CA4D0;
    InitCpman(&pcm->cpman);
    InitCptn(&pcm->cptn);
    InitCplook(&pcm->cplook);
    InitCplcyCamobj(&pcm->cplcyCamobj);
    func_00151208(&pcm->cpclose);
    func_00151610(&pcm->cppolicy);
    func_00150728(&pcm->k30cam);
    func_001518C8(&pcm->cpattach);
    InitCplcy(pcplcy);
    pcplcy->vtable = D_002CD378;
    return pcm;
}
