#include "../src/ProductionCode.h"
#include "../lib/unity/unity.h"
#include "../lib/unity/unity_fixture.h"

TEST_GROUP(ProductionCode);

//sometimes you may want to get at local data in a module.
//for example: If you plan to pass by reference, this could be useful
//however, it should often be avoided
extern int Counter;

TEST_SETUP(ProductionCode) {
  //This is run before EACH TEST
  Counter = 0x5a5a;
}

TEST_TEAR_DOWN(ProductionCode) {
}

TEST(ProductionCode, FunctionWhichReturnsLocalVariable_ShouldReturnTheCurrentCounterValue) {
    //This should be true because setUp set this up for us before this test
    TEST_ASSERT_EQUAL_HEX(0x5a5a, FunctionWhichReturnsLocalVariable());

    //This should be true because we can still change our answer
    Counter = 0x1234;
    TEST_ASSERT_EQUAL_HEX(0x1234, FunctionWhichReturnsLocalVariable());
}
