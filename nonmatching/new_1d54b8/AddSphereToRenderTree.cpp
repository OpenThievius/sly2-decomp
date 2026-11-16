#include "vu0inline.h"
#include "ps2inline.h"
struct RTB_1D6508;
struct BITS_1D6508 {
    unsigned long low : 32;
    long kind : 4;
    long grf : 8;
    unsigned long flag : 1;
    unsigned long rest : 19;
};
struct RTE_1D6508 {
    float x, y, z, radius;
    union {
        float sRadius;
        BITS_1D6508 bits;
    };
    RTB_1D6508 *child;
    int pad;
};
struct RTB_1D6508 { RTE_1D6508 aentry[3]; float x, y, z, radius; unsigned long bits; RTB_1D6508 *child; RTB_1D6508 *next; };
struct TREE_1D6508 { char pad[0x3E5C]; RTB_1D6508 *root; };
extern "C" {
RTB_1D6508 *AllocRenderTreeNode(TREE_1D6508 *);
extern float g_2a7870;
}


static inline float GMin(float a, float b) { return a < b ? a : b; }

extern "C" RTE_1D6508 *AddSphereToRenderTree(TREE_1D6508 *tree, QW pos, int grf, float radius, float sRadius)
{
    RTE_1D6508 * result;
    RTB_1D6508 *pblock = tree->root;
    RTE_1D6508 *pfree;
    RTB_1D6508 *pb;
    if (pblock == 0)
        return 0;
    while (pblock != 0) {
        float best = g_2a7870;
        RTB_1D6508 *pnext = 0;
        pfree = 0;
        pb = pblock;
        for (;;) {
            RTB_1D6508 *chain = pb->next;
            RTE_1D6508 *pe = (RTE_1D6508 *)pb;
            for (unsigned int i = 0; i < 4; i++, pe++) {
                switch (pe->bits.kind) {
                case -1:
                    if (pfree == 0)
                        pfree = pe;
                    break;
                case 1: {
                    QW offset = VectorSub(VectorFromQuad(pos), *(QW *)pe);
                    float r = pe->radius;
                    float dist = LaneX(SqrtX(SquaredLength(offset)));
                    if (dist + radius <= r) {
                        float s = pe->sRadius;
                        if ((s == 1e10f || dist + sRadius <= s) && (grf & ~pe->bits.grf) == 0) {
                            float m = GMin(100000.0f, s);
                            float d = r * m * m;
                            if (d < best) {
                                best = d;
                                pnext = pe->child;
                            }
                        }
                    }
                    break;
                }
                }
            }
            if (chain == 0)
                break;
            pb = chain;
        }
        if (pnext == 0) {
            if (pfree == 0) {
                RTB_1D6508 *pnew = AllocRenderTreeNode(tree);
                pb->next = pnew;
                pfree = (RTE_1D6508 *)pnew;
            }
            pfree->sRadius = sRadius;
            *(QW *)pfree = pos;
            pfree->radius = radius;
            pfree->bits.grf = grf;
                { result = pfree; goto done; }
        }
        pblock = pnext;
    }
    { result = 0; goto done; }
done:
    return result;
}
