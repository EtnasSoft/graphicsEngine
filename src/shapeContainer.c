#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void shapeContainerInit(uint16_t r_length, uint16_t r_width) {
  rectangleInit(r_length, r_width);
}

bool shapeContainerCalcRect(uint16_t r_length, uint16_t r_width) {
  rectangleInit(r_length, r_width);
  rectangleGetArea();
  rectangleGetPerimeter();
  return rectangleIsSquare();
}