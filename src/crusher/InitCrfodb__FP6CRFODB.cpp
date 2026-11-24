// 0x13CEB8 InitCrfodb
#include "crfodb.h"
extern "C" void func_00183F08();

void InitCrfodb__FP6CRFODB(void *arg0)
{
    func_00183F08();
    CRFODB *crfodb = (CRFODB *)arg0;
    crfodb->idLootDefault = 0x2BC;
    crfodb->kind = -1;
    crfodb->field_0x18C = 15.0f;
}
