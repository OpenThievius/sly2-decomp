#include "sly.h"
extern "C" {
int func_001409B8();
int GetSlyExposeMode(SLY *self) {
    int result;
    int mode = func_001409B8();
    if (mode == -1) {
        int state = self->jts;
        if (state < 7) {
            if (state < 5 && state != 1)
                { result = -1; goto done; }
            goto one;
        }
        if (state == 9) {
one:
            return 1;
        }
        { result = -1; goto done; }
    }
    return mode;
done:
    return result;
}
}
