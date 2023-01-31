#include "cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

MyColorPicker::MyColorPicker() { }


HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  HSLAPixel color(100, 0.96, 0.48);
  return color;
}