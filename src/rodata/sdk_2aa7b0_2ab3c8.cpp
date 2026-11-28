// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file).
// Retail .rodata 0X2AB3C8-0X2AB418 (piece rodata/sdk_2aa7b0). Splat's one label covers three objects: the third of sceDmaPutEnv's
// three lookup tables (with D_002AB3A8 and D_002AB3B8: each indexed by one byte of the environment, checked below 10), then two strings
// of the CD library that no label names (the compiler pads the 10-byte table to the next 8-byte boundary, as retail does).

// data-ok: typed from sceDmaPutEnv
extern const unsigned char D_002AB3C8[10] = {0, 2, 3, 0, 0, 0, 0, 0, 0, 0};

// data-ok: retail's bytes at 0X2AB3D8
extern const char D_002AB3D8[40] = "sceCdCbfunc= %d sceCdCbfunc_num= %d\012";

// data-ok: retail's bytes at 0X2AB400
extern const char D_002AB400[24] = "SceCdCallbackThread";
