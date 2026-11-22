// SPDX-License-Identifier: GPL-3.0-or-later
// Unaligned 8-byte store (ldl/ldr, sdl/sdr): a by-value struct of bytes.
#include "jtzap.h"
void SetZapContinuation(JTZAP *zap, BYTES8 continuation)
{
    zap->continuation = continuation;
}
