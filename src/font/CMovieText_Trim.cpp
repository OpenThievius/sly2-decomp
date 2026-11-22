// SPDX-License-Identifier: GPL-3.0-or-later
struct CMOVIETEXT {
    char unknown_0x0[4];
    char *pchEnd; /* CMovieText_Trim terminates the text here after skipping its characters */
};
extern "C" {
int CMovieText_ChNext(CMOVIETEXT *);
void CMovieText_Reset(CMOVIETEXT *, int);
void CMovieText_Trim(CMOVIETEXT *text, int cch) {
    CMovieText_Reset(text, 0);
    while (CMovieText_ChNext(text) != 0) {
        if (cch == 0) {
            break;
        }
        cch -= 1;
    }
    *text->pchEnd = 0;
}
}
