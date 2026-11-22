// SPDX-License-Identifier: GPL-3.0-or-later
#include "cfont.h"

extern "C" {
void AddPrimList__4GIFSiUl(GIFS *, int, unsigned long);
void AddPrimPack__4GIFSiiUl(GIFS *, int, int, int);
int FEnsureLoaded__8CFontBrxP4GIFS(CFONT *, GIFS *);
void PackAD__4GIFSll(GIFS *, int, s64);

void SetupDraw__8CFontBrxP8CTextBoxP4GIFS(CFONT *font, CTextBox *textBox, GIFS *gifs) {
    f32 left;
    f32 top;
    s32 x0;
    s32 x1;
    s32 y0;
    s64 y1;
    s32 fLoaded;
    s64 test;

    if (textBox != 0) {
        left = textBox->x;
        top = textBox->y;
        x0 = (s32) (left * 0.8f);
        x1 = (s32) ((left + (textBox->dx * 512.0f)) * 0.0015625f) - 1;
        y0 = (s32) (top * 0.45454547f);
        y1 = (s32) ((top + textBox->dy) * 0.45454547f) - 1;
        AddPrimPack__4GIFSiiUl(gifs, 0, 1, 0xE);
        PackAD__4GIFSll(gifs, 0x40, x0 | ((s64) x1 << 0x10) | ((s64) y0 << 0x20) | (y1 << 0x30));
    }
    fLoaded = FEnsureLoaded__8CFontBrxP4GIFS(font, gifs);
    AddPrimPack__4GIFSiiUl(gifs, 6, 1, 0xE);
    if (fLoaded != 0) {
        PackAD__4GIFSll(gifs, 0x3F, 0);
    }
    test = 0x31001;
    if (font->fTest != 0) {
        test = font->test;
    }
    PackAD__4GIFSll(gifs, 0x47, test);
    PackAD__4GIFSll(gifs, 0x42, 0x44);
    PackAD__4GIFSll(gifs, 6, font->tex0);
    PackAD__4GIFSll(gifs, 0x14, 0x60);
    PackAD__4GIFSll(gifs, 8, 5);
    PackAD__4GIFSll(gifs, 0, 0x1D6);
    AddPrimList__4GIFSiUl(gifs, 5, 0x43431);
}
}
