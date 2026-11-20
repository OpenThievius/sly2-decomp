// SPDX-License-Identifier: GPL-3.0-or-later
extern "C" {
struct MathException {
    int type;
    const char *name;
    double arg1;
    double arg2;
    double retval;
    int err;
};
double __ieee754_log10(double);
int dpcmp(double, double);
int *func_002401C8(void);
int func_00249C80(double);
int matherr(MathException *);
extern const double RO_002AC130;
extern const int RO_002AC138;

double logf(double x)
{
    MathException exc;
    double z = __ieee754_log10(x);
    int version = RO_002AC138;
    if (version == -1 || func_00249C80(x) != 0) {
        return z;
    }
    if (dpcmp(x, 0.0) <= 0) {
        exc.err = 0;
        exc.name = "log10";
        exc.arg1 = x;
        exc.arg2 = x;
        if (version == 0) {
            exc.retval = -3.4028234663852886e+38;
        } else {
            exc.retval = 0.0 - RO_002AC130;
        }
        if (dpcmp(x, 0.0) == 0) {
            exc.type = 2;
            if (RO_002AC138 == 2) {
                *func_002401C8() = 0x22;
            } else if (matherr(&exc) == 0) {
                *func_002401C8() = 0x21;
            }
        } else {
            exc.type = 1;
            if (RO_002AC138 == 2) {
                *func_002401C8() = 0x21;
            } else if (matherr(&exc) == 0) {
                *func_002401C8() = 0x21;
            }
        }
        if (exc.err != 0) {
            *func_002401C8() = exc.err;
        }
        return exc.retval;
    }
    return z;
}
}
