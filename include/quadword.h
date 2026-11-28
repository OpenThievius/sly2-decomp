/* SPDX-License-Identifier: GPL-3.0-or-later */
/* QUADWORD, one 128-bit quadword as four words (little-endian, the first word is the low one): the unit the GS upload reads a bitmap's pixels
   in (BMP::cqw, include/bmp.h: FBuildUploadBitmapGifs, PqwVifsBitmapUpload) and so the element of a table of pixels defined as data
   (src/rodata/puffer-slotheap_27a790.cpp, _29a790.cpp). g++ 2.95 has no 128-bit constants, so a quadword is written as its words. C and C++. */
#ifndef SLY2_QUADWORD_H
#define SLY2_QUADWORD_H
struct QUADWORD {
    unsigned int word[4];
};

#if defined(__mips__)
typedef char check_QUADWORD_size[(sizeof(struct QUADWORD) == 16) ? 1 : -1];
#endif
#endif
