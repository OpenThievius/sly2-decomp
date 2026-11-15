struct VT1C4228 { char pad[0x18]; short delta; short index; void (*fn)(void *, int, int, int, int **, int); };
struct Obj1C4228 { char pad[0xC]; VT1C4228 *vt; };
struct Locals1C4228 { int *args[2]; int gap[2]; int values[2]; };
extern "C" void func_001C4228(Obj1C4228 *obj, int first, int second)
{
    int *args[2];
    args[0] = &first;
    args[1] = &second;
    obj->vt->fn((char *)obj + obj->vt->delta, 12, 0, 2, args, 0);
}
