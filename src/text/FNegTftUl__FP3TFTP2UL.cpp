#include "sly2.h"
#include "tft.h"

int FNegTftUl__FP3TFTP2UL(TFT *t, u64 *pul)
{
    int neg = 0;
    switch (t->cbArg) {
    case 0:
        ((int *)pul)[1] = 0;
        break;
    case 1:
        *pul = *(unsigned short *)pul;
        break;
    case 2:
        break;
    }
    if (t->chType == 'd' || t->chType == 'i') {
        switch (t->cbArg) {
        case 0: {
            int value = *(int *)pul;
            if (value < 0) {
                *(int *)pul = -value;
                neg = 1;
            }
            break;
        }
        case 1: {
            short value = *(short *)pul;
            if (value < 0) {
                *(unsigned short *)pul = -*(unsigned short *)pul;
                neg = 1;
            }
            break;
        }
        case 2: {
            s64 value = (s64)*pul;
            if (value < 0) {
                *pul = (u64)-value;
                neg = 1;
            }
            break;
        }
        }
    }
    return neg;
}
