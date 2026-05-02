#include "Blocks.h"
#include "GraphBoy.h"

GraphBoy gb;

#include <TouchScreen.h>
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void restorePins() {
  pinMode(XP, OUTPUT);  digitalWrite(XP, HIGH);
  pinMode(YM, OUTPUT);  digitalWrite(YM, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
}

bool readTouch(int16_t &sx, int16_t &sy) {
  TSPoint p = ts.getPoint();
  restorePins();
  if (p.z < 200 || p.z > 1000) return false;
  sy = map(p.y, TS_TOP, TS_BOT, 0, 319);
  sx = map(p.x, TS_LEFT, TS_RT, 0, 239);
  Serial.print("sx= ");Serial.print(sx);Serial.print(" sy= ");Serial.println(sy); 
  return (sx >= 0 && sx < 240 && sy >= 0 && sy < 320);
}

// Зони: 1=ліво, 2=право, 3=поворот, 4=вниз, 5=рестарт
// Зони: 4=ліво, 5=право, 1=поворот, 6=вниз, 2=рестарт
uint8_t getKey(){
  int16_t sx, sy;
  if (!readTouch(sx, sy))  return 0;
  
  if (sx < (int16_t)FldLeft)           return 4;
  if (sx >= (int16_t)(FldLeft + FldW)) return 5;
  if (sy >= (int16_t)(FldH * 3 / 4)) return 6;
  return 1;  
}

int x = 2, y = -1;
int rot =0; 

void setup() {
  Serial.begin(9600);
  gb.begin();
  Serial.println("Started");

}

void drawBlock(byte arr[4][4], int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (arr[j][i] == 1) {
        gb.drawPoint(x + i, y + j);
}}}}

void wipeBlock(byte arr[4][4], int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (arr[j][i] == 1) {
        gb.wipePoint(x + i, y + j);
}}}}

void makeMove(){
  if (getKey()==4){
     x--;
  }
  if (getKey()==5){
      x++;
  }
  
}



void loop() {
  
  makeMove();
  gb.drawDisplay();
  drawBlock(gb.block[rot], x,y);
  y++;
   if (y>Brd_H)y=;
   delay(200);
}