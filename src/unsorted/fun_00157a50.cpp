// qsort comparator of SortRenderRecords' sorted pointer array: far to near by depth, ties by record address
struct RENDER_RECORD {
    int bucket;
    float depth;
    int field8;
    int fieldC;
};

extern "C" {
int func_00157A50(RENDER_RECORD **arg0, RENDER_RECORD **arg1) {
    RENDER_RECORD *left = *arg0;
    RENDER_RECORD *right = *arg1;
    float leftKey = left->depth;
    float rightKey = right->depth;
    if (rightKey < leftKey) {
        return -1;
    }
    if (leftKey < rightKey) {
        return 1;
    }
    return (int)(left - right);
}
}
