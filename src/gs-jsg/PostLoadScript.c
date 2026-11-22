/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "script.h"

void PostLoLoad(struct SCRIPT *script);
void ResolveScriptObjects(struct SCRIPT *script);

void PostLoadScript(struct SCRIPT *script) {
    PostLoLoad(script);
    ResolveScriptObjects(script);
}
