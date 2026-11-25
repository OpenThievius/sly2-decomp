// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
extern "C" {
struct MpegSlot {
    u8 unknown_0x0[0x12C];
    int predicted;
    u8 unknown_0x130[0x140 - 0x130];
};
struct MpegDecoder {
    u8 unknown_0x0[0x130];
    int secondField;
    u8 unknown_0x134[0x160 - 0x134];
    int pictureCodingType;
    u8 unknown_0x164[0x184 - 0x164];
    int pictureStructure;
    u8 unknown_0x188[0x1C8 - 0x188];
    int forwardFrame;
    int backwardFrame;
    u8 unknown_0x1D0[0x1D8 - 0x1D0];
    int fieldFrames[2][4];
    u8 unknown_0x1F8[0x5A0 - 0x1F8];
    MpegSlot slots[2];
    int slotIndex;
};
void func_002505B0(MpegDecoder *mpeg, int source, int sourceField, int destinationField, int offset, int height, int x, int y,
                   int dx, int dy, int fieldBased, int average);
void func_0024FAD0(MpegDecoder *mpeg, int dualPrime[2][2], int *dmvector, int mvx, int mvy);
void func_0024FA90(MpegDecoder *mpeg, const char *format, ...);

void func_0024FC58(MpegDecoder *mpeg, int x, int y, int macroblockType, int motionType, int vectors[2][2][2], int fieldSelect[2][2],
                   int *dmvector) {
    int average = 0;
    int select = 1;
    int dualPrime[2][2];
    mpeg->slots[mpeg->slotIndex].predicted = 0;
    if ((macroblockType & 8) || mpeg->pictureCodingType == 2) {
        if (mpeg->pictureStructure == 3) {
            if (motionType == 2 || !(macroblockType & 8)) {
                func_002505B0(mpeg, mpeg->forwardFrame, 0, 0, 0, 16, x, y, vectors[0][0][0], vectors[0][0][1], 0, 0);
            } else if (motionType == 1) {
                func_002505B0(mpeg, mpeg->forwardFrame, fieldSelect[0][0], 0, 0, 8, x, y, vectors[0][0][0], vectors[0][0][1] >> 1, 1, 0);
                func_002505B0(mpeg, mpeg->forwardFrame, fieldSelect[1][0], 1, 0, 8, x, y, vectors[1][0][0], vectors[1][0][1] >> 1, 1, 0);
            } else if (motionType == 3) {
                func_0024FAD0(mpeg, dualPrime, dmvector, vectors[0][0][0], vectors[0][0][1] >> 1);
                func_002505B0(mpeg, mpeg->forwardFrame, 0, 0, 0, 8, x, y, vectors[0][0][0], vectors[0][0][1] >> 1, 1, 0);
                func_002505B0(mpeg, mpeg->forwardFrame, 1, 0, 0, 8, x, y, dualPrime[0][0], dualPrime[0][1], 1, 1);
                func_002505B0(mpeg, mpeg->forwardFrame, 1, 1, 0, 8, x, y, vectors[0][0][0], vectors[0][0][1] >> 1, 1, 0);
                func_002505B0(mpeg, mpeg->forwardFrame, 0, 1, 0, 8, x, y, dualPrime[1][0], dualPrime[1][1], 1, 1);
            } else {
                func_0024FA90(mpeg, "(a) invalid motion_type(%d)-0", motionType);
            }
        } else {
            int currentField = mpeg->pictureStructure == 2;
            int frames[2][2];
            frames[0][0] = mpeg->fieldFrames[0][0];
            frames[0][1] = mpeg->fieldFrames[1][0];
            frames[1][0] = mpeg->fieldFrames[0][1];
            frames[1][1] = mpeg->fieldFrames[1][1];
            if (mpeg->pictureCodingType == 2 && mpeg->secondField && currentField != fieldSelect[0][0]) {
                select = 1;
            } else {
                select = 0;
            }
            if (motionType == 1 || !(macroblockType & 8)) {
                func_002505B0(mpeg, frames[select][fieldSelect[0][0]], 0, 0, 0, 16, x, y, vectors[0][0][0], vectors[0][0][1], 0, 0);
            } else if (motionType == 2) {
                func_002505B0(mpeg, frames[select][fieldSelect[0][0]], 0, 0, 0, 8, x, y, vectors[0][0][0], vectors[0][0][1], 0, 0);
                select = mpeg->pictureCodingType == 2 && mpeg->secondField && currentField != fieldSelect[1][0];
                func_002505B0(mpeg, frames[select][fieldSelect[1][0]], 0, 0, 8, 8, x, y, vectors[1][0][0], vectors[1][0][1], 0, 0);
            } else if (motionType == 3) {
                if (mpeg->secondField) {
                    select = 1;
                } else {
                    select = 0;
                }
                func_0024FAD0(mpeg, dualPrime, dmvector, vectors[0][0][0], vectors[0][0][1]);
                func_002505B0(mpeg, frames[0][currentField], 0, 0, 0, 16, x, y, vectors[0][0][0], vectors[0][0][1], 0, 0);
                func_002505B0(mpeg, frames[select][!currentField], 0, 0, 0, 16, x, y, dualPrime[0][0], dualPrime[0][1], 0, 1);
            } else {
                func_0024FA90(mpeg, "(b) invalid motion_type(%d)-1", motionType);
            }
        }
        average = 1;
    }
    if (macroblockType & 4) {
        if (mpeg->pictureStructure == 3) {
            select = 1;
            if (motionType == 2) {
                func_002505B0(mpeg, mpeg->backwardFrame, 0, 0, 0, 16, x, y, vectors[0][1][0], vectors[0][1][1], 0, average);
            } else {
                func_002505B0(mpeg, mpeg->backwardFrame, fieldSelect[0][1], 0, 0, 8, x, y, vectors[0][1][0], vectors[0][1][1] >> 1, select, average);
                func_002505B0(mpeg, mpeg->backwardFrame, fieldSelect[1][1], 1, 0, 8, x, y, vectors[1][1][0], vectors[1][1][1] >> 1, select, average);
            }
        } else {
            if (motionType == 1) {
                func_002505B0(mpeg, (fieldSelect[0][1] ? mpeg->fieldFrames[1][1] : mpeg->fieldFrames[0][1]), 0, 0, 0, 16, x, y, vectors[0][1][0], vectors[0][1][1], 0, average);
            } else if (motionType == 2) {
                func_002505B0(mpeg, (fieldSelect[0][1] ? mpeg->fieldFrames[1][1] : mpeg->fieldFrames[0][1]), 0, 0, 0, 8, x, y, vectors[0][1][0], vectors[0][1][1], 0, average);
                func_002505B0(mpeg, (fieldSelect[1][1] ? mpeg->fieldFrames[1][1] : mpeg->fieldFrames[0][1]), 0, 0, 8, 8, x, y, vectors[1][1][0], vectors[1][1][1], 0, average);
            } else {
                func_0024FA90(mpeg, "(c) invalid motion_type(%d)-2", motionType);
            }
        }
    }
}
}
