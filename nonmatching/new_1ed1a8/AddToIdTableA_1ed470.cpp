struct Bmp { int id; };
extern "C" {
extern int *B_003DD010;
void AddToIdTableA_1ed470(Bmp *bmp) {
    int index = bmp->id % 16381;
    int *slot = &B_003DD010[index];
    goto test;
body:
    index = (index + 1) % 16381;
    slot = &B_003DD010[index];
test:
    if (*slot != 0) goto body;
    *slot = (int)bmp;
}
}
