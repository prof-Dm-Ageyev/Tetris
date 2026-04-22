# Заняття 1. TFT LCD Shield та малювання поля

**Тривалість**: 50 хв + 10 хв перерва + 50 хв  
**Вік**: 10–13 років  
**Підсумковий результат**: Ігрове поле Tetris з сіткою і бічними панелями на екрані

> **Для вчителя**: бібліотеки (`MCUFRIEND_kbv`, `Adafruit GFX`, `Adafruit TouchScreen`)
> вже встановлені на комп'ютерах учнів. Перевір це заздалегідь.
> Детальна таблиця підключення.

---

## Мета заняття

- Зрозуміти систему координат і формат кольорів RGB565.
- Навчитися малювати текст, прямокутники і сітку на TFT-дисплеї.
- **Результат**: `tetris.ino` — файл проекту з намальованим полем.

---

## Матеріали

| Файл | Опис |
|------|------|
| `tetris_L01.ino` | ✅ Готовий стан проекту після цього заняття (старт Заняття 2) |
| `hello_lcd.ino` | Перший тест: вивести текст і прямокутники |
| `code_template_01.md` | 📋 Шаблони коду для учнів (тільки для копіювання) |
| `teach-code_template_01.md` | 🎓 Шаблон для вчителя (позначено: копіювати / набирати) |
| `students/` | Матеріали для учнів (роздатковий матеріал) |
| `slides/` | Слайди презентації |

---

## Розклад заняття

### Частина 1 — 50 хвилин

**Теорія (15 хв)**

TFT LCD Shield — плата-розширення, яка кріпиться прямо зверху на Arduino без дротів.
Піни підключаються автоматично через з'єднувачі.

Система координат (240 × 320 пікселів, портретна орієнтація):
```
(0,0) ──── x ──► (239,0)
  │
  y
  ▼
(0,319)
```

Кольори RGB565: 16 біт = 5 біт R + 6 біт G + 5 біт B.

| Константа | Значення | Колір |
|-----------|---------|-------|
| `0x0000` | чорний | фон |
| `0xFFFF` | білий | рамка |
| `0x07FF` | блакитний | фігура I |
| `0xF800` | червоний | фігура Z |

**Демо (15 хв)** — копіюмо та запускаємо `hello_lcd.ino` разом з учнями (обговорюємо, експерементуємо ).

Ключові функції Adafruit_GFX:

| Функція | Що робить |
|---------|-----------|
| `tft.fillScreen(color)` | Заповнити весь екран |
| `tft.fillRect(x, y, w, h, color)` | Закрашений прямокутник |
| `tft.drawRect(x, y, w, h, color)` | Лише контур |
| `tft.setCursor(x, y)` + `tft.print(...)` | Текст |

**Обговорення (10 хв)**: поле Tetris = 10 × 20 клітинок × 16 пікселів = 160 × 320 пікселів.  
Відступ зліва: `(240 − 160) / 2 = 40` пікселів.

Учні відкривають **новий скетч** в Arduino IDE: `File → New`, зберегти як `tetris`.

#### Крок 1 — Підключення бібліотеки і оголошення об'єкта (3 хв)
✏️ **Набираємо самостійно:**
```cpp
#include Adafruit_GFX
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
```

#### Крок 2 — Константи поля і кольорів (3-7 хв)
✏️ **Копіюємо з `code_template_01.md` / Набираємо самостійно:**
```cpp
const uint8_t  BOARD_W = 10;
const uint8_t  BOARD_H = 20;
const uint16_t CELL    = 16;
const uint16_t FX      = (240 - BOARD_W * CELL) / 2;  // = 40

const uint16_t COL_BG    = 0x0000;
const uint16_t COL_GRID  = 0x18C3;
const uint16_t COL_FRAME = 0xFFFF;
const uint16_t COL_PANEL = 0x0841;
const uint16_t COL_TEXT  = 0xFFFF;
```

#### Крок 3 — Кольори фігур (3 хв)
📋 **Копіюємо з `code_template_01.md`:**
```cpp
const uint16_t PIECE_COLORS[7] = { ... };
```
---

### Перерва — 10 хвилин

---

### Частина 2 — 50 хвилин


#### Крок 4 — Ініціалізація дисплея (5 хв)
✏️ **Набираємо самостійно:**
```cpp
void initDisplay() {
  uint16_t id = tft.readID();
  tft.begin(id);
  tft.setRotation(0);
  tft.fillScreen(COL_BG);
  tft.setTextWrap(false);
}
```

#### Крок 5 — Малювання клітинки (5 хв)
✏️ **Набираємо самостійно:**
```cpp
void drawCell(uint8_t col, uint8_t row, uint16_t color) {
  tft.fillRect(FX + col * CELL + 1, row * CELL + 1, CELL - 2, CELL - 2, color);
}

void clearCell(uint8_t col, uint8_t row) {
  drawCell(col, row, COL_BG);
  tft.drawRect(FX + col * CELL, row * CELL, CELL, CELL, COL_GRID);
}
```

#### Крок 6 — Малювання поля (10 хв)
✏️ **Набираємо самостійно:** (Копіюємо)
```cpp
void drawField() {

    tft.fillRect(0, 0, FIELD_LEFT, 320, COL_STATUS);
    tft.fillRect(FIELD_LEFT + FIELD_W, 0, FIELD_LEFT, 320, COL_STATUS);
    tft.drawRect(FIELD_LEFT - 1, 0, FIELD_W + 2, FIELD_H, COL_FRAME);
    tft.drawFastVLine(FIELD_LEFT - 2, 0, 320, COL_FRAME);
    tft.drawFastVLine(FIELD_LEFT + FIELD_W + 1, 0, 320, COL_FRAME);

    for (uint8_t row = 0; row < BOARD_H; ++row) {
        for (uint8_t col = 0; col < BOARD_W; ++col) {
            int16_t x = FIELD_LEFT + col * CELL_SIZE;
            int16_t y = row * CELL_SIZE;
            tft.drawRect(x, y, CELL_SIZE, CELL_SIZE, COL_GRID);
        }
    }
}
```

#### Крок 7 — setup() і завантаження (5 хв)
✏️ **Набираємо самостійно:**
```cpp
void setup() {
   initDisplay();
   drawField();
}
void loop() {}
```
Завантажити на плату: `Sketch → Upload`.

#### Крок 8 — Підписи на панелях (8 хв)
✏️ **Набираємо самостійно:**
```cpp
void drawPanels() {
  tft.setTextColor(COL_TEXT); tft.setTextSize(1);
  tft.setCursor(2, 8);   tft.print("SCORE");
  tft.setCursor(2, 22);  tft.print("0");

  int16_t rx = FX + BOARD_W * CELL + 3;
  tft.setCursor(rx, 8);  tft.print("LEVEL");
  tft.setCursor(rx, 22); tft.print("1");

  tft.setCursor(rx, 40); tft.print("LINES");
  tft.setCursor(rx, 54); tft.print("0");
}
```
#### Крок 9 — setup() і завантаження (2 хв)
✏️ **Набираємо самостійно:**
```cpp
void setup() {
   initDisplay();
   drawField();
   drawPanels();    // <= Додамо
}
void loop() {}
```
Завантажити на плату: `Sketch → Upload`.


#### Крок 9 — Самостійне завдання (5 хв)
Дивись розділ "Завдання для учнів" нижче.

---

## Завдання для учнів

1. Намалюй фігуру **I** (4 блоки в рядок) блакитним кольором (`0x07FF`) на полі.
2. Намалюй фігуру **O** (2×2) жовтим кольором (`0xFFE0`).
3. Стери один блок через `clearCell()` — чи відновилась сітка?
4. Додай напис зі своїм іменем на лівій панелі.

---

## Ключові поняття

- `readID()` + `begin(id)` — ініціалізація контролера ILI9341
- `FX = (240 − 160) / 2 = 40` — поле по центру екрана
- `fillRect(x+1, y+1, CELL-2, CELL-2, color)` — клітинка з відступом для сітки
- 200 клітинок: від `tft.drawRect()` у вкладеному циклі

> **Наступний урок**: додамо фігурки та падіння!  

## Kahoot (10 хв)

> **Наступний урок**: додамо фігурки та падіння!
