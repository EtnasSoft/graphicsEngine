#include <stdlib.h>
#include "../../lib/unity/unity_fixture.h"

void cls(void);

static void RunAllTests(void) {
  RUN_TEST_GROUP(ProductionCode);
}

void cls(void) {
  system("@cls||clear");
}

int main(int argc, const char * argv[]) {
  cls();
  return UnityMain(argc, argv, RunAllTests);
}
