// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "clock.h"
#include "cmpeg.h"
#include "cfilelocation.h"
#include "joy.h"
#include "memcard.h"
struct REQ_1B3BD0 { int size; int align; };
struct STREAM_1B3BD0 { char bytes[0x30]; };
extern "C" {
int CBinaryAsyncStream_FOpenLocation(STREAM_1B3BD0 *, CFileLocation *);
void CMpeg_Start(CMpeg *, STREAM_1B3BD0 *);
void *CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
int Close__18CBinaryAsyncStream(STREAM_1B3BD0 *);
int FJoyButtonPressed(JOY *, int, int);
void MarkClockTick__FP5CLOCK(CLOCK *, int);
void *PvAllocStackClearImpl__Fi(REQ_1B3BD0 *);
void UpdateCd__Fv();
void UpdateJoy__FP3JOY(JOY *);
void UpdateSave__FP4SAVE(SAVE *);
void __18CBinaryAsyncStreamPv(STREAM_1B3BD0 *, int, void *);
void func_001325B8(STREAM_1B3BD0 *, int);
int sceMpegIsEnd(void *);
extern JOY B_002DFC00;
extern SAVE B_002E65E0;
extern int B_002F68F8;
extern int D_002C0268;
extern MOVIE RO_002A3968;
extern MOVIE RO_002A39A8;
extern int g_2bd4c0;
}
static inline int SameMovie(MOVIE *left, MOVIE *right)
{
    if (left == right) return 1;
    if (left == 0) return 0;
    if (right == 0) return 0;
    return (left->field_0x8 ^ left->field_0x38) == (right->field_0x8 ^ right->field_0x38);
}

extern "C" void Execute__5CMpeg(CMpeg *self, MOVIE *movie)
{
    char frame[0x10];
    REQ_1B3BD0 req;
    STREAM_1B3BD0 stream;
    CFileLocation location;

    CStackFrame_Construct(frame);
    REQ_1B3BD0 *preq = &req;
    req.size = 0x41FC00;
    preq->align = 0x40;
    void *buffer = PvAllocStackClearImpl__Fi(preq);
    self->pbBuffer = (u8 *)buffer;
    __18CBinaryAsyncStreamPv(&stream, 0x80000, buffer);
    CFileLocation *ploc = &location;
    ploc->kind = 2;
    ploc->Clear();
    int valid;
    if (movie == 0) {
        valid = 0;
    } else {
        int slot = movie->field_0x4;
        int other = movie->field_0x3C;
        ploc->kind = 2;
        location.hash = (movie->field_0x0 ^ movie->field_0x34) + 0xCA0;
        location.slot = slot ^ other;
        valid = slot != other;
    }
    if (valid != 0 && CBinaryAsyncStream_FOpenLocation(&stream, &location) != 0) {
        CMpeg_Start(self, &stream);
        while (sceMpegIsEnd(self->sdk) == 0) {
            MarkClockTick__FP5CLOCK(&g_2dded0, 1);
            UpdateJoy__FP3JOY(&B_002DFC00);
            if (B_002E65E0.pslotCur == 0)
                UpdateSave__FP4SAVE(&B_002E65E0);
            int skippable = 0;
            if (SameMovie(movie, &RO_002A3968) != 0 || SameMovie(movie, &RO_002A39A8) != 0)
                skippable = B_002F68F8 != 0;
            if (D_002C0268 != 0)
                skippable = 1;
            int allowed = skippable;
            if (allowed != 0) {
                int pressed = 0;
                if (FJoyButtonPressed(&B_002DFC00, 0x91F, allowed) != 0)
                    pressed = 1;
                if (pressed != 0) {
                    self->fSkippable = 0;
                    break;
                }
            }
            if (location.kind != 2 || (UpdateCd__Fv(), g_2bd4c0 == 3))
                self->Update();
            else
                break;
        }
        if (SameMovie(movie, &RO_002A39A8) != 0)
            B_002F68F8 = 1;
        self->Finish();
        Close__18CBinaryAsyncStream(&stream);
    }
    self->pbBuffer = 0;
    func_001325B8(&stream, 2);
    CStackFrame_Destructor(frame, 2);
}
