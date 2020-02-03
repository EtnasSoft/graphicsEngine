#include "../src/ProductionCode.h"
#include "../lib/unity/unity.h"
#include "../lib/unity/unity_fixture.h"

TEST_GROUP(ProductionCode);

//sometimes you may want to get at local data in a module.
//for example: If you plan to pass by reference, this could be useful
//however, it should often be avoided


TEST_SETUP(ProductionCode) {
}

TEST_TEAR_DOWN(ProductionCode) {
}

TEST(ProductionCode, sum_ShouldReturnTheSumOfTwoIntegersParams) {
    //This should be true because setUp set this up for us before this test
    int a = 10,
      b = 20,
      expected = 30;

    TEST_ASSERT_EQUAL_INT(expected, sum(a, b));
}
