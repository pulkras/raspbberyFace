#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "ramfont.c"

typedef unsigned char byte;

byte * screen = (byte *) 0xA000;

#define SCREEN_WIDTH  64
#define SCREEN_HEIGHT 128
#define CHARWIDTH 8
#define CHARHEIGHT 8

#define BYTESPERROW (SCREEN_WIDTH / 8)
#define BYTESPERCHARROW (BYTESPERROW * 8)
#define CHARSPERROW (SCREEN_WIDTH / CHARWIDTH)
#define ROWSPERCOLUMN (SCREEN_HEIGHT / CHARWEIGHT)


// setPixel
// 
// 0 <= x < 64
// 0 <= y < 128
//
// pixel on the screen in white or black at pixel pos x, y
void setPixel(int x, int y, byte b) {
  byte * pb = screen;
  pb += x >> 3;
  pb += y * BYTESPERROW;

  if (b)
      *(pb) |= (B10000000 >> (x & 7)); // ob10000000
  else
      *(pb) &= ~(B10000000 >> (x & 7)); // ob10000000
}

// drawPixel
//
// 0 <= x < 64
// 0 <= y < 128
//
// turns on a screen pixel at pixel pos x, y
void drawPixel(int x, int y) {
  byte * pb = screen;
  pb += x >> 3;
  pb += y * BYTESPERROW;
  *(pb) |= (B10000000 >> (x & 7)); // ob10000000
}



void drawLine(int x0, int y0, int x1, int y1, byte val) {
  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = (dx > dy ? dx : -dy) / 2, e2;

  while (1) {
    setPixel(x0, y0, val);

    if (x0 == x1 && y0 == y1)
        break;

    e2 = err;

    if (e2 > -dx) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dy) {
      err += dx;
      y0 += sy;
    }
  }

}
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
