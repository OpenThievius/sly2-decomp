#include "fbsprite.h"
extern "C" {
void PlayRootSpriteLabelIndex(SPRITE *, int, int);

void PlayRootSpriteLabel(SPRITE *sprite, int label) {
    if (sprite->fRoot) {
        int index = 0;
        if (label != 0x314) {
            for (index = 0; index < sprite->clabel; index++) {
                if (label == sprite->labels[index].id) break;
            }
            if (index >= sprite->clabel) index = 0;
        }
        PlayRootSpriteLabelIndex(sprite, index, label);
    }
}
}
