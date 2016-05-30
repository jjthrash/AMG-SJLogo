/*
Copyright 2014 Joel Lienhard  (joel@mclien.de  joel@sisam42.de)

Modified by the Alamance Makers Guild 5/6/2016 (Jeff Wright, Schae Stewart, Danny Oakley)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Need to have e copy of adafruits nepixel Library in the according arduino folder
#include <Adafruit_NeoPixel.h>

#define PIN 3
#define UP 9
#define Left 10
#define Right 11
#define DOWN 12

#define matrixx 20
#define matrixy 10

//
// PLATFORM SPECIFIC
//

Adafruit_NeoPixel strip = Adafruit_NeoPixel(200, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
}
void setCartesianPixelColor(int x, int y, int r, int b, int g) {
  // The IF statement takes all even rows and reverses them. This accounts for all odd rows linking from left to right and all even rows connecting from right to left.
  if (x % 2) {
    strip.setPixelColor((x*matrixy)+y, r, g, b);
  }
  else {
    strip.setPixelColor((x*matrixy)+(matrixy-y-1), r, g, b);
  }
}

void setLinearPixelColor(int i, int r, int g, int b) {
  strip.setPixelColor(i, r, g, b);
}

void updateDisplay() {
  strip.show();
}

int readRight() {
  return digitalRead(Right);
}

int readLeft() {
  return digitalRead(Left);
}

int readUp() {
  return digitalRead(UP);
}

int readDown() {
  return digitalRead(DOWN);
}

void clearBoard() {
  for(int i = 0; i < strip.numPixels(); i++){
    setLinearPixelColor(i, 0, 0, 0);
  }
}

//
// END PLATFORM SPECIFIC
//

