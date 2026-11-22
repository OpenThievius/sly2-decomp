/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ROWS3: three rows of a matrix as 16-byte aligned VECTORs (0x30 bytes). What ConvertXfMat returns, RotateXfmToMat copies into
   an XFM's local matrix and SetSlotSoHeading's LoadRotateMatrixRad fills in (then stored in SLOTSO::rotation); dprize.h's prize code
   uses it too. C and C++. */
#ifndef SLY2_ROWS3_H
#define SLY2_ROWS3_H
#include "sly2.h"

struct ROWS3 {
    VECTOR row[3];
};
#endif
