// SPDX-License-Identifier: GPL-3.0-or-later
// Retail .rodata 0X2AC5F0-0X2AC678 (piece rodata/sdk_2aa7b0), one global per Splat label: written by scripts/build/make_data_files.py,
// listed in config/us/data_files.tsv (link_image.py links it at its address and checks the bytes).

// data-ok: retail's bytes at 0X2AC5F0
extern const char D_002AC5F0[48] = "skiped macroblock in I picure is not allowed";

// data-ok: retail's bytes at 0X2AC620
extern const char D_002AC620[32] = "Invalid macroblock_type code: 0";

// data-ok: retail's bytes at 0X2AC640
extern const unsigned int D_002AC640[14] = {0x61766e49, 0x2064696c, 0x7263616d, 0x6f6c626f, 0x615f6b63, 0x65726464, 0x695f7373, 0x6572636e, 0x746e656d, 0x646f6320, 0x78302865, 0x78383025, 41, 0};
