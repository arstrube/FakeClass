#include "UsedOriginal.h"

class UsedFake {
public:
    virtual long add(long a, long b) = 0;
    virtual long subtract(long a, long b) = 0;
};

class UsedDummy : public UsedFake {
public:
    virtual long add(long, long) { return 0; }
    virtual long subtract(long, long) { return 0; }
    static UsedDummy* instance() {
        static UsedDummy instance;
        return &instance;
    }
};

UsedFake* fakePtr = UsedDummy::instance();

extern "C" long Used_add(long a, long b) {
    return fakePtr->add(a, b);
}

extern "C" long Used_subtract(long a, long b) {
    return fakePtr->subtract(a, b);
}
