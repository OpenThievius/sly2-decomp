/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The world's object lookups: one prototype each, for the sources that find objects in the world (SW, include/sw.h) by id or by
   class. The parameter names follow what the matched callers pass: grffso holds the search kind in its low byte (5: every object of
   the class, 4: by id relative to a context object) and flags above it (0x100, 0x200); cid is a class of retail's class table;
   ploContext the object the search is relative to. Signatures from the matched definitions: PloFindSwObject_thunk (0x15E938),
   PloFindSwObject (0x15E958), CploFindSwObjectsByClass (0x15E9C8). A source includes this header instead of declaring its own
   copy, so a whole file built from several sources sees one declaration (docs/ROADMAP.md item 7, "One prototype per function").
   C++ only. */
#ifndef SLY2_SWFIND_H
#define SLY2_SWFIND_H
#include "sw.h"

extern "C" {
LO *PloFindSwObject(SW *psw, int grffso, int oid, LO *ploContext, void *pownerContext);
LO *PloFindSwObject_thunk(SW *psw, int grffso, int oid, LO *ploContext);
int CploFindSwObjectsByClass(SW *psw, int grffso, int cid, LO *ploContext, int cploMax, LO **aplo);
}

#endif
