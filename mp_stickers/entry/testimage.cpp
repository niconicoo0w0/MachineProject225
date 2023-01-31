#include "Image.h"

#include <iostream>

int main() {
  Image alma;

  // std::cout << "Using Image::lighten to create `lighten.png`..." << std::endl;
  // alma.readFromFile("../alma.png");
  // alma.lighten(0.2);
  // alma.writeToFile("../lighten.png");

  // std::cout << "Using Image::saturate to create `saturate.png`..." << std::endl;
  // alma.readFromFile("../alma.png");
  // alma.illinify();
  // alma.writeToFile("../saturate.png");

  std::cout << "Using Image::scale to create `scale.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.writeToFile("../scale2x.png");

  

  return 0;
}
