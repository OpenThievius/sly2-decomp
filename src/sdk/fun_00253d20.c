/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "mpeg.h"
int func_00252148(MPEGDEC *, int);
void func_002542B8(MPEGDEC *);
void func_002544C0(MPEGDEC *, int);
void func_00253D20(MPEGDEC *decoder) {
    int temporalReference;
    int firstAfterGroup;
    int previous;
    int pictureIndex;
    temporalReference = func_00252148(decoder, 10);
    decoder->pictureCodingType = func_00252148(decoder, 3);
    func_00252148(decoder, 0x10);
    if ((u32) (decoder->pictureCodingType - 2) < 2U) {
        decoder->fullPelForward = func_00252148(decoder, 1);
        decoder->forwardCode = func_00252148(decoder, 3);
    }
    if (decoder->pictureCodingType == 3) {
        decoder->fullPelBackward = func_00252148(decoder, 1);
        decoder->backwardCode = func_00252148(decoder, 3);
    }
    while (func_00252148(decoder, 1) != 0) {
        func_002544C0(decoder, 8);
    }
    func_002542B8(decoder);
    firstAfterGroup = 0;
    previous = 0;
    if (decoder->pictureCodingType != 3 && temporalReference != 0) {
        if (temporalReference < 0) {
            firstAfterGroup = decoder->newGop == 0;
        }
        decoder->newGop = 0;
        previous = temporalReference;
    }
    pictureIndex = decoder->gopBase + temporalReference;
    decoder->pictureIndex = pictureIndex;
    if (firstAfterGroup != 0 && previous >= temporalReference) {
        decoder->pictureIndex = pictureIndex + 0x400;
    }
    {
        int current = decoder->maxPictureIndex;
        int limit = decoder->pictureIndex;
        if (current < limit) current = limit;
        decoder->maxPictureIndex = current;
    }
}
