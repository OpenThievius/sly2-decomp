/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" s64 CsgsMatchGrfsgs(s64 wanted, s64 have) {
    s64 matched = wanted & have;
    if (matched != wanted) {
        return 0;
    }
    int count = 0;
    while (matched != 0) {
        matched &= matched - 1;
        count += 1;
    }
    return count;
}
