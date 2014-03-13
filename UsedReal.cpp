/** IMPORTANT:
  * 1. The C source must be #included in a differenct source from
  *    where the extern "C" wrappers are defined, because the names
  *    would clash. Hence the UsedReal class must be implemented in 
  *    a source of its own.
  * 2. The C source must not be wrapped in extern "C" {}.
  */

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
