struct Bytes24 { char bytes[24]; };
struct BmpHeader {
    union {
        Bytes24 head;
        struct { char unknown_0x0[0x10]; unsigned cb; };
    };
    unsigned paragraphs;
};
extern "C" {
BmpHeader *CopyBmpHeader(BmpHeader *destination, BmpHeader *source) {
    destination->head = source->head;
    destination->paragraphs = (destination->cb + 0xF) >> 4;
    return destination;
}
}
