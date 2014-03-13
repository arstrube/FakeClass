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
    void teardown() {
        mock().clear();
    }
};
TEST(Using_withUsedMockCode, calculate) {
    mock().expectOneCall("Used_add")
          .withParameter("a", 57)
          .withParameter("b", 57)
          .andReturnValue(114);
    mock().expectOneCall("Used_subtract")
          .withParameter("a", 312)
          .withParameter("b", 57)
          .andReturnValue(255);
    mock().expectOneCall("Used_subtract")
          .withParameter("a", 114)
          .withParameter("b", 255)
          .andReturnValue(-141);
    LONGS_EQUAL(-141, Using_calculate(57, 312));
    mock().checkExpectations();
}

int main(int ac, char** av)
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}

