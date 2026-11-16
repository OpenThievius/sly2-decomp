// SPDX-License-Identifier: GPL-3.0-or-later
struct AMB;
// The instance's ambient sound is held through a reference pointer (StopSpriteInstance clears it with VirtualRefPtr_Assign); reading it goes through
// the conversion operator.
struct AMBREF {
    AMB *pamb;
    operator AMB *() const { return pamb; }
};
struct SPRITEINST { char pad[8]; short ilabel; short pad2; float t; int fPaused; AMBREF ramb; };
struct SPRITE { char pad[8]; SPRITEINST *ainst; };
extern "C" void PauseAmb(AMB *);

extern "C" void PauseSpriteInstance(SPRITE *psprite, int iinst)
{
    psprite->ainst[iinst].fPaused = 1;
    if (psprite->ainst[iinst].ramb) PauseAmb(psprite->ainst[iinst].ramb);
}
