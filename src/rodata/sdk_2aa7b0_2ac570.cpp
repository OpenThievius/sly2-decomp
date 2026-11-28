// SPDX-License-Identifier: GPL-3.0-or-later
// Retail .rodata 0X2AC570-0X2AC5B0 (piece rodata/sdk_2aa7b0), one global per Splat label: written by scripts/build/make_data_files.py,
// listed in config/us/data_files.tsv (link_image.py links it at its address and checks the bytes).

// data-ok: retail's bytes at 0X2AC570
extern const struct {
    char m0[36];
    char m1[4];
} D_002AC570 = {
    "Invalid modion type -- ignored(%d)",
    ""
};

// data-ok: retail's bytes at 0X2AC598
extern const struct {
    char m0[20];
    char m1[4];
} D_002AC598 = {
    "intra && skip MB",
    ""
};
