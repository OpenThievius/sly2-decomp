#include "cfilelocation.h"
extern "C" int CFileLocation_Cb(CFileLocation *);

extern "C" int FUN_0018c1e8(MOVIE *source) {
 CFileLocation location;
 location.kind = 2;
 location.Clear();
 if (location.Set(source) != 0) return CFileLocation_Cb(&location);
 return 0;
}
