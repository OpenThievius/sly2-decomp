// SPDX-License-Identifier: GPL-3.0-or-later
extern "C" {
typedef union { double value; struct { unsigned int lsw; unsigned int msw; } parts; unsigned long l; } ieee_double_shape_type;
#define EXTRACT_WORDS(ix0, ix1, d) do { ieee_double_shape_type ew_u; ew_u.value = (d); (ix0) = ew_u.parts.msw; (ix1) = ew_u.parts.lsw; } while (0)
#define GET_HIGH_WORD(i, d) do { ieee_double_shape_type gh_u; gh_u.value = (d); (i) = gh_u.parts.msw; } while (0)
#define SET_HIGH_WORD(d, v) do { ieee_double_shape_type sh_u; sh_u.value = (d); sh_u.parts.msw = (v); (d) = sh_u.value; } while (0)
static const double two54 = 1.80143985094819840000e+16;
static const double ivln10 = 4.34294481903251816668e-01;
static const double log10_2hi = 3.01029995663611771306e-01;
static const double log10_2lo = 3.69423907715893078616e-13;
static const double zero = 0.0;
double __ieee754_log(double x);

double __ieee754_log10(double x)
{
    double y, z;
    int i, k, hx;
    unsigned int lx;

    EXTRACT_WORDS(hx, lx, x);

    k = 0;
    if (hx < 0x00100000) {
        if (((hx & 0x7fffffff) | lx) == 0)
            return -two54 / zero;
        if (hx < 0)
            return (x - x) / zero;
        k -= 54;
        x *= two54;
        GET_HIGH_WORD(hx, x);
    }
    if (hx >= 0x7ff00000)
        return x + x;
    k += (hx >> 20) - 1023;
    i = ((unsigned int)k & 0x80000000) >> 31;
    hx = (hx & 0x000fffff) | ((0x3ff - i) << 20);
    y = (double)(k + i);
    SET_HIGH_WORD(x, hx);
    z = y * log10_2lo + ivln10 * __ieee754_log(x);
    return z + y * log10_2hi;
}
}
