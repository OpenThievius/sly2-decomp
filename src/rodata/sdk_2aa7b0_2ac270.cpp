// SPDX-License-Identifier: GPL-3.0-or-later
// Retail .rodata 0X2AC270-0X2AC290 (piece rodata/sdk_2aa7b0), one global per Splat label: written by scripts/build/make_data_files.py,
// listed in config/us/data_files.tsv (link_image.py links it at its address and checks the bytes).

// data-ok: retail's bytes at 0X2AC270
extern const struct {
    char m0[12];
    char m1[4];
    unsigned int m2[4];
} D_002AC270 = {
    "rom0:ROMVER",
    "",
    {0x1e1f1c1f, 0x1f1f1e1f, 0x1f1e1f1e, 0}
};
