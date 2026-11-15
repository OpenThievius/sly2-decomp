/* SPDX-License-Identifier: GPL-3.0-or-later */
struct AMB { char p0[0x88]; int pan[6]; char p1[0x3BC - 0xA0]; unsigned dirty; };
extern "C" void SetAmbGrf(AMB *, int, int);
extern "C" void SetAmbSlotPan(AMB *amb, unsigned slot, int degrees)
{
    if (slot < 6) {
        int pan = degrees % 360;
        if (pan < 0)
            pan += 360;
        if (pan != amb->pan[slot]) {
            amb->dirty |= 1 << slot;
            amb->pan[slot] = pan;
            SetAmbGrf(amb, 0x100, 0x100);
        }
    }
}
