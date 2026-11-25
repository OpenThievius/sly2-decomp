#include "cfont.h"
extern "C" {
void AddPrimPack__4GIFSiiUl(GIFS *gifs, int a, int b, int c);
void PackAD__4GIFSll(GIFS *gifs, s64 reg, s64 value);
void CleanupDraw__5CFontP8CTextBoxP4GIFS(CFONT *font, CTextBox *textBox, GIFS *gifs) {
    if (textBox != 0) {
        AddPrimPack__4GIFSiiUl(gifs, 0, 1, 0xE);
        PackAD__4GIFSll(gifs, 0x40, ((0xDF00L << 31) | 0xFF80) << 9);
    }
}
}
