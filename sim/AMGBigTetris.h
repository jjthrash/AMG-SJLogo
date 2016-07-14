#ifndef __AMGBIGTETRIS_H__
#define __AMGBIGTETRIS_H__

void setupStrip();
void setupController();

void setCartesianPixelColor(int x, int y, int r, int b, int g);
void setLinearPixelColor(int i, int r, int g, int b);
void updateDisplay();
int readRight();
int readLeft();
int readUp();
int readDown();
void clearBoard();

#endif
