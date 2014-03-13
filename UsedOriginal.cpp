#include "UsedOriginal.h"
#include "Used.c"

long UsedOriginal::add(long a, long b) {
    return Used_add(a, b);
}

long UsedOriginal::subtract(long a, long b) {
    return Used_subtract(a, b);
}

UsedOriginal* UsedOriginal::instance() {
    static UsedOriginal instance;
    return &instance;
}
