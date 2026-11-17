struct AttachPaseg1944C8 { char pad[8]; int kind; int sub; char pad2[0x44]; void *a54; void *a58; void *a5c; void *a60; void *a64; };

extern "C" void *PasegAttachBase(AttachPaseg1944C8 *attach, int *secondary)
{
    void *paseg;
    int isSecondary = 0;
    switch (attach->kind) {
    case 0:
        paseg = (attach->sub == 5) ? attach->a60 : attach->a54;
        break;
    case 1:
        paseg = attach->a58;
        break;
    case 8:
        if (attach->sub < 11) {
            if (attach->sub > 8) {
                paseg = attach->a64;
                isSecondary = 1;
            } else {
                paseg = 0;
            }
        } else {
            paseg = 0;
        }
        break;
    default:
        paseg = 0;
        break;
    }
    *secondary = isSecondary;
    return paseg;
}
