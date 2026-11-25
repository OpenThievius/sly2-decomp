#include "sly2.h"
#include "cmpeg.h"
extern "C" void QueueMovie(CMpeg *mpeg, MOVIE *movie)
{
    if (movie != 0) {
        if (movie->field_0x4 != movie->field_0x3C) {
            unsigned count = mpeg->cmovie;
            if (count < 4) {
                mpeg->amovie[count] = *movie;
                mpeg->cmovie = count + 1;
            }
        }
    }
}
