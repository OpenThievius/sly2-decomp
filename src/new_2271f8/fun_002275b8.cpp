struct RGBA4_2275B8 {
    unsigned char c[4];
    RGBA4_2275B8() {}
    RGBA4_2275B8(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        c[0] = r; c[1] = g; c[2] = b; c[3] = a;
    }
    ~RGBA4_2275B8() {}
};
extern "C" RGBA4_2275B8 func_002275B8(int kind)
{
    RGBA4_2275B8 color;
    switch (kind) {
    case 0x35:
        color = RGBA4_2275B8(0x33, 0x66, 0x99, 0x7F);
        break;
    case 0x37:
        color = RGBA4_2275B8(0x33, 0x99, 0x33, 0x7F);
        break;
    case 0x36:
        color = RGBA4_2275B8(0x99, 0x33, 0x66, 0x7F);
        break;
    case 0x3F:
        color = RGBA4_2275B8(0x99, 0x33, 0x33, 0x7F);
        break;
    case 0x3C:
        color = RGBA4_2275B8(0x99, 0x33, 0x99, 0x7F);
        break;
    default:
        color = RGBA4_2275B8(0x66, 0x66, 0x66, 0x7F);
        break;
    }
    return color;
}
