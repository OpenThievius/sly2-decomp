// SPDX-License-Identifier: GPL-3.0-or-later
struct AMBBASE {
    char pad0[0xC];
    /* 0xC: the vtable pointer */
    virtual void AddRef();          /*  1: AMB_AddRef */
    virtual void Release();         /*  2: AMB_Release */
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual int Slot8();
    virtual void Slot9();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
};

struct AMB : AMBBASE {
    float field_0x10;
    char pad14[0x40 - 0x14];
    int field_0x40;
    float uVol;
    char pad48[0x50 - 0x48];
    unsigned short grf;
    unsigned short fPending;
};

extern "C" void SetAmbGrf(AMB *pamb, int grfMask, int grfValue);

struct AMBREF {
    AMB *pamb;
    AMBREF(AMB *target) { pamb = target; pamb->AddRef(); }
    ~AMBREF() { pamb->Release(); }
};

extern "C" void UpdateAmb(AMB *pamb)
{
    AMBREF ref(pamb);
    if (pamb->grf & 0x200)
        pamb->Slot16();
    else
        pamb->uVol = pamb->field_0x10;
    unsigned short grf = pamb->grf;
    if (grf & 1) {
        pamb->Slot9();
        if (pamb->Slot8() == 1)
            SetAmbGrf(pamb, 0x400, 0x400);
    } else if (pamb->field_0x40 != 0) {
        if (grf & 8) {
            pamb->Slot10();
            pamb->field_0x40 = 0;
            SetAmbGrf(pamb, 0x1DFF, 0);
        } else {
            if (grf & 0x1C00)
                pamb->Slot14();
            if (pamb->fPending != 0)
                return;
            if (pamb->grf & 0x1F0) {
                pamb->Slot13();
                SetAmbGrf(pamb, 0x1F0, 0);
            }
            grf = pamb->grf;
            if (grf & 2) {
                pamb->Slot11();
                SetAmbGrf(pamb, 2, 0);
            } else if (grf & 4) {
                pamb->Slot12();
                SetAmbGrf(pamb, 4, 0);
            }
        }
    } else if (pamb->fPending == 0 && !(grf & 0x200)) {
        SetAmbGrf(pamb, 0x1FFF, 0);
    }
}
