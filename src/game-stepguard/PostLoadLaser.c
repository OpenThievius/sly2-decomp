/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct LASER;
void BuildLaserBeams(struct LASER *);
void ClipLaserBeams(struct LASER *, int);
void PostSoLoad();
void func_001DEDB0(struct LASER *);

void PostLoadLaser(struct LASER *laser) {
    PostSoLoad();
    BuildLaserBeams(laser);
    func_001DEDB0(laser);
    ClipLaserBeams(laser, 0);
}
