#ifndef USEDORIGINAL_H_
#define USEDORIGINAL_H_

#include "UsedFake.h"

class UsedOriginal : public UsedFake {
public:
    virtual long add(long a, long b);
    virtual long subtract(long a, long b);
    static UsedOriginal* instance();
};

#endif
