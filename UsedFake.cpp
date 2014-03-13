#include "UsedFake.h"
#include "UsedOriginal.h"

class UsedDummy : public UsedFake {
public:
    virtual long add(long, long) { return 0; }
    virtual long subtract(long, long) { return 0; }
    static UsedDummy* instance() {
        static UsedDummy instance;
        return &instance;
    }
};

static UsedFake* fakePtr = UsedDummy::instance();

void UsedFake::setDummy() { fakePtr = UsedDummy::instance(); }

void UsedFake::setMock() {}

void UsedFake::setStub() {}

void UsedFake::setReal() { fakePtr = UsedOriginal::instance(); }

extern "C" long Used_add(long a, long b) {
    return fakePtr->add(a, b);
}

extern "C" long Used_subtract(long a, long b) {
    return fakePtr->subtract(a, b);
}
