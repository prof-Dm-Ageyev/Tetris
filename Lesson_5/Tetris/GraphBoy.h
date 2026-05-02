#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

const uint8_t  Brd_W    = 10;
const uint8_t  Brd_H    = 20;
const uint16_t FldW    = Brd_W * 16;          
const uint16_t FldH    = Brd_H * 16;          
const uint16_t FldLeft = (240 - FldW) / 2;     

// Кольори
const uint16_t COL_BG     = 0x0000; // чорний
const uint16_t COL_GRID   = 0x18C3; // темно-сірий
const uint16_t COL_FRAME  = 0xFFFF; // білий
const uint16_t COL_STATUS = 0x0841; // темний синій (бокові панелі)
const uint16_t COL_TEXT   = 0xFFFF; // білий текст

struct GraphBoy{
bool display[Brd_W][Brd_H];
byte block[4][4][4];

void memDisplay(short int x,short int y); 
void drawDisplay();
void drawPoint(uint8_t col, uint8_t row);
void drawPoint(uint8_t col, uint8_t row, uint16_t color);
void wipePoint(uint8_t col, uint8_t row);
void drawLabel(int16_t panelLeft, int16_t y, const char* text);
void drawField();
void drawPanels();
void begin();
void clearDisplay();
void generateBlock(byte block[4][4][4], byte arr1[4][4], byte arr2[4][4], byte arr3[4][4], byte arr4[4][4]);
void memBlock(byte arr[4][4], int x, int y);
bool checkCollision(int x, int y);
bool checkBlockCollision(byte arr[4][4], int x, int y);
};

void GraphBoy::generateBlock(byte block[4][4][4], byte arr1[4][4], byte arr2[4][4], byte arr3[4][4], byte arr4[4][4] ) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      block[0][i][j] = arr1[i][j];
      block[1][i][j] = arr2[i][j];
      block[2][i][j] = arr3[i][j];
      block[3][i][j] = arr4[i][j];
    }
  }
}

void GraphBoy::memBlock(byte arr[4][4], int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (arr[j][i] == 1) {
        memDisplay(x + i, y + j);
      }
    }
  }
}

bool GraphBoy::checkCollision(int x, int y){
    if(x < Brd_W && x > -1){
        if(display[x][y] == 1 || y > (Brd_H - 1)) return true;
        else return false;
    }
    else return true;
}

bool GraphBoy::checkBlockCollision(byte arr[4][4], int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (arr[j][i] == 1 && (checkCollision(x + i, y + j))) return true;
    }
  }
  return false;
}

void GraphBoy::drawDisplay(){
    for(int x = 0; x < Brd_W; x++){
        for(int y = 0; y < Brd_H; y++){
           if (display[x][y]) drawPoint(x, y); 
           else wipePoint(x, y);
        }
    }
}

void GraphBoy::drawPanels(){
   drawLabel(0, 10, "SCORE");
    tft.setTextSize(2);
    tft.setCursor(4, 26);
    tft.print("0");

    drawLabel(0, 74, "LINES");
    tft.setTextSize(2);
    tft.setCursor(4, 90);
    tft.print("0");

    drawLabel(FldLeft + FldW, 10, "LEVEL");
    tft.setTextSize(2);
    tft.setCursor(FldLeft + FldW + 4, 26);
    tft.print("1");
	
  // Стрілка ліво (◄): торкнись лівої панелі → фігура рухається вліво
  tft.fillTriangle(4, 160,  30, 144,  30, 176, COL_TEXT);
  // Стрілка право (►): торкнись правої панелі → фігура рухається вправо
  tft.fillTriangle(235, 160,  209, 144,  209, 176, COL_TEXT);
}

void GraphBoy::clearDisplay(){
 /*tft.fillRect(FldLeft + FldW, 0, FldLeft, 320, COL_BG);
  drawField();
  drawPanels();*/
  for (uint8_t row = 0; row < Brd_H; ++row) {
        for (uint8_t col = 0; col < Brd_W; ++col) {
            wipePoint(col,row);
        }
    }
}

void GraphBoy::begin(){
  uint16_t id = tft.readID();
   // if (id == 0xD3D3 || id == 0xFFFF || id == 0x0000) id = 0x9341;
    tft.begin(id);
    tft.setRotation(0);
    tft.fillScreen(COL_BG);
    drawField();
    drawPanels();
}

void GraphBoy::drawPoint(uint8_t col, uint8_t row){
  drawPoint(col, row, 0xFFE0);
}

void GraphBoy::drawPoint(uint8_t col, uint8_t row, uint16_t color){
  int16_t x = FldLeft + col * 16;
    int16_t y = row * 16;

    tft.fillRect(x + 1, y + 1, 16 - 2, 16 - 2, color);
}

void GraphBoy::wipePoint(uint8_t col, uint8_t row){
  drawPoint(col, row, COL_BG);

    int16_t x = FldLeft + col * 16;
    int16_t y = row * 16;
    tft.drawRect(x, y, 16, 16, COL_GRID);
}

void GraphBoy::drawLabel(int16_t panelLeft, int16_t y, const char* text) {
    tft.setTextColor(COL_TEXT);
    tft.setTextSize(1);
    tft.setCursor(panelLeft + 4, y);
    tft.print(text);
}

void GraphBoy::drawField() {
    tft.fillRect(0, 0, FldLeft, 320, COL_STATUS);
    tft.fillRect(FldLeft + FldW, 0, FldLeft, 320, COL_STATUS);
    tft.drawRect(FldLeft - 1, 0, FldW + 2, FldH, COL_FRAME);
    tft.drawFastVLine(FldLeft - 2, 0, 320, COL_FRAME);
    tft.drawFastVLine(FldLeft + FldW + 1, 0, 320, COL_FRAME);

    for (uint8_t row = 0; row < Brd_H; ++row) {
        for (uint8_t col = 0; col < Brd_W; ++col) {
            int16_t x = FldLeft + col * 16;
            int16_t y = row * 16;
            tft.drawRect(x, y, 16, 16, COL_GRID);
        }
    }
}