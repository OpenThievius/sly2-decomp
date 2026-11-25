#include "jobmenu.h"
extern "C" {
extern JOBMENU B_003DA3C0;
extern char B_003DD490;
char *PchzStringFromId(void *, int);
char *strcpy(char *, char *);

/* the job list's page 0 row: the job's name (JOB's word at 0x6C, a string id) */
void func_001DDEA0(char *dest, int index) {
    if (index < B_003DA3C0.cent) {
        strcpy(dest, PchzStringFromId(&B_003DD490, B_003DA3C0.aent[index].pjob->field_0x6C));
    }
}
}
