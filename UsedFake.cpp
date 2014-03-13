#include "UsedFake.h"
#include "CppUTestExt/MockSupport.h"

class UsedFakeInterface {
public:
    virtual long add(long a, long b) = 0;
    virtual long subtract(long a, long b) = 0;
};

class UsedDummy : public UsedFakeInterface {
public:
    virtual long add(long, long) { return 0; }
    virtual long subtract(long, long) { return 0; }
    static UsedDummy* instance() {
        static UsedDummy instance;
        return &instance;
    }
};

namespace C {
    #include "Used.c"
}
    
class UsedReal : public UsedFakeInterface {
public:
    virtual long add(long a, long b) { return C::Used_add(a, b); }
    virtual long subtract(long a, long b) { return C::Used_subtract(a, b); }
    static UsedReal* instance() {
        static UsedReal instance;
        return &instance;
    }
};

static UsedFakeInterface* fake = UsedDummy::instance();

class UsedMock : public UsedFakeInterface {
public:
    virtual long add(long a, long b) {
        mock().actualCall("Used_add")
              .withParameter("a", (int) a)
              .withParameter("b", (int) b);
        return (long) mock().returnValue().getIntValue(); 
    }
    virtual long subtract(long a, long b) {
        mock().actualCall("Used_subtract")
              .withParameter("a", (int) a)
              .withParameter("b", (int) b);
        return mock().returnValue().getIntValue(); 
    }
    static UsedMock* instance() {
        static UsedMock instance;
        return &instance;
    }
};

#include <cstdio>

class UsedStub : public UsedFakeInterface {
public:
    virtual long add(long a, long b) {
        printf("Used_add(%ld, %ld) was called\n", a, b);
        return a + b;
    }
    virtual long subtract(long a, long b) {
        printf("Used_subtract(%ld, %ld) was called\n", a, b);
        return a - b;
    }
    static UsedStub* instance() {
        static UsedStub instance;
        return &instance;
    }
};

void UsedFake::setDummy() { fake = UsedDummy::instance(); }

void UsedFake::setMock() { fake = UsedMock::instance(); }

void UsedFake::setStub() { fake = UsedStub::instance(); }

void UsedFake::setReal() { fake = UsedReal::instance(); }

extern "C" long Used_add(long a, long b) { return fake->add(a, b); }

extern "C" long Used_subtract(long a, long b) { return fake->subtract(a, b); }
