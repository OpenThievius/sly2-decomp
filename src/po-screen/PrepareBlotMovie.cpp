/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "alloc.h"
struct MOVIE { unsigned record[0x11]; int start; int end; };
struct CFileLocation { unsigned hash; unsigned slot; unsigned kind; unsigned field0C; char path[0x100]; void Clear(); int Set(const MOVIE *movie)
    {
        if (movie == 0) return 0;
        unsigned slotNew = movie->record[1] ^ movie->record[0xF];
        unsigned hashNew = movie->record[0] ^ movie->record[0xD];
        kind = 2;
        hash = hashNew + 0xCA0;
        slot = slotNew;
        return slotNew != 0;
    }
};
struct BLOTX { char pad0[0x58]; int state; int pad5C; int time; };
struct NODE { char pad0[0x40]; BLOTX *blot; int first; int last; NODE *next; };
struct BLOT { char pad0[0x50]; int field50; int field54; char pad58[0x68]; MOVIE *movie; };
struct COUNTERS { char pad[0xC]; int limit; };
struct STREAM { char bytes[0x70]; };
extern "C" {
void *CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
void CBinaryFileStream_Destructor(STREAM *, int);
void CBinaryInputStream_ConstructFromBuffer(STREAM *, int, void *, int);
int CBinaryFileStream_FOpenLocation(STREAM *, CFileLocation *);
void *PvAllocStackImpl__Fi(ALLOCREQ *);
void SetBlotBlots(BLOTX *, int);
int U16Read__18CBinaryInputStream(STREAM *);
int U8Read__18CBinaryInputStream(STREAM *);
void func_001179D8(STREAM *, int, int);
int func_00233470(const void *, const void *, int);
void LoadMovieDictionary(BLOT *, STREAM *, BLOT *, int *, int *);
void LoadMovieSprites(BLOT *, STREAM *, BLOT *);
extern NODE *B_003E106C;
extern COUNTERS B_003E1C70;
extern int g_2be538;
}
/* Two passes over the movie-blot list: the newest end frame of the live blots is kept, blots starting at or after it are
 * reset, and it is stored to the arena's mark (B_003E1C70+0xC). Then the movie's BRX file is opened through a stack buffer,
 * its "ZRB." magic and version 6 checked, and the dictionary and sprites loaded between two arena marks.
 * Each early exit runs the stream and stack-frame destructors itself, as the scope exits of the original did; the
 * post-reload cross-jump merges them into the one shared tail retail shows. */
extern "C" void PrepareBlotMovie(BLOT *pblot)
{
    int latest = 0;
    NODE *node;
    BLOTX *blot;
    for (node = B_003E106C; node != 0; node = node->next) {
        blot = node->blot;
        if (blot->state != 0 && (blot->state != 1 || g_2be538 - blot->time < 2)) {
            int last = node->last;
            latest = latest < last ? last : latest;
        }
    }
    for (node = B_003E106C; node != 0; node = node->next) {
        blot = node->blot;
        if (node->first >= latest && blot->state != 0) SetBlotBlots(blot, 0);
    }
    B_003E1C70.limit = latest;
    char frame[0x10];
    CStackFrame_Construct(frame);
    void *buffer;
    {
        ALLOCREQ request;
        ALLOCREQ *req = &request;
        request.cb = 0x10000;
        req->cbAlign = 0x40;
        buffer = PvAllocStackImpl__Fi(req);
    }
    STREAM stream;
    CBinaryInputStream_ConstructFromBuffer(&stream, 0x10000, buffer, 0);
    CFileLocation location;
    CFileLocation *loc = &location;
    loc->kind = 2;
    loc->Clear();
    if (!location.Set(pblot->movie)) {
        CBinaryFileStream_Destructor(&stream, 2);
        CStackFrame_Destructor(frame, 2);
        return;
    }
    if (CBinaryFileStream_FOpenLocation(&stream, &location) == 0) {
        CBinaryFileStream_Destructor(&stream, 2);
        CStackFrame_Destructor(frame, 2);
        return;
    }
    func_001179D8(&stream, 0x4000, 0x70000000);
    {
        char magic[4];
        magic[0] = U8Read__18CBinaryInputStream(&stream);
        magic[1] = U8Read__18CBinaryInputStream(&stream);
        magic[2] = U8Read__18CBinaryInputStream(&stream);
        magic[3] = U8Read__18CBinaryInputStream(&stream);
        int version = U16Read__18CBinaryInputStream(&stream);
        if (func_00233470(magic, "ZRB.", 4) != 0) {
            CBinaryFileStream_Destructor(&stream, 2);
            CStackFrame_Destructor(frame, 2);
            return;
        }
        if (version != 6) {
            CBinaryFileStream_Destructor(&stream, 2);
            CStackFrame_Destructor(frame, 2);
            return;
        }
    }
    pblot->movie->start = B_003E1C70.limit;
    LoadMovieDictionary(pblot, &stream, pblot, &pblot->field50, &pblot->field54);
    LoadMovieSprites(pblot, &stream, pblot);
    pblot->movie->end = B_003E1C70.limit;
    CBinaryFileStream_Destructor(&stream, 2);
    CStackFrame_Destructor(frame, 2);
}
