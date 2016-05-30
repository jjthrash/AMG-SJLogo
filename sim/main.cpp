#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "board.hpp"

#define FLTK_LOOP_TIME 0.01

void loop();

//
// PLATFORM SPECIFIC
//

Board *board = 0;

void setCartesianPixelColor(int x, int y, int r, int g, int b) {
  board->setCartesianPixelColor(x, y, r, g, b);
}

void setLinearPixelColor(int i, int r, int g, int b) {
  board->setLinearPixelColor(i, r, g, b);
}

void updateDisplay() {
  board->updateDisplay();
}

int readRight() {
  return board->readRight();
}

int readLeft() {
  return board->readLeft();
}

int readUp() {
  return board->readUp();
}

int readDown() {
  return board->readDown();
}

void clearBoard() {
  board->clearBoard();
}

void delay(long ms) {
  usleep(ms * 1000);
}

long random(long max) {
  return rand() % max;
}

//
// END PLATFORM SPECIFIC
//


void handle_timeout(void *context) {
//puts("void handle_timeout(void *context) {");
  loop();
  Fl::repeat_timeout(FLTK_LOOP_TIME, handle_timeout);
}

int main(int argc, char **argv) {
  srand(time(NULL));
  Fl_Window *window = new Fl_Window(440,840);
  board = new Board(20,20,400,800);
  board->updateDisplay();
  window->end();
  window->show(argc, argv);
  Fl::add_timeout(FLTK_LOOP_TIME, handle_timeout);
  return Fl::run();
}

