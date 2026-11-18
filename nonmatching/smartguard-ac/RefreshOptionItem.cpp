struct CRef { int tagk; union { float g; int n; }; };
extern "C" {
void RefGetGameSaveValue(CRef *, void *, int *);
void CRef_Destruct(CRef *);
}
extern "C" int B_003D4A60;
extern "C" void *B_003E0FC0, *B_003E0FD8, *B_003E0FDC, *B_003E0FE0;
extern "C" int B_003DD050;
extern "C" int g_2c2d8c;

extern "C" void RefreshOptionItem(int *pitem)
{
    CRef ref;
    int item;
    switch (*pitem) {
    case 0x3F:
    case 0x68:
        break;
    case 0x4C:
    case 0x4D:
    case 0x4E: {
        RefGetGameSaveValue(&ref, B_003E0FC0, &B_003D4A60);
        int value = ref.n;
        CRef_Destruct(&ref);
        switch (value) {
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
            RefGetGameSaveValue(&ref, B_003E0FD8, &B_003D4A60);
            value = ref.n;
            CRef_Destruct(&ref);
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
        *pitem = (value != 0) ? 0x49 : 0x48;
        break;
    }
    case 0x51:
    case 0x52: {
        RefGetGameSaveValue(&ref, B_003E0FDC, &B_003D4A60);
        int value = ref.n;
        CRef_Destruct(&ref);
        switch (value) {
        case 0:
            item = 0x51;
            break;
        default:
            item = 0x52;
            break;
        }
        *pitem = item;
        break;
    }
    case 0x53:
    case 0x54: {
        RefGetGameSaveValue(&ref, B_003E0FE0, &B_003D4A60);
        int value = ref.n;
        CRef_Destruct(&ref);
        switch (value) {
        case 0:
            item = 0x53;
            break;
        default:
            item = 0x54;
            break;
        }
        *pitem = item;
        break;
    }
    }
}
