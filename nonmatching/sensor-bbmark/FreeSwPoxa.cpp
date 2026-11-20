struct VT_1337D0 {
    char pad0[0x1B0];
    short delta1B0;
    short unused1B2;
    void (*bind)(void *, void *);
    char pad1B8[0x1F0 - 0x1B8];
    short delta1F0;
    short unused1F2;
    int (*query)(void *);
};
struct OBJ_1337D0 { char pad0[0xC]; VT_1337D0 *vt; char pad10[0xEC - 0x10]; int tag; };
struct NODE_1337D0 { void *mq; NODE_1337D0 *next; int pad8; OBJ_1337D0 *obj; };
struct POXA_1337D0 { char pad0[0x60]; OBJ_1337D0 *obj; NODE_1337D0 *head; int pad68; void *mq; long flags; };
struct ENTRY_1337D0 { int flag; POXA_1337D0 *owner; int pad8; };
struct SW_1337D0 {
    char pad0[0x3CD0];
    int count;
    ENTRY_1337D0 *tables[3];
    char slotheapA[0x3CF8 - 0x3CE0];
    char slotheapB[0x3D10 - 0x3CF8];
    char dlA[0x3D1C - 0x3D10];
    char dlB[0x3D28 - 0x3D1C];
    char dlC[0x3D34 - 0x3D28];
    char dlD[1];
};
extern "C" {
int FFindDlEntry(void *, void *);
void FreeSlotheapPv(void *, void *);
void FreeSwMqList__FP2SWP2MQ(SW_1337D0 *, void *);
void *PoxExtractFromPoxa(SW_1337D0 *, int, POXA_1337D0 *);
void RemoveDlEntry(void *, void *);
void func_001F5078(OBJ_1337D0 *);
void *memmove(void *, const void *, unsigned int);
void FreeSwPoxa(SW_1337D0 *sw, POXA_1337D0 *poxa) {
    NODE_1337D0 *node;
    NODE_1337D0 *current;
    OBJ_1337D0 *object;
    OBJ_1337D0 *other;
    void *extracted;
    ENTRY_1337D0 *first;
    ENTRY_1337D0 *entry;
    ENTRY_1337D0 *base;
    int table;
    void *slotheap;
    node = poxa->head;
    if (node != 0) {
        do {
            object = poxa->obj;
            object->vt->bind((char *)object + object->vt->delta1B0, node->obj);
            other = node->obj;
            other->vt->bind((char *)other + other->vt->delta1B0, poxa->obj);
            extracted = PoxExtractFromPoxa(sw, node->obj->tag, poxa);
            if (node->mq != 0) {
                if (node->obj->vt->query((char *)node->obj + node->obj->vt->delta1F0) == 0) {
                    func_001F5078(node->obj);
                }
                FreeSwMqList__FP2SWP2MQ(sw, node->mq);
            }
            current = node->next;
            FreeSlotheapPv(sw->slotheapB, node);
            FreeSlotheapPv(sw->slotheapB, extracted);
            node = current;
        } while (node != 0);
    }
    FreeSwMqList__FP2SWP2MQ(sw, poxa->mq);
    RemoveDlEntry(sw->dlA, poxa);
    if (FFindDlEntry(sw->dlB, poxa) != 0) {
        RemoveDlEntry(sw->dlB, poxa);
    }
    if ((poxa->flags & 1) == 1) {
        RemoveDlEntry(sw->dlC, poxa);
    }
    if (poxa->flags & 2) {
        RemoveDlEntry(sw->dlD, poxa);
    }
    slotheap = sw->slotheapA;
    for (table = 0; table < 3; table++) {
        base = sw->tables[table];
        entry = base;
        for (;;) {
            while (entry->owner != poxa) {
                entry++;
            }
            if (entry->flag != 0) {
                break;
            }
            first = entry;
            entry++;
        }
        memmove(first, first + 1, (entry - first) * sizeof(ENTRY_1337D0) - sizeof(ENTRY_1337D0));
        memmove(entry - 1, entry + 1, (sw->count - (entry - base)) * sizeof(ENTRY_1337D0) - sizeof(ENTRY_1337D0));
    }
    sw->count -= 2;
    FreeSlotheapPv(slotheap, poxa);
}
}
