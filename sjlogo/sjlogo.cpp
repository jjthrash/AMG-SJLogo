#ifdef ARDUINO
#include "Arduino.h"
#else
#include "fakearduino.h"
#endif

#include "platform.h"

#include <stdio.h>
#include <string.h>

#include "image.h"

#define WIDTH 10
#define HEIGHT 20

int alpha = 0;
int tick = 0;
int direction = 1;
int offset = 0;

void incrementWithBounce() {
  offset = offset + direction;
  if (offset == STRIDE - WIDTH || offset == 0) {
    direction *= -1;
  }
}

void incrementWithWrap() {
  offset = (offset + direction) % STRIDE;
}

void loop() {
  tick++;

  if (tick % 10 == 0) {
    // incrementWithBounce();
    incrementWithWrap();
  }

  int xoffset = offset;
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      int index = (j*STRIDE+(i+xoffset)%STRIDE);
      int* color = (int*)&palette[(int)image[index]];
      setCartesianPixelColor(i, j, color[0], color[1], color[2]);
    }
  }
  updateDisplay();
}
