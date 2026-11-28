// SPDX-License-Identifier: GPL-3.0-or-later
// Retail .rodata 0X2AB330-0X2AB368 (piece rodata/sdk_2aa7b0), one global per Splat label: written by scripts/build/make_data_files.py,
// listed in config/us/data_files.tsv (link_image.py links it at its address and checks the bytes).

// data-ok: retail's bytes at 0X2AB330
extern const struct {
    char m0[52];
    char m1[4];
} D_002AB330 = {
    "sceGsDefDispEnv:Not support displaymode for 0x%x!!\012",
    ""
};
