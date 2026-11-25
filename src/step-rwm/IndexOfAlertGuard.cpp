#include "sly2.h"
#include "stepguard.h"
int IndexOfAlertGuard(ALERT *owner, STEPGUARD *guard)
{
int count = owner->cguard; int index = 0; if (count > 0) { STEPGUARD **item = owner->apguard; do { if (guard == *item) return index; index++; item++; } while (index < count); } return -1;
}
