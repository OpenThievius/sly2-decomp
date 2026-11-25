// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "clock.h"
struct SMPA20F7E0;
struct HUDVALUE { u8 unknown_0x0[0x14]; float value; };
struct BLOTMOVIE { u8 unknown_0x0[0xF8]; HUDVALUE *hud; };
extern "C" {
int FDrawBlotMovie(BLOTMOVIE *);
float GSmoothA__FffffP4SMPAPf(float, float, float, float, SMPA20F7E0 *, float *);
void *NewEmitter(int);
void SetEmitterUnpositioned(void *, int);
extern char D_002C3E88;
extern float D_002C3E80;
static inline float Clamp(float value, float low) { return value < low ? low : value; }
void UpdateSwHudBlots(SW *owner)
{
    float level = 0.0f;
    for (int index = 0; index < 4; index++) {
        HUDBLOT *blot = &owner->ahudblot[index];
        BLOTMOVIE *movie = (BLOTMOVIE *)blot->plo;
        if (movie == 0 || FDrawBlotMovie(movie) == 0) {
            blot->fresh = 1;
        } else {
            if (blot->fresh != 0) {
                movie->hud->value = level;
                blot->velocity = 0.0f;
                blot->fresh = 0;
            } else {
                movie->hud->value = GSmoothA__FffffP4SMPAPf(movie->hud->value, blot->velocity, level, g_2dded0.dt, (SMPA20F7E0 *)&D_002C3E88, &blot->velocity);
            }
            level += D_002C3E80;
            if (index == 3) {
                float now = g_2dded0.t;
                float remaining = owner->tEmit - now;
                int stamp = (int)Clamp(remaining, 0.0f);
                if (stamp != owner->emitStamp) {
                    int kind = 0x31;
                    if (stamp & 1) kind = 0x30;
                    SetEmitterUnpositioned(NewEmitter(kind), 0);
                    owner->emitStamp = stamp;
                }
            }
        }
    }
}
}
