/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The class flags of one entry of the C library's character table (`_ctype_`, 0x2AA6A0: 257 bytes, entry 0 is for EOF, entry 1 + c is for the character c;
   the library's isalpha, isdigit... read it as `(_ctype_ + 1)[c] & flags`). The values are the ones of the usual newlib layout, proved against
   retail's table by tests/test_tools.py (CtypeTableTests). C and C++. */
#ifndef SLY2_CTYPEFLAGS_H
#define SLY2_CTYPEFLAGS_H
#define CTYPE_UPPER 0x01  /* A-Z */
#define CTYPE_LOWER 0x02  /* a-z */
#define CTYPE_DIGIT 0x04  /* 0-9 */
#define CTYPE_SPACE 0x08  /* tab, newline, vertical tab, form feed, carriage return, space */
#define CTYPE_PUNCT 0x10  /* the printable characters that are neither letters, digits nor space */
#define CTYPE_CONTROL 0x20  /* 0 to 31 and 127 */
#define CTYPE_HEX 0x40  /* a-f and A-F */
#define CTYPE_BLANK 0x80  /* the space itself */
#endif
