/* SPDX-License-Identifier: GPL-3.0-or-later */
/* PAIRNODE, a 0x14-byte node of the garbage collector's pair pool (chunks of 0x2000 of them, B_00452098): PpairNew sets words 0x8
   (-1) and 0x10 (0); LinkPairNode packs the chunk and node indexes of its list neighbours into grf. Readers: PpairNew, LinkPairNode. */
#ifndef SLY2_PAIRNODE_H
#define SLY2_PAIRNODE_H
struct PAIRNODE {
    unsigned char unknown_0x0[4];
    int grf;
    int field_0x8;
    unsigned char unknown_0xC[4];
    int field_0x10;
};
#endif
