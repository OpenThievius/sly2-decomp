#include "so.h"

struct PRIPG : SO {
    /* 0x150 */ s32 unk150;
    u8 unknown_0x154[8];
    /* 0x15C */ DL dlMembers; /* reader: Pripg_InitSo (InitDl) */
};
void InitDl(DL *, int);
extern "C" {
void InitSo(SO *);
void func_001A6CA8(SO *, int);
void EnsureSoOxa(SO *);
void SetSoNoXpsAll(SO *, int);
}
extern "C" void Pripg_InitSo(PRIPG *so)
{
    InitSo(so);
    InitDl(&so->dlMembers, 0xC);
    func_001A6CA8(so, 1);
    unsigned bits = so->grfSw;
    if (!(bits & 1)) {
        *(unsigned *)bits = (*(unsigned *)bits & 1) | 0xE;
    } else {
        so->grfSw = (bits & 1) | 0xE;
    }
    so->grfso &= ~0x800000000UL;
    if (so->unk150 == 1) {
        EnsureSoOxa(so);
        SetSoNoXpsAll(so, 1);
    }
}
