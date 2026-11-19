static inline float Min(float a, float b) { return b < a ? b : a; }
static inline float Max(float a, float b) { return b > a ? b : a; }

extern "C" void CombineColorTransforms(unsigned char *parentMul, unsigned char *parentAdd, unsigned char *slotMul,
                                       unsigned char *slotAdd, unsigned char *outMul, unsigned char *outAdd)
{
    int i;
    float pm;
    float sm;
    float mul;
    float pa;
    float add;

    for (i = 0; i < 4; i++) {
        pm = (float)((int)parentMul[i] - 0x7F) * 0.007874016f;
        sm = (float)((int)slotMul[i] - 0x7F) * 0.007874016f;
        pm = Max(Min(pm, 1.0f), -1.0f);
        sm = Max(Min(sm, 1.0f), -1.0f);
        mul = Min(pm * sm, 1.0f);
        pa = (float)parentAdd[i] - 127.0f;
        add = pm * ((float)slotAdd[i] - 127.0f) + pa;
        add = Min(add, 128.0f);
        outMul[i] = (unsigned char)(int)(Max(mul, -1.0f) * 127.0f + 128.0f);
        outAdd[i] = (unsigned char)(int)(Max(add, -127.0f) + 127.0f);
    }
}
