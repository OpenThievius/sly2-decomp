/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The exception-handling frame tables' two record kinds, as the unwinder's lookup (func_0023FE78) and its record decoder
   (func_0023F938) read them. A record opens with its length (the bytes after the word). An EHFDE (a frame description entry) holds
   the distance back to its EHCIE (the common information it shares: func_0023F938 reads its augmentation string), the first address it
   covers and the size of the range; its instructions start at 0x10. Names and layout from what the code does (the DWARF
   frame-table format is public). Readers: func_0023F938 (length of the CIE is not read there), func_0023FE78. */
#ifndef SLY2_EHFRAME_H
#define SLY2_EHFRAME_H
struct EHCIE {
    int length;
};
struct EHFDE {
    int length;
    int cieOffset;           /* the distance from this word back to the CIE's 0x4 */
    unsigned pcBegin;        /* func_0023FE78 compares its limit with it */
    unsigned char unknown_0xC[4]; /* the size of the range it covers */
};
#endif
