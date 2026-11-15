// SPDX-License-Identifier: GPL-3.0-or-later
extern "C" {
struct SortEntry {
    int pad0;
    int pad4;
    int key;
};
struct SortVector {
    SortEntry **array;
    unsigned count;
};
struct SortObject {
    int result;
    unsigned count;
    SortVector sorted;
};
void func_00240328(void) __attribute__((noreturn));
void func_00240050(SortObject *, SortVector *);
void func_0023F2D8(SortObject *, SortVector *);
void free(void *);

static inline int CompareEntries(SortEntry *left, SortEntry *right) {
    return left->key - right->key;
}

static inline void SiftDown(SortEntry **entries, unsigned index, unsigned count) {
    unsigned child = index * 2;
    while (child + 1 < count) {
        SortEntry *temporary;
        if (child + 2 < count) {
            if (CompareEntries(entries[child + 2], entries[child + 1]) > 0) {
                if (CompareEntries(entries[child + 2], entries[index]) > 0) {
                    temporary = entries[index];
                    entries[index] = entries[child + 2];
                    entries[child + 2] = temporary;
                    index = child + 2;
                    child = index * 2;
                    continue;
                }
            }
        }
        if (CompareEntries(entries[child + 1], entries[index]) <= 0)
            break;
        temporary = entries[index];
        entries[index] = entries[child + 1];
        entries[child + 1] = temporary;
        index = child + 1;
        child = index * 2;
    }
}

int func_0023F3D8(SortObject *object, unsigned expected) {
    unsigned original = object->count;
    SortVector *vector = &object->sorted;
    if (original != expected)
        func_00240328();
    func_00240050(object, vector);
    if (object->count + object->sorted.count != original)
        func_00240328();
    SortEntry **entries = vector->array;
    unsigned count = vector->count;
    if (count != 0) {
        unsigned index = count;
        do {
            index--;
            SiftDown(entries, index, count);
        } while (index != 0);
        if (count >= 2) {
            SortEntry **last = entries + count - 1;
            do {
                count--;
                SortEntry *temporary = entries[0];
                *last = temporary;
                entries[0] = *last;
                SiftDown(entries, 0, count);
                last--;
            } while (count > 1);
        }
    }
    func_0023F2D8(object, vector);
    free(object->sorted.array);
    return object->result;
}
}
