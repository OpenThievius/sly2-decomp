// SPDX-License-Identifier: GPL-3.0-or-later
struct RGBA {
    unsigned char r, g, b, a;
    RGBA() {}
    RGBA(unsigned int rgba) { *(unsigned int *)this = rgba; }
};
struct CTextBox;
struct MT_1DAC58 { char pad[0xA0]; };
struct GADGETENTRY { int id; char pad4[0x10]; float x; float y; char pad1c[4]; };
struct GADGETMENU { char pad0[0x24]; int hmovie; char pad28[0x24]; int centry; GADGETENTRY *pentry; };
struct FOCUSSLOT { int id; char pad4[8]; };
struct FOCUS { char pad0[0x1180]; FOCUSSLOT aslot[3]; };
extern "C" {
void CTextBox_SetPos(CTextBox *, float, float);
void CTextBox_SetSize(CTextBox *, float, float);
void CTextBox_SetTextColor(CTextBox *, RGBA *);
void CTextBox_SetHorizontalJust(CTextBox *, int);
void CTextBox_SetVerticalJust(CTextBox *, int);
int FDrawBlotMovie(int);
int FIsBasicDerivedFrom(void *, int);
void *PpoSwFocusBase(void *);
MT_1DAC58 *func_00215AC0(MT_1DAC58 *, int, float);
void CMovieText_Draw(MT_1DAC58 *, CTextBox *, int);
extern char B_003DD490[];
extern int D_002C3268[];
extern float D_002C3264;
}
struct CTextBox {
    float x;
    float y;
    float dx;
    float dy;
    RGBA rgba;
    int jh;
    int jv;
    CTextBox(float xNew, float yNew, float dxNew, float dyNew, unsigned int rgbaText)
    {
        CTextBox_SetPos(this, xNew, yNew);
        CTextBox_SetSize(this, dxNew, dyNew);
        RGBA rgbaColor(rgbaText);
        CTextBox_SetTextColor(this, &rgbaColor);
        CTextBox_SetHorizontalJust(this, 0);
        CTextBox_SetVerticalJust(this, 0);
    }
};
extern "C" void GadgetMenu_DrawSlotLabels(GADGETMENU *self)
{
    if (self->hmovie == 0 || FDrawBlotMovie(self->hmovie) == 0)
        return;
    FOCUS *pfocus = (FOCUS *)PpoSwFocusBase(B_003DD490);
    if (pfocus == 0 || FIsBasicDerivedFrom(pfocus, 0x34) == 0)
        return;
    for (int ientry = 0; ientry < self->centry; ientry++) {
        GADGETENTRY *pentry = &self->pentry[ientry];
        for (int islot = 0; islot < 3; islot++) {
            if (pentry->id == pfocus->aslot[islot].id) {
                CTextBox textBox(0.0f, 0.0f, 640.0f, 492.80002f, 0xFF808080);
                MT_1DAC58 text;
                func_00215AC0(&text, D_002C3268[islot], D_002C3264);
                float xText = pentry->x;
                float yText = pentry->y;
                textBox.y = yText;
                textBox.x = xText;
                textBox.dx = 32.0f;
                textBox.dy = 32.0f;
                CMovieText_Draw(&text, &textBox, 0x13);
                break;
            }
        }
    }
}
