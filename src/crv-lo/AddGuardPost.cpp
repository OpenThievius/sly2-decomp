#include "sly2.h"
struct Post { int postA; int pad4; int zoneA; int pad0xC; int postB; int pad0x14; int zoneB; u8 unknown_0x1C[0x8]; };
struct Guard { u8 unknown_0x0[0x1010]; int count; Post *posts; };
void AddGuardPost(Guard *guard, int postA, int zoneA, int postB, int zoneB)
{
    int index = guard->count;
    guard->count = index + 1;
    Post *post = &guard->posts[index];
    post->postA = postA;
    post->zoneA = zoneA;
    post->postB = postB;
    post->zoneB = zoneB;
}
