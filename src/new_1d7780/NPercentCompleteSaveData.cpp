// SPDX-License-Identifier: GPL-3.0-or-later
#include "cref.h"
#include "sw.h"

// A node of the save tree, 10 bytes (CcluesFound walks the same array through inodeFirstChild and inodeNext).
struct SAVENODE
{
    short sym;
    signed char kind;
    unsigned char cbit;
    unsigned short ib;
    unsigned short inodeFirstChild;
    unsigned short inodeNext;
};

// The save tree at SW+0x3A18 (CcluesFound's save, nodes and symtab).
struct SAVE
{
    int cnode;
    SAVENODE *anode;
    char symtab[4];
};

extern SW B_003DD490;
extern "C" {
extern int D_002C2DC0[];
extern const char RO_002A78F0[];
CRef RefGetGameSaveValue(SAVEPATH *path, unsigned char *pb);
int SymidFindSymtab(void *symtab, const char *name);
}

static inline int NGetSaveValue(SAVEPATH *path, unsigned char *pb)
{
    return RefGetGameSaveValue(path, pb).m_tag.m_n;
}

static inline int NClamp(int n, int nMin, int nMax)
{
    if (n < nMin)
        return nMin;
    if (n > nMax)
        return nMax;
    return n;
}

extern "C" int NPercentCompleteSaveData(SAVE *psave, unsigned char *pb)
{
    int total = 0;
    int possible = 0;
    for (int i = 0; i < 9; i++) {
        SAVEPATH *path = B_003DD490.apsavepathEpisodePercent[i];
        int weight = D_002C2DC0[i];
        possible += weight * 100;
        if (path != 0)
            total += NGetSaveValue(path, pb) * weight;
    }
    possible += 0xD0;
    int symid = SymidFindSymtab(psave->symtab, RO_002A78F0);
    for (int inode = 0; inode < psave->cnode; inode++) {
        SAVENODE *pnode = &psave->anode[inode];
        if (pnode->kind == 4 && pnode->sym == symid) {
            unsigned char *pbBits = pb + pnode->ib;
            if (pnode->cbit != 0) {
                for (int ibit = 0; ibit < pnode->cbit; ibit++) {
                    int bit = (1 << (ibit % 8)) & 0xFF;
                    if (pbBits[ibit / 8] & bit)
                        total += 0x1A;
                }
            } else if (*pbBits != 0) {
                total += 0x1A;
            }
        }
    }
    if (total == 0)
        return 0;
    if (total == possible)
        return 100;
    int percent = total * 100 / possible;
    return NClamp(percent, 1, 99);
}
