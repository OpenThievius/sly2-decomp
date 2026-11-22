/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CMpeg, the movie player, and the classes it embeds: CByteQueue (bq/Init_file.cpp's, its fields named there), CQueueOutputIop
   (the audio queue that feeds the IOP) and CMpegAudio (the audio stream). Layouts and names are ours, from the mpeg sources:
   a field is here when a function of src/mpeg reads or writes it at that offset (readers listed). C++ only. */
#ifndef SLY2_CMPEG_H
#define SLY2_CMPEG_H
#include "types.h"

struct SUBTITLE;
struct CBinaryAsyncStream;
struct sceMpeg;
struct sceMpegCbData;
struct CQueueOutput;

/* What the SDK hands a stream callback: the demuxed chunk (FMpegAcceptVideo, FMpegAcceptAudio) */
struct sceMpegCbDataStr {
    u8 unknown_0x0[0x8];
    /* 0x08 */ u8 *data;
    /* 0x0C */ u32 size;
};

struct CByteQueue {
    /* 0x00 */ u8 *pbBuffer;
    /* 0x04 */ s32 cbBuffer;  /* CByteQueue::Init stores it; Reset copies it to cbFree */
    /* 0x08 */ s32 ibFill;
    /* 0x0C */ s32 ibDrain;
    /* 0x10 */ s32 cbFree;    /* FMpegAcceptVideo compares the chunk size with it */
    /* 0x14 */ s32 cbData;    /* FMpegDecodeVideo reads the queued byte count */
    /* 0x18 */ s32 cbHeld;
    /* 0x1C */ s32 cbTotal;
    void Init(int cb, void *pv);
    void Reset();
    int CbFill(int cb, u8 *pb);     /* FMpegAcceptVideo, FMpegDecodeVideo */
    void FreeDrain(int cb);
    void CbDrain(int cb, CQueueOutput *poutput);
};

struct CQueueOutputIop {
    u8 unknown_0x0[0x4];
    /* 0x04 */ s32 wfmt;
    /* 0x08 */ s32 rate;
    /* 0x0C */ s32 cChannel;
    u8 unknown_0x10[0x4];
    /* 0x14 */ s32 pbIop;
    /* 0x18 */ s32 cbBuffer;  /* Reset copies it to cbFree */
    /* 0x1C */ s32 ibWrite;   /* Reset clears it */
    /* 0x20 */ s32 ibRead;    /* Reset clears it */
    /* 0x24 */ s32 cbFree;
    /* 0x28 */ s32 cbQueued;  /* Reset clears it */
    /* 0x2C */ s32 field_0x2C; /* Reset clears it */
    void Reset();
};

struct CMpegAudio {
    /* 0x00 */ s32 state;     /* Init sets 1, Reset sets 1 when it is not 0, Close clears it */
    /* 0x04 */ s32 idStream;  /* Init and Reset set -1 */
    /* 0x08 */ u8 header[0x28];
    /* 0x30 */ CByteQueue qHeader;
    /* 0x50 */ CByteQueue qData;
    /* 0x70 */ CQueueOutputIop qIop;
    /* 0xA0 */ s32 volumeMovie;  /* Init saves master volume 2, Close restores it */
    /* 0xA4 */ s32 volumeMusic;  /* master volume 0x10 */
    u8 unknown_0xA8[0x14];
    void Init();
    void Reset();
    void Close();
    void Update();
};

struct CMpeg {
    u8 unknown_0x0[0x104];
    /* 0x104 */ SUBTITLE *psubtitle;  /* DrawMpegFrame */
    /* 0x108 */ s32 fSkippable;       /* RunNextBootQueueEntry sets it for a skippable movie; Execute clears it when the player skips */
    /* 0x10C */ f32 tPicture;         /* Update stamps the time of the last picture */
    /* 0x110 */ u8 *pbBuffer;         /* Execute stores the stack buffer, Update reads its picture area at +0x285A80 */
    /* 0x114 */ CBinaryAsyncStream *pbas; /* CMpeg_Start stores the stream, CMpeg::Finish clears it */
    u8 sdk[0x8];                      /* 0x118: the SDK's decoder state, passed to sceMpegGetPicture and sceMpegIsEnd */
    /* 0x120 */ s32 skipDraw;         /* Update draws the picture only when it is 0 */
    u8 unknown_0x124[0x3C];
    /* 0x160 */ CByteQueue qVideo;
    /* 0x180 */ CMpegAudio audio;
    /* 0x23C */ s32 sema;
    /* 0x240 */ volatile s32 pending; // volatile-ok: written by MpegDisplayThread (phase 0 to 2) and the demux callback, polled by Update and Finish
    void Update();
    void Finish();
};

#if defined(__mips__)
typedef char check_CByteQueue_size[(sizeof(CByteQueue) == 0x20) ? 1 : -1];
typedef char check_CMpegAudio_qIop[((unsigned int)&((CMpegAudio *)0)->qIop == 0x70) ? 1 : -1];
typedef char check_CMpeg_sdk[((unsigned int)&((CMpeg *)0)->sdk == 0x118) ? 1 : -1];
typedef char check_CMpeg_qVideo[((unsigned int)&((CMpeg *)0)->qVideo == 0x160) ? 1 : -1];
typedef char check_CMpeg_audio[((unsigned int)&((CMpeg *)0)->audio == 0x180) ? 1 : -1];
typedef char check_CMpeg_sema[((unsigned int)&((CMpeg *)0)->sema == 0x23C) ? 1 : -1];
typedef char check_CMpeg_pending[((unsigned int)&((CMpeg *)0)->pending == 0x240) ? 1 : -1];
#endif
#endif
