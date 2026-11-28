// SPDX-License-Identifier: GPL-3.0-or-later
// Retail .rodata 0X2AB8D0-0X2AB8E0 (piece rodata/sdk_2aa7b0), one global per Splat label: written by scripts/build/make_data_files.py,
// listed in config/us/data_files.tsv (link_image.py links it at its address and checks the bytes).

// data-ok: retail's bytes at 0X2AB8D0
extern const unsigned int D_002AB8D0[2] = {0x776f70, 0};

// data-ok: retail's bytes at 0X2AB8D8
extern const unsigned int D_002AB8D8[2] = {0, 0x7ff80000};
