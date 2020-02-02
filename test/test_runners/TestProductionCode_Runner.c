#include "../../lib/unity/unity.h"
#include "../../lib/unity/unity_fixture.h"

TEST_GROUP_RUNNER(ProductionCode) {
  RUN_TEST_CASE(ProductionCode, FunctionWhichReturnsLocalVariable_ShouldReturnTheCurrentCounterValue);
}