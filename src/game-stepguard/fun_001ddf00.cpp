#include "jobmenu.h"
extern "C" {
extern JOBMENU B_003DA3C0;
extern char B_003DD490;
char *PchzStringFromId(void *, int);
char *strcpy(char *, char *);

/* the job list's page 1 row: the task's text (TASK::labelId, a string id) */
void func_001DDF00(char *dest, int index) {
    if (index < B_003DA3C0.cent) {
        strcpy(dest, PchzStringFromId(&B_003DD490, B_003DA3C0.aent[index].ptask->labelId));
    }
}
}
