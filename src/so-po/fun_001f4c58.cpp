#include "so.h"
#include "xf.h"
extern "C" XF *func_001F4C58(SO *arg0, int arg1, int arg2) {
    XF *var_a0;
    int var_v0;
    int var_v1;
    int temp_a3;

    temp_a3 = arg0->cxf;
    var_v1 = 0;
    if (temp_a3 > 0) {
        var_a0 = arg0->axf;
        do {
            var_v1++;
            if (var_a0->id == arg1) {
                if (var_a0->dof == arg2) {
                    return var_a0;
                }
            }
            var_v0 = var_v1 < temp_a3;
            var_a0++;
        } while (var_v0 != 0);
    }
    return 0;
}
