// SPDX-License-Identifier: GPL-3.0-or-later
// Retail .rodata 0X2AC6C8-0X2AC728 (piece rodata/sdk_2aa7b0), one global per Splat label: written by scripts/build/make_data_files.py,
// listed in config/us/data_files.tsv (link_image.py links it at its address and checks the bytes).

// data-ok: retail's bytes at 0X2AC6C8
extern const char D_002AC6C8[24] = "vertical size > 2800";

// data-ok: retail's bytes at 0X2AC6E0
extern const struct {
    char m0[36];
    char m1[4];
} D_002AC6E0 = {
    "_chroma_format needs to be 1: 420",
    ""
};

// data-ok: retail's bytes at 0X2AC708
extern const struct {
    char m0[28];
    char m1[4];
} D_002AC708 = {
    "Unsupported profile/level",
    ""
};
