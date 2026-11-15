// SPDX-License-Identifier: GPL-3.0-or-later
typedef struct MpegState {
    int done;
    char pad4[0xA8 - 0x4];
    int countA8;
    int countAC;
    int countB0;
    int indexB4;
    int indexB8;
    int indexBC;
    char padC0[0xE8 - 0xC0];
    int targetE8;
    unsigned int imageBuffer;
    char padF0[0x184 - 0xF0];
    int mode;
    char pad188[0x834 - 0x188];
    int stop;
    char pad838[0x858 - 0x838];
    int keepGoing;
    char pad85C[0x878 - 0x85C];
    int aborted;
} MpegState;

typedef struct MpegHandle {
    char pad0[0x40];
    MpegState *state;
} MpegHandle;

void func_0024FA90(MpegState *state, const char *format, unsigned int value);
int func_00236960(const char *format, ...);
int func_002544C8(MpegState *state);
int func_0024C360(MpegHandle *handle);
int func_0024B760(MpegHandle *handle, int first, int second);

int func_0024ACD8(MpegHandle *handle)
{
    MpegState *state = handle->state;
    int result = 0;
    int kind = 1;

    state->done = 0;
    if (state->imageBuffer & 0x3F) {
        func_0024FA90(state, "image buffer needs to be aligned to 64byte boundary(0x%08x)", state->imageBuffer);
        return -1;
    }
    if (state->aborted) {
        func_00236960("Need to re-setup libipu since sceMpegGetPicture was aborted\n");
        return -1;
    }
    state->stop = 0;
    do {
        if (result != -1) {
            do {
                kind = func_002544C8(state);
                if (kind < 0) {
                    return -1;
                }
                if (kind == 0) {
                    break;
                }
                if (state->mode == state->targetE8) {
                    break;
                }
            } while (state->keepGoing);
        }
        switch (kind) {
        case 0:
            func_0024C360(handle);
            state->done = 1;
            break;
        case 1:
            state->indexBC = 0;
            state->indexB8 = 0;
            state->indexB4 = 0;
            result = func_0024B760(handle, 0, state->countA8);
            state->indexB4++;
            break;
        case 2:
            result = func_0024B760(handle, state->indexB8, state->countAC);
            state->indexB8++;
            break;
        case 3:
        case 4:
            result = func_0024B760(handle, state->indexBC, state->countB0);
            state->indexBC++;
            break;
        }
        if (state->aborted) {
            func_00236960("sceMpegGetPicture is aborted\n");
            return -1;
        }
        if (state->stop) {
            return 1;
        }
    } while (state->done == 0);
    return 1;
}
