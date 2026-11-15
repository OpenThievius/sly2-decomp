extern "C" {
int IdCurrentLevel();
int func_0013FAD0(int count, short *ids) {
    int id = IdCurrentLevel();
    if (id == -1) return 1;
    int index = 0;
    do {
        index++;
        if (index >= count) return 0;
    } while (*ids++ != id);
    return 1;
}
}
