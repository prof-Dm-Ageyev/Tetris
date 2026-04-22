# Шаблони коду — Заняття 1

Ці фрагменти **скопіюй у свій `tetris.ino`** — набирати вручну не потрібно.

---

## Блок 1: PIECE_COLORS — кольори 7 фігур

Замінює рядок `const uint16_t PIECE_COLORS[7] = { ... };` у секції КОНСТАНТИ.

```cpp
// Кольори 7 фігур Tetris: I, J, L, O, S, T, Z
const uint16_t PIECE_COLORS[7] = {
  0x07FF,  // I — блакитний
  0x001F,  // J — синій
  0xFD20,  // L — помаранчевий
  0xFFE0,  // O — жовтий
  0x07E0,  // S — зелений
  0xF81F,  // T — фіолетовий
  0xF800   // Z — червоний
};
```

> **RGB565**: 16 бітів = 5 біт R + 6 біт G + 5 біт B.  
> Онлайн-конвертер: https://rgbto565.com — спробуй задати свої кольори!

---

## Блок 2: Константи 

Вставь перелік констант у свій `tetris.ino`.

```cpp
// Розміри поля (збігаються з AppConfig.h)
const uint8_t  BOARD_W    = 10;
const uint8_t  BOARD_H    = 20;
const uint16_t CELL_SIZE  = 16;
const uint16_t FIELD_W    = BOARD_W * CELL_SIZE;          // 160 пікселів
const uint16_t FIELD_H    = BOARD_H * CELL_SIZE;          // 320 пікселів
const uint16_t FIELD_LEFT = (240 - FIELD_W) / 2;          // 40 пікселів
```

