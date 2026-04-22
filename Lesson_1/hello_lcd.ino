// hello_lcd.ino — Урок 1: перший скетч, виводимо текст на TFT-дисплей
//
// Бібліотеки: MCUFRIEND_kbv, Adafruit GFX
// Плата:      Arduino Uno + 2.4" TFT LCD Shield (ILI9341)
//
// Завдання:
//   1. Завантажте скетч на Arduino.
//   2. Змініть текст на своє ім'я.
//   3. Змініть колір тексту: червоний = 0xF800, жовтий = 0xFFE0.
//   4. Додайте ще один прямокутник іншого кольору.
//   5. Порівняйте fillRect і drawRect — у чому різниця?

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;

void setup() {
    // Зчитуємо ідентифікатор контролера шилда.
    // Деякі шилди повертають некоректний ID — підставляємо ILI9341 вручну.
    uint16_t id = tft.readID();
    if (id == 0xD3D3 || id == 0xFFFF || id == 0x0000) {
        id = 0x9341;
    }

    tft.begin(id);          // ініціалізуємо контролер дисплея
    tft.setRotation(0);     // портретна орієнтація (0°): 240 × 320
    tft.fillScreen(0x0000); // заповнюємо екран чорним

    // --- Виводимо вітальний текст ---
    tft.setTextColor(0xFFFF); // білий текст (RGB565: 1111 1111 1111 1111)
    tft.setTextSize(2);        // розмір шрифту × 2 (базовий — 6×8 пікселів)
    tft.setCursor(20, 60);     // ставимо курсор у точку (x=20, y=60)
    tft.print("Hello!");

    tft.setTextColor(0x07E0); // зелений текст
    tft.setTextSize(1);
    tft.setCursor(20, 90);
    tft.print("Arduino + TFT LCD");

    // --- Малюємо фігури ---
    // Контур прямокутника (тільки рамка)
    tft.drawRect(20, 110, 80, 40, 0x07E0); // зелений контур

    // Заповнений прямокутник
    tft.fillRect(120, 110, 80, 40, 0xF800); // червоний прямокутник

    // Прямокутник з округленими кутами
    tft.fillRoundRect(20, 170, 180, 40, 8, 0x001F); // синій, радіус кута 8

    tft.setTextColor(0xFFFF);
    tft.setTextSize(1);
    tft.setCursor(30, 183);
    tft.print("Округлений кут");
}

void loop() {
    // Нічого не робимо в циклі — малювання відбулося один раз у setup()
}
