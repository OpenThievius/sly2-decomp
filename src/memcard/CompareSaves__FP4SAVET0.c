/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

#include "memcard.h"

s32 CompareSaves__FP4SAVET0(MCFILEINFO *first, MCFILEINFO *second) {
    s32 difference;

    difference = first->modifyYear - second->modifyYear;
    if (difference == 0) {
        difference = first->modifyMonth - second->modifyMonth;
        if (difference == 0) {
            difference = first->modifyDay - second->modifyDay;
            if (difference == 0) {
                difference = first->modifyHour - second->modifyHour;
                if (difference == 0) {
                    difference = first->modifyMinute - second->modifyMinute;
                    if (difference == 0) {
                        return first->modifySecond - second->modifySecond;
                    }
                }
            }
        }
    }
    return difference;
}
