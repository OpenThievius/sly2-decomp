#include "alloc.h"
#include "bis.h"
#include "shd.h"
extern "C" void FilterColorRgba8_1ed278(void *);
void LoadTexFromBrx(CBinaryInputStream *, TEX *);
extern "C" void *PvAllocSwClearImpl__Fi(ALLOCREQ *);
extern int *B_003DD004;
extern "C" void LoadShdFromBrx(CBinaryInputStream *stream, SHD *shd) {
    ALLOCREQ request;
    CBinaryInputStream_Read_thunk(stream, 0x18, shd);
    FilterColorRgba8_1ed278(&shd->rgba8);
    FilterColorRgba8_1ed278(&shd->rgbaC);
    FilterColorRgba8_1ed278(&shd->rgbaTex);
    int textureIndex = stream->S16Read();
    if (textureIndex >= 0) {
        shd->field_0x28 = B_003DD004[textureIndex];
    }
    request.cbAlign = 0x10;
    request.cb = shd->ctex * sizeof(TEX);
    shd->atex = (TEX *)PvAllocSwClearImpl__Fi(&request);
    for (int index = 0; index < shd->ctex; index++) {
        TEX *texture = &shd->atex[index];
        LoadTexFromBrx(stream, texture);
        texture->owner = shd;
    }
    shd->cframe = shd->atex->cbmp;
    switch (shd->kind) {
    case 0:
    case 4:
    case 5:
    case 6:
        shd->cpart = 1;
        break;
    case 1:
    case 2:
        shd->cpart = 2;
        break;
    case 7:
        shd->cpart = (shd->grf & 0x20) ? 2 : 3;
        break;
    case 3:
        shd->cpart = 4;
        break;
    }
    request.cbAlign = 0x10;
    request.cb = shd->cpart * 8;
    SHDPART *parts = (SHDPART *)PvAllocSwClearImpl__Fi(&request);
    shd->apart = parts;
    SHDPART *cursor;
    switch (shd->kind) {
    case 0:
    case 4:
    case 5:
    case 6: {
        int vertices = shd->atex->owner->cframe + 8;
        parts[0].count = vertices;
        request.cb = vertices * 0x10;
        request.cbAlign = 0x10;
        parts[0].memory = PvAllocSwClearImpl__Fi(&request);
        return;
    }
    case 3: {
        int extra;
        if (shd->grf & 2) {
            extra = shd->atex->owner->cframe + 2;
        } else {
            extra = 0;
        }
        int vertices = extra + 6;
        cursor = &parts[1];
        parts[0].count = vertices;
        request.cb = vertices * 0x10;
        request.cbAlign = 0x10;
        parts[0].memory = PvAllocSwClearImpl__Fi(&request);
        parts[1].count = 6;
        request.cb = 0x60;
        request.cbAlign = 0x10;
        cursor->memory = PvAllocSwClearImpl__Fi(&request);
        parts[2].count = 8;
        cursor = &parts[2];
        request.cb = 0x80;
        request.cbAlign = 0x10;
        cursor->memory = PvAllocSwClearImpl__Fi(&request);
        parts[3].count = 4;
        cursor = &parts[3];
        request.cb = 0x40;
        request.cbAlign = 0x10;
        cursor->memory = PvAllocSwClearImpl__Fi(&request);
        return;
    }
    case 2:
        parts[0].count = 5;
        cursor = &parts[1];
        request.cb = 0x50;
        request.cbAlign = 0x10;
        parts[0].memory = PvAllocSwClearImpl__Fi(&request);
        parts[1].count = 5;
        request.cb = 0x50;
        request.cbAlign = 0x10;
        cursor->memory = PvAllocSwClearImpl__Fi(&request);
        return;
    case 1: {
        cursor = &parts[1];
        int vertices = shd->atex->owner->cframe + 8;
        parts[0].count = vertices;
        request.cb = vertices * 0x10;
        request.cbAlign = 0x10;
        parts[0].memory = PvAllocSwClearImpl__Fi(&request);
        parts[1].count = vertices;
        request.cb = vertices * 0x10;
        request.cbAlign = 0x10;
        cursor->memory = PvAllocSwClearImpl__Fi(&request);
        return;
    }
    case 7: {
        cursor = &parts[1];
        int vertices = shd->atex->owner->cframe + 8;
        parts[0].count = vertices;
        int bytes = vertices * 0x10;
        request.cb = bytes;
        request.cbAlign = 0x10;
        parts[0].memory = PvAllocSwClearImpl__Fi(&request);
        parts[1].count = vertices;
        request.cb = bytes;
        request.cbAlign = 0x10;
        cursor->memory = PvAllocSwClearImpl__Fi(&request);
        cursor = &parts[2];
        if (!(shd->grf & 0x20)) {
            parts[2].count = vertices;
            request.cb = bytes;
            request.cbAlign = 0x10;
            cursor->memory = PvAllocSwClearImpl__Fi(&request);
        return;
        }
        return;
    }
    default:
        return;
    }
}
