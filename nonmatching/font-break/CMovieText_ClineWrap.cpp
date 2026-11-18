/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
struct CMOVIETEXT {
    unsigned char *pchzStart;
    unsigned char *pchCur;
    void *pfont;
    char pad[0x74 - 0xC];
    float dx;
    char pad2[0x88 - 0x78];
    float gScale;
};
extern "C" {
extern const unsigned char RO_002AA6A1[];
void CMovieText_Reset(CMOVIETEXT *, int);
int CMovieText_ChNext(CMOVIETEXT *);
float DxFromFontCh(void *, int);
}

extern "C" int CMovieText_ClineWrap(CMOVIETEXT *ptext)
{
    float dxLine = 0.0f;
    int cline = 1;
    CMovieText_Reset(ptext, 0);
    unsigned char newline = '\n';
    int ch;
    while ((ch = CMovieText_ChNext(ptext)) != 0) {
        if (ch == '\n') {
            dxLine = 0.0f;
            cline++;
        } else {
            dxLine = dxLine + DxFromFontCh(ptext->pfont, ch) * ptext->gScale;
        }
        if (ptext->dx == 0.0f)
            continue;
        if (ptext->dx < dxLine) {
        unsigned char *pchSearch;
        for (pchSearch = ptext->pchCur - 1; pchSearch >= ptext->pchzStart && *pchSearch != '\n'; pchSearch--) {
            if (*pchSearch == ' ' || *pchSearch == '\t') {
                if ((RO_002AA6A1[pchSearch[1]] & 0x10) == 0) {
                    cline++;
                    *pchSearch = newline;
                    dxLine = 0.0f;
                    ptext->pchCur = pchSearch + 1;
                    break;
                }
            }
        }
        if (dxLine != 0.0f && *ptext->pchCur != 0) {
            *ptext->pchCur = newline;
            cline++;
            dxLine = 0.0f;
        }
        }
    }
    return cline;
}
