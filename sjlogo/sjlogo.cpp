#ifdef ARDUINO
#include "Arduino.h"
#else
#include "fakearduino.h"
#endif

#include "AMGBigTetris.h"

#include <stdio.h>
#include <string.h>

#include "image.h"

#define WIDTH 10
#define HEIGHT 20

int tick = 0;

const int rowWrapWidths[] = {
  STRIDE-10,
  STRIDE-10,
  STRIDE-10,
  STRIDE-10,
  STRIDE-10,
  STRIDE-10,
  STRIDE-10,
  STRIDE-10,
  STRIDE-10,
  STRIDE-10,
  STRIDE,
  STRIDE,
  STRIDE,
  STRIDE,
  STRIDE,
  STRIDE,
  STRIDE,
  STRIDE,
  STRIDE,
  STRIDE
};

int offsets[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int directions[20] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

void incrementWithBounce() {
  for (int i = 0; i < 20; i++) {
    offsets[i] = offsets[i] + directions[i];
    if (offsets[i] == rowWrapWidths[i] - WIDTH || offsets[i] == 0) {
      directions[i] *= -1;
    }
  }
}

void incrementWithWrap() {
  for (int i = 0; i < 20; i++) {
    offsets[i] = (offsets[i] + directions[i]) % rowWrapWidths[i];
  }
}

void loop() {
  tick++;

  if (tick % 10 == 0) {
    // incrementWithBounce();
    incrementWithWrap();
  }

  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      int index = (j*STRIDE+(i+offsets[j])%rowWrapWidths[j]);
      int* color = (int*)&palette[(int)image[index]];
      setCartesianPixelColor(i, j, color[0], color[1], color[2]);
    }
  }
  updateDisplay();
}
