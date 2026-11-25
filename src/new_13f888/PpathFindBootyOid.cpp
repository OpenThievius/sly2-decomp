// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "alloc.h"

struct SAVEVARREC
{
    short symid;
    signed char savek;
    unsigned char cElement;
    unsigned short ib;
    unsigned short irecChild;
    unsigned short irecNext;
};

struct SAVEVARS
{
    int crec;
    SAVEVARREC *arec;
    u8 symtab[0]; /* the symbol table follows the save variables */
};

struct SAVEPATH
{
    int csym;
    short *asymid;
};

struct SAVEVARLOC
{
    SAVEVARREC *prec;
    int iElement;
};

struct SWD
{
    char field0[0x3A18];
    SAVEVARS savevars;
};

void CopyAb(void *destination, void *source, unsigned int count);

extern "C" {
int FFindSaveVar(SAVEVARS *psavevars, SAVEPATH *ppath, SAVEVARLOC *psavevarloc);
CRef RefGetSaveValue(SAVEVARS *psavevars, SAVEPATH *ppath, char *pbBase);
int SymidFindSymtab(void *symtab, const char *name);
void *PvAllocStackImpl__Fi(ALLOCREQ *);
extern SWD B_003DD490;
extern char B_003D4A60[];
extern const char RO_002A4D88[];
extern const char RO_002A4D90[];
extern const char RO_002A4D98[];
extern const char RO_002A4DA0[];
}

// The symbol table follows the save variables.
static inline void *SymtabOfSave(SAVEVARS *psavevars)
{
    return psavevars->symtab;
}

// The game's save variables; an out-of-line copy is at 0x2581C0.
static inline CRef RefGetGameSaveValue(SAVEPATH *ppath, char *pbBase)
{
    return RefGetSaveValue(&B_003DD490.savevars, ppath, pbBase);
}

static inline ALLOCREQ *Aligned(ALLOCREQ *request)
{
    request->cbAlign = 0x10;
    return request;
}

extern "C" SAVEPATH *PpathFindBootyOid(int oid)
{
    short asym[7];
    SAVEPATH path;
    SAVEVARLOC locEpisode;
    SAVEVARLOC locLevel;
    path.csym = 0;
    path.asymid = asym;
    asym[0] = SymidFindSymtab(SymtabOfSave(&B_003DD490.savevars), RO_002A4D88);
    asym[2] = SymidFindSymtab(SymtabOfSave(&B_003DD490.savevars), RO_002A4D90);
    asym[4] = SymidFindSymtab(SymtabOfSave(&B_003DD490.savevars), RO_002A4D98);
    asym[5] = SymidFindSymtab(SymtabOfSave(&B_003DD490.savevars), RO_002A4DA0);
    path.csym = 1;
    FFindSaveVar(&B_003DD490.savevars, &path, &locEpisode);
    SAVEVARREC *precLevel;
    SAVEVARREC *precBooty;
    for (unsigned irecLevel = locEpisode.prec->irecChild; irecLevel != 0; irecLevel = precLevel->irecNext) {
        precLevel = &B_003DD490.savevars.arec[irecLevel];
        path.csym = 3;
        asym[1] = precLevel->symid;
        if (!FFindSaveVar(&B_003DD490.savevars, &path, &locLevel))
            continue;
        for (unsigned irecBooty = locLevel.prec->irecChild; irecBooty != 0; irecBooty = precBooty->irecNext) {
            precBooty = &B_003DD490.savevars.arec[irecBooty];
            asym[3] = precBooty->symid;
            CRef ref;
            ref.m_tagk = TAGK_Nil;
            for (int index = 0; index < 15; index++) {
                asym[6] = index;
                path.csym = 7;
                ref = RefGetGameSaveValue(&path, B_003D4A60);
                if (ref.m_tag.m_n == oid) {
                    ALLOCREQ reqSym;
                    ALLOCREQ req;
                    req.cb = 8;
                    SAVEPATH *ppath = (SAVEPATH *)PvAllocStackImpl__Fi(Aligned(&req));
                    CopyAb(ppath, &path, 8);
                    reqSym.cb = path.csym * 2;
                    ppath->asymid = (short *)PvAllocStackImpl__Fi(Aligned(&reqSym));
                    CopyAb(ppath->asymid, path.asymid, path.csym * 2);
                    return ppath;
                }
            }
        }
    }
    return 0;
}
