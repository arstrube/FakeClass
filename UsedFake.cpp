#include "UsedFake.h"
#include "CppUTestExt/MockSupport.h"

class UsedDummy : public UsedFake {
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
    
class UsedReal : public UsedFake {
public:
    virtual long add(long a, long b) { return C::Used_add(a, b); }
    virtual long subtract(long a, long b) { return C::Used_subtract(a, b); }
    static UsedReal* instance() {
        static UsedReal instance;
        return &instance;
    }
};

static UsedFake* fakePtr = UsedDummy::instance();

class UsedMock : public UsedFake {
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

class UsedStub : public UsedFake {
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

void UsedFake::setDummy() { fakePtr = UsedDummy::instance(); }

void UsedFake::setMock() { fakePtr = UsedMock::instance(); }

void UsedFake::setStub() { fakePtr = UsedStub::instance(); }

void UsedFake::setReal() { fakePtr = UsedReal::instance(); }

extern "C" long Used_add(long a, long b) { return fakePtr->add(a, b); }

extern "C" long Used_subtract(long a, long b) { return fakePtr->subtract(a, b); }
