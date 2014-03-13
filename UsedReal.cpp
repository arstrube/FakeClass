#include "UsedReal.h"
#include "Used.c"

long UsedReal::add(long a, long b) {
    return Used_add(a, b);
}

long UsedReal::subtract(long a, long b) {
    return Used_subtract(a, b);
}

UsedReal* UsedReal::instance() {
    static UsedReal instance;
    return &instance;
}
