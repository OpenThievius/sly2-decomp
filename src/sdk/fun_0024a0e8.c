// SPDX-License-Identifier: GPL-3.0-or-later
typedef union { float value; unsigned int word; } ieee_float_shape_type_24A0E8;
#define GET_FLOAT_WORD(i, d) do { ieee_float_shape_type_24A0E8 gf_u; gf_u.value = (d); (i) = gf_u.word; } while (0)
#define SET_FLOAT_WORD(d, i) do { ieee_float_shape_type_24A0E8 sf_u; sf_u.word = (i); (d) = sf_u.value; } while (0)
float copysignf(float x, float y);
static const float two25 = 3.355443200e+07f;
static const float twom25 = 2.9802322388e-08f;
static const float huge = 1.0e+30f;
static const float tiny = 1.0e-30f;
float func_0024A0E8(float x, int n) {
    int k, ix;
    GET_FLOAT_WORD(ix, x);
    k = (ix & 0x7f800000) >> 23;
    if (k == 0) {
        if ((ix & 0x7fffffff) == 0) return x;
        x *= two25;
        GET_FLOAT_WORD(ix, x);
        k = ((ix & 0x7f800000) >> 23) - 25;
        if (n < -50000) return tiny * x;
    }
    if (k == 0xff) return x + x;
    k = k + n;
    if (k > 0xfe) return huge * copysignf(huge, x);
    if (k > 0) {
        SET_FLOAT_WORD(x, (ix & 0x807fffff) | (k << 23));
        return x;
    }
    if (k <= -25) {
        if (n > 50000) return huge * copysignf(huge, x);
        else return tiny * copysignf(tiny, x);
    }
    k += 25;
    SET_FLOAT_WORD(x, (ix & 0x807fffff) | (k << 23));
    return x * twom25;
}
