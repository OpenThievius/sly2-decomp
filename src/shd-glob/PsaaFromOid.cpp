struct SAA {
    unsigned char unknown_0x0[0x14];
    /* 0x14 */ int oid;
    unsigned char unknown_0x18[0x18];
    /* 0x30 */ int fStop;
    unsigned char unknown_0x34[0xC];
    /* 0x40 */ SAA *next;
};
extern "C" {
extern SAA *B_003E159C;
SAA *PsaaFromOid(int oid)
{
    char frame[0x10] __attribute__((aligned(16)));
    if (oid == -1)
        return 0;
    SAA *psaa = B_003E159C;
    while (psaa && psaa->fStop == 0) {
        if (psaa->oid == oid)
            return psaa;
        psaa = psaa->next;
    }
    return 0;
}
}
