#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C" {
    #include "Used.h"
    #include "Using.h"
}

#include "UsedFake.h"

TEST_GROUP(Used) {
    void setup() {
        UsedFake::setReal();
    }
};
TEST(Used, add) {
    LONGS_EQUAL(5678, Used_add(5555, 123));
}
TEST(Used, subtract) {
    LONGS_EQUAL(1, Used_subtract(-34567, -34568));
}

TEST_GROUP(Using_withUsedRealCode) {
    void setup() {
        UsedFake::setReal();
    }
};
TEST(Using_withUsedRealCode, calculate) {
    LONGS_EQUAL(-141, Using_calculate(57, 312));
}

TEST_GROUP(Using_withUsedMockCode) {
    void setup() {
        UsedFake::setMock();
    }
};
TEST(Using_withUsedMockCode, calculate) {
    LONGS_EQUAL(-141, Using_calculate(57, 312));
}

int main(int ac, char** av)
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}

