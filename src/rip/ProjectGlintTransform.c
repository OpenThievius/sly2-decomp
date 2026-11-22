/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "rip.h"

struct LO;
QW PosLoWorld(struct LO *plo);

/* a GLINT follows an object: its RIP is followed by the object at 0xF0 */
struct GLINT {
    struct RIP rip;
    struct LO *plo; /* ProjectGlintTransform */
};

void ProjectGlintTransform(struct GLINT *glint) {
    glint->rip.posPrev = glint->rip.pos;
    glint->rip.pos = PosLoWorld(glint->plo);
}
