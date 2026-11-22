// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
#include "xf.h"

extern "C" MATRIX4 *PmatWorldSo(SO *pso) {
    return &pso->pxfRoot->matWorld;
}
