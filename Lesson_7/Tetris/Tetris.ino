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
int acc = 1;
int speed = 20;
int score = 0;
int level = 0;
int lines;

void setup() {
  Serial.begin(9600);
  gb.begin();
  randomSeed(analogRead(0) +
      analogRead(5));
  createBlock(random(0,7));
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
    if(!gb.checkBlockCollision(gb.block[rot], x - 1, y)){ 
      x--;
  }}
  if (getKey()==5){
    if(!gb.checkBlockCollision(gb.block[rot], x + 1, y)){
      x++;
  }}
  if (getKey()==1)
    if (!gb.checkBlockCollision(gb.block[(rot + 1) % 4], x, y)) 
      rot = (rot + 1) % 4;  
  if (getKey()==6) acc = 4;
    else acc = 1;
}

void createBlock(int num){
  x=3; y= -1; rot = random(0,4); 
  if(num == 0) gb.generateBlock(gb.block, I_Block_1, I_Block_2, I_Block_3, I_Block_4);
  if(num == 1) gb.generateBlock(gb.block, Z_Block_1, Z_Block_2, Z_Block_3, Z_Block_4);
  if(num == 2) gb.generateBlock(gb.block, S_Block_1, S_Block_2, S_Block_3, S_Block_4);
  if(num == 3) gb.generateBlock(gb.block, L_Block_1, L_Block_2, L_Block_3, L_Block_4);
  if(num == 4) gb.generateBlock(gb.block, J_Block_1, J_Block_2, J_Block_3, J_Block_4);
  if(num == 5) gb.generateBlock(gb.block, T_Block_1, T_Block_2, T_Block_3, T_Block_4);
  if(num == 6) gb.generateBlock(gb.block, O_Block_1, O_Block_2, O_Block_3, O_Block_4);
}

void loop() {
  if (loss()){
    for (int i = Brd_H; i>=0; i--){
      gb.clearLine(i);
      delay(10);
    }
      gb.drawGameOver();
      delay(2000);
  }
  makeMove();
  if (gb.checkBlockCollision(gb.block[rot], x, y + 1)){
    gb.memBlock(gb.block[rot], x, y);
    lines = gb.fullLine();
    if (lines != 0){
      gb.lines = lines;
      gb.score += lines;
      gb.level += lines;
      gb.updateStatus();
      }
    if (gb.level >4){ 
      speed = speed / 2;
      level =1;
    }       
    createBlock(random(0,7));
  } else y++;
  
  gb.drawDisplay();
  drawBlock(gb.block[rot], x,y);
  delay(speed / acc);
}

bool loss(){
  if (gb.checkBlockCollision(gb.block[rot], x, 0))
  {
    return true;
  } else {
    return false;
  }
}

