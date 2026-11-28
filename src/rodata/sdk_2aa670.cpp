// SPDX-License-Identifier: GPL-3.0-or-later
// Retail .rodata 0X2AA670-0X2AA6A0 (piece rodata/sdk), one global per Splat label: written by scripts/build/make_data_files.py,
// listed in config/us/data_files.tsv (link_image.py links it at its address and checks the bytes).

// data-ok: retail's bytes at 0X2AA670
extern const struct {
    char m0[44];
    char m1[4];
} D_002AA670 = {
    "snd_SendIOPCommandNoWait: continuing (%d).\012",
    ""
};
