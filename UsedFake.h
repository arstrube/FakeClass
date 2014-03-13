#ifndef USEDFAKE_H_
#define USEDFAKE_H_

class UsedFake {
public:
    virtual long add(long a, long b) = 0;
    virtual long subtract(long a, long b) = 0;
    static void setDummy();
    static void setMock();
    static void setStub();
    static void setReal();
};

#endif
