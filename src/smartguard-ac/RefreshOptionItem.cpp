#include "sly2.h"
#include "cref.h"
struct SAVE { char b[0x5408]; };
extern SAVE B_003D4A60;
extern "C" CRef RefGetGameSaveValue(void *, SAVE *);
extern "C" void *B_003E0FC0, *B_003E0FD8, *B_003E0FDC, *B_003E0FE0;
extern "C" int B_003DD050;
extern "C" int g_2c2d8c;

static inline int ReadSave(void *path)
{
    int value = RefGetGameSaveValue(path, &B_003D4A60).m_tag.m_n;
    return value;
}

extern "C" void RefreshOptionItem(int *pitem)
{
    int item;
    switch (*pitem) {
    case 0x3F:
    case 0x68:
        break;
    case 0x4C:
    case 0x4D:
    case 0x4E: {
        int value = ReadSave(B_003E0FC0);
        switch (value) {
        case 0:
            item = 0x4E;
            break;
        case 1:
            item = 0x4C;
            break;
        case 2:
            item = 0x4D;
            break;
        default:
            item = 0x4E;
            break;
        }
        *pitem = item;
        break;
    }
    case 0x4F:
    case 0x50:
        *pitem = (B_003DD050 != 0) ? 0x4F : 0x50;
        break;
    case 0x48:
    case 0x49: {
        int value;
        switch (g_2c2d8c) {
        case 1:
            value = ReadSave(B_003E0FD8);
            break;
        case 2:
            value = 0;
            break;
        case 3:
            value = 1;
            break;
        default:
            value = 0;
            break;
        }
        if (value != 0)
            *pitem = 0x49;
        else
            *pitem = 0x48;
        break;
    }
    case 0x51:
    case 0x52: {
        int value = ReadSave(B_003E0FDC);
        if (value != 0)
            *pitem = 0x52;
        else
            *pitem = 0x51;
        break;
    }
    case 0x53:
    case 0x54: {
        int value = ReadSave(B_003E0FE0);
        if (value != 0)
            *pitem = 0x54;
        else
            *pitem = 0x53;
        break;
    }
    }
}
