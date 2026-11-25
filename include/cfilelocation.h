/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CFileLocation, where a file is on the disc (0x110 bytes: Clear zeroes it): a hash, a slot, a kind and the path. Names are ours,
   from the callers that fill it from a movie record (Execute, FUN_0018c1e8, load_file_from_disc). C++ only. */
#ifndef SLY2_CFILELOCATION_H
#define SLY2_CFILELOCATION_H
#include "types.h"
#include "cmpeg.h"

struct CFileLocation {
    /* 0x00 */ s32 hash;  /* reader: load_file_from_disc, Execute, FUN_0018c1e8: movie field_0x0 ^ field_0x34, plus 0xCA0 */
    /* 0x04 */ s32 slot;  /* movie field_0x4 ^ field_0x3C: zero when the movie has no file */
    /* 0x08 */ s32 kind;  /* set to 2 before Clear */
    /* 0x0C */ char path[0x104];
    void Clear();
    int Set(const MOVIE *movie)
    {
        if (movie == 0) return 0;
        kind = 2;
        slot = movie->field_0x4 ^ movie->field_0x3C;
        hash = (movie->field_0x0 ^ movie->field_0x34) + 0xCA0;
        return slot != 0;
    }
};
#endif
