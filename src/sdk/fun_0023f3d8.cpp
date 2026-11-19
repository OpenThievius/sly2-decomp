// SPDX-License-Identifier: GPL-3.0-or-later
extern "C" {
struct SortItem {
    int field0;
    int field4;
    int key;
};
struct SortList {
    SortItem **items;
    unsigned count;
};
struct SortState {
    SortList list;
    SortList sorted;
};
void func_00240328(void) __attribute__((noreturn));
void func_00240050(SortState *, SortList *);
void func_0023F2D8(SortState *, SortList *);
void free(void *);

#define SWAP_ITEMS(first, second) do { SortItem *temporary = first; first = second; second = temporary; } while (0)

static inline int CompareKeys(SortItem *left, SortItem *right) {
    return left->key - right->key;
}

static inline void HeapSort(SortList *list) {
    SortItem **items = list->items;
    unsigned count = list->count;
    unsigned remaining = count;
    unsigned index;

    while (remaining > 0) {
        remaining--;
        for (index = remaining; 2 * index + 1 < count;) {
            if (2 * index + 2 < count && CompareKeys(items[2 * index + 2], items[2 * index + 1]) > 0
                && CompareKeys(items[2 * index + 2], items[index]) > 0) {
                SWAP_ITEMS(items[index], items[2 * index + 2]);
                index = 2 * index + 2;
            } else if (CompareKeys(items[2 * index + 1], items[index]) > 0) {
                SWAP_ITEMS(items[index], items[2 * index + 1]);
                index = 2 * index + 1;
            } else {
                break;
            }
        }
    }
    while (count > 1) {
        count--;
        SWAP_ITEMS(items[0], items[count]);
        for (index = 0; 2 * index + 1 < count;) {
            if (2 * index + 2 < count && CompareKeys(items[2 * index + 2], items[2 * index + 1]) > 0
                && CompareKeys(items[2 * index + 2], items[index]) > 0) {
                SWAP_ITEMS(items[index], items[2 * index + 2]);
                index = 2 * index + 2;
            } else if (CompareKeys(items[2 * index + 1], items[index]) > 0) {
                SWAP_ITEMS(items[index], items[2 * index + 1]);
                index = 2 * index + 1;
            } else {
                break;
            }
        }
    }
}

SortItem **func_0023F3D8(SortState *state, unsigned expected) {
    if (state->list.count != expected)
        func_00240328();
    func_00240050(state, &state->sorted);
    if (state->list.count + state->sorted.count != expected)
        func_00240328();
    HeapSort(&state->sorted);
    func_0023F2D8(state, &state->sorted);
    free(state->sorted.items);
    return state->list.items;
}
}
