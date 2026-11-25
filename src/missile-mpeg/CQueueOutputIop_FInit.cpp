#include "sly2.h"
#include "cmpeg.h"
struct HDR { u8 unknown_0x0[8]; int wfmt; int rate; int channels; int run; };
extern "C" int snd_PlaySoundVolPanPMPB(int, int, int, int, int, int);

int CQueueOutputIop_FInit(CQueueOutputIop *queue, HDR *hdr)
{
    int wfmt = hdr->wfmt;
    queue->wfmt = wfmt;
    queue->rate = hdr->rate;
    int channels = hdr->channels;
    queue->cChannel = channels;
    queue->cbChunk = hdr->run;
    if (wfmt == 0x10) {
        queue->cbBuffer = channels << 12;
        queue->pbIop = snd_PlaySoundVolPanPMPB(0x400, 0x1000, 0x400, 0, 2, 3);
    } else {
        queue->cbBuffer = 0x6000;
        queue->pbIop = snd_PlaySoundVolPanPMPB(0x6000, 0, 0x400, 0, 2, 2);
    }
    if (queue->pbIop < 0)
        return 0;
    queue->Reset();
    return 1;
}
