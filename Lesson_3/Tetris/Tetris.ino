#include "Blocks.h"
#include "GraphBoy.h"
GraphBoy gb;


void setup() {
  // put your setup code here, to run once:
gb.begin();
}

void drawBlock(byte arr[4][4], int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (arr[j][i] == 1) {
        gb.drawPoint(x + i, y + j);
      }
    }
  }
}

void wipeBlock(byte arr[4][4], int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (arr[j][i] == 1) {
        gb.wipePoint(x + i, y + j);
      }
    }
  }
}

void loop() {


}
