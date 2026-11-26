#include "sly2.h"
#include "cref.h"
#include "lo.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
/* class 126 of retail's class table: an LO (0x110 bytes) whose subclasses 127 to 131 add slots 49 and 50 */
struct LO126 : LO {
    virtual void Slot49();
    virtual void Slot50();
};
extern "C" CRef func_0010DB78(LO126 *obj, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    obj->Slot50();
    return refResult;
}
