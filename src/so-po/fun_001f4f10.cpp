#include "sly2.h"
struct PMF { s64 v; } __attribute__((packed));
#include "so.h"
#include "oxa.h"
extern "C" char B_003DD490[];
extern PMF RO_002A8278;
extern "C" void QueueSwCallbackOnce(char *, SO *, s64, int);
#define PM (RO_002A8278.v)

void func_001F4F10(SO *so)
{
    OXA *oxa = so->poxa;
    if (oxa->pcontact != 0) {
        QueueSwCallbackOnce(B_003DD490, so, PM, 0);
    } else if ((so->grfso & 0x3000000UL) != 0) {
        for (OX *link = oxa->first; link != 0; link = link->next) {
            if (link->pxp != 0) {
                QueueSwCallbackOnce(B_003DD490, so, PM, 0);
                break;
            }
        }
    }
}
