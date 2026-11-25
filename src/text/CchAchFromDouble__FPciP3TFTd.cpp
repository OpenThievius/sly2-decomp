// SPDX-License-Identifier: GPL-3.0-or-later
#include "tft.h"
extern const unsigned char D_002C40C8[];
unsigned char ChDigitFromG(double g, int first, int exp);
extern "C" {
int ExpFirstFromG__Fd(double g);
double pow(double, double);
double __floatsidf(int);
double __muldf3(double, double);
double __adddf3(double, double);
int __fixdfsi(double);
char *strcpy(char *, const char *);
int strlen(const char *);

int CchAchFromDouble__FPciP3TFTd(char *pch, int cch, TFT *ptft, double d)
{
    union { double d; u64 u; } bits;
    bits.d = d;
    if ((bits.u & 0x7FF0000000000000UL) == 0x7FF0000000000000UL) {
        strcpy(pch, (bits.u & 0xFFFFFFFFFFFFFUL) ? "(nan)" : "(inf)");
        return strlen(pch);
    }
    char *pchCur = pch;
    int expFirst = ExpFirstFromG__Fd(d);
    int fExp = ptft->chType == 'e';
    if (ptft->chType == 'g') {
        if (expFirst < -4 || expFirst >= ptft->cchPrec) {
            fExp = 1;
            ptft->cchPrec = ptft->cchPrec - 1;
        }
    }
    int expScale = 0;
    if (fExp)
        expScale = expFirst;
    double gRound = __adddf3(d, __muldf3(pow(10.0, __floatsidf(expScale - ptft->cchPrec)), 0.5));
    int expRound = ExpFirstFromG__Fd(gRound);
    if (expFirst < ExpFirstFromG__Fd(gRound))
        expFirst = expRound;
    int cchInt;
    int exp;
    if (fExp) {
        cchInt = 1;
        exp = expFirst;
    } else if (expFirst >= 0) {
        cchInt = expFirst + 1;
        exp = expFirst;
    } else {
        cchInt = 1;
        exp = 0;
    }
    while (cchInt-- > 0)
        *pchCur++ = ChDigitFromG(gRound, expFirst, exp--);
    if (ptft->fPrec == 0) {
        *pchCur++ = '.';
        int cchFrac = ptft->cchPrec;
        while (cchFrac-- > 0)
            *pchCur++ = ChDigitFromG(gRound, expFirst, exp--);
        if (ptft->chType == 'g') {
            while (pch < pchCur && (unsigned char)pchCur[-1] == '0')
                pchCur--;
            if (pch < pchCur && (unsigned char)pchCur[-1] == '.')
                pchCur--;
        }
    }
    if (fExp) {
        *pchCur++ = 'e';
        if (expFirst < 0) {
            *pchCur++ = '-';
            expFirst = -expFirst;
        } else {
            *pchCur++ = '+';
        }
        int divisor = __fixdfsi(pow(10.0, 2.0));
        int i = 2;
        do {
            i--;
            *pchCur++ = D_002C40C8[expFirst / divisor];
            expFirst = (expFirst % divisor) * 10;
        } while (i >= 0);
    }
    return pchCur - pch;
}
}
