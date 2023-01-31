#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image i;        
  i.readFromFile("/workspaces/CS 225/release-f22-main/mp_stickers/tests/alma.png");
  i.scale(1500,2000);
  i.writeToFile("/workspaces/CS 225/release-f22-main/mp_stickers/saturate.png");
  return 0;
}
