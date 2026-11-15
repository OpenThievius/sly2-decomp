// SPDX-License-Identifier: GPL-3.0-or-later
extern "C" {
struct EhInfo {
    void *match;
};
typedef void *(*EhMatcher)(void *, void *, void *);
EhInfo **__get_eh_info(void);

int __eh_rtime_match(void *runtimeType) {
    EhInfo *info = *__get_eh_info();
    EhMatcher matcher = (EhMatcher)info->match;
    void *result;
    if (matcher == 0)
        return 0;
    result = matcher(info, runtimeType, 0);
    return result != 0;
}
}
