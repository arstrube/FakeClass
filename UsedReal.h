#ifndef USEDREAL_H_
#define USEDREAL_H_

#include "UsedFake.h"

class UsedReal : public UsedFake {
public:
    virtual long add(long a, long b);
    virtual long subtract(long a, long b);
    static UsedReal* instance();
};

#endif
