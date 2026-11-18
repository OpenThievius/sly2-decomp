#include "sly2.h"
extern "C" {
void UpperizePchz__FPc(char *);
unsigned int strlen(const char *);
char *strcat(char *, const char *);
extern const char RO_STR_002A4F00[];
}

extern "C" int CpchzTokenizePath__FPc(char *pchzPath)
{
    UpperizePchz__FPc(pchzPath);
    int cch = strlen(pchzPath);
    if (cch != 0 && (unsigned char)pchzPath[cch - 1] != '\\' && (unsigned char)pchzPath[cch - 1] != '/') {
        strcat(pchzPath, RO_STR_002A4F00);
        cch = strlen(pchzPath);
    }
    unsigned char *pbEnd = (unsigned char *)pchzPath + cch;
    char *pchWrite = pchzPath;
    unsigned char *pbRead = (unsigned char *)pchzPath;
    int cComponent = 0;
    int cchComponent = 0;
    int cchMax = 8;
    while (pbRead < pbEnd) {
        unsigned char ch = *pbRead;
        switch (ch) {
        case '/':
        case '\\':
            if (cchComponent != 0) {
                *pchWrite++ = 0;
                cchComponent = 0;
                cchMax = 8;
                cComponent++;
            }
            break;
        case '.':
            if (cchComponent != 0 && cchMax == 8) {
                *pchWrite++ = '.';
                cchComponent = 0;
                cchMax = 3;
            }
            break;
        case ';':
            if (cchComponent != 0 && pbRead == pbEnd - 2 && pbRead[1] == '1') {
                *pchWrite++ = pbRead[0];
                pbRead = pbEnd - 1;
                *pchWrite++ = pbRead[0];
                cchComponent += 2;
                break;
            }
            goto copy;
        default:
        copy:
            if (cchComponent < cchMax) {
                if ((*pbRead >= 'A' && *pbRead <= 'Z') || (*pbRead >= '0' && *pbRead <= '9'))
                    *pchWrite = *pbRead;
                else
                    *pchWrite = '_';
                pchWrite++;
                cchComponent++;
            }
            pbRead++;
            continue;
        }
        pbRead++;
    }
    if (cchComponent != 0) {
        *pchWrite = 0;
        cComponent++;
    }
    return cComponent;
}
