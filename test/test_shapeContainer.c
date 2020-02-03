#include "../lib/unity/unity.h" // The testing framework

#include "mock_rectangle.h" // A mock header
#include "shapeContainer.h" // The header for the code we are testing

void test_shape_container_init(void) {
  // Set up known values
  uint16_t length = 4;
  uint16_t width = 3;

  // State, in order of call, what expectations we have, and the expected values
  // to be returned, if any
  rectangleInit_Expect(length, width);

  // Run Actual Function Under Test
  shapeContainerInit(length, width);
}