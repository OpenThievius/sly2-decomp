// SPDX-License-Identifier: GPL-3.0-or-later
extern "C" {
struct EhContext {
    void *pad0;
    void **dynamicHandlerChain;
    void *info;
};
extern EhContext *(*D_002C60BC)(void);
void __terminate(void);

void __sjthrow(void) {
    EhContext *context = D_002C60BC();
    void ***handlerChain = &context->dynamicHandlerChain;
    void ***cleanup = (void ***)&(*handlerChain)[1];
    if (cleanup[0] != 0) {
        double store[200];
        void **buffer = (void **)store;
        buffer[1] = 0;
        buffer[0] = (void *)*handlerChain;
        if (!__builtin_setjmp((void **)&buffer[2])) {
            *handlerChain = buffer;
            while (cleanup[0] != 0) {
                void (*function)(void *, int) = (void (*)(void *, int))cleanup[0][1];
                void *argument = cleanup[0][2];
                cleanup[0] = (void **)cleanup[0][0];
                function(argument, 2);
            }
            *handlerChain = (void **)buffer[0];
        } else {
            __terminate();
        }
    }
    if (context->info == 0 || (*handlerChain)[0] == 0)
        __terminate();
    void *jumpBuffer = &(*handlerChain)[2];
    *handlerChain = (void **)**handlerChain;
    __builtin_longjmp((void **)jumpBuffer, 1);
}
}
