#include "board.hpp"
#include <FL/Fl_draw.H>

Board::Board(int x, int y, int w, int h) : Fl_Widget(x,y,w,h) {
  clearBoard();
}

void Board::clearBoard() {
  for (int i = 0; i < BOARD_WIDTH_BLOCKS; i++) {
    for (int j = 0; j < BOARD_HEIGHT_BLOCKS; j++) {
      this->matrix[i][j] = fl_rgb_color(0,0,0);
    }
  }
}

void Board::setCartesianPixelColor(int x, int y, int r, int g, int b) {
  this->matrix[x][y] = fl_rgb_color(r, g, b);
}

void Board::setLinearPixelColor(int i, int r, int g, int b) {
  this->matrix[i%BOARD_WIDTH_BLOCKS][i/BOARD_WIDTH_BLOCKS] =
    fl_rgb_color(r, g, b);
}

int Board::blockX(int i, int j) {
  //top left + i * blockwidth
  return this->x() + i * this->blockW();
}

int Board::blockY(int i, int j) {
  return this->y() + (BOARD_HEIGHT_BLOCKS - j - 1) * this->blockH();
}

int Board::blockW() {
  return this->w() / BOARD_WIDTH_BLOCKS;
}

int Board::blockH() {
  return this->h() / BOARD_HEIGHT_BLOCKS;
}

void Board::updateDisplay() {
  for (int i = 0; i < BOARD_WIDTH_BLOCKS; i++) {
    for (int j = 0; j < BOARD_HEIGHT_BLOCKS; j++) {
      fl_color(matrix[i][j]);
      fl_rectf(this->blockX(i,j),
               this->blockY(i,j),
               this->blockW(),
               this->blockH());
    }
  }
}

int Board::readRight() {
  return right_key_down;
}

int Board::readLeft() {
  return left_key_down;
}

int Board::readUp() {
  return up_key_down;
}

int Board::readDown() {
  return down_key_down;
}

void Board::draw() {
  fl_color(123, 56, 23);
  fl_rectf(this->x(), this->y(), this->w(), this->h());
}

int Board::handle(int event) {
  switch (event) {
  case FL_FOCUS:
    return 1;
  case FL_UNFOCUS:
    return 1;
  case FL_KEYDOWN:
    handle_keydown();
    break;
  case FL_KEYUP:
    handle_keyup();
    break;
  }

  return 0;
}

int Board::handle_keydown() {
  switch (Fl::event_key()) {
  case FL_Down:
    down_key_down = true;
    return 1;
  case FL_Up:
    up_key_down = true;
    return 1;
  case FL_Left:
    left_key_down = true;
    return 1;
  case FL_Right:
    right_key_down = true;
    return 1;
  default:
    return 0;
  }
}

int Board::handle_keyup() {
  switch (Fl::event_key()) {
  case FL_Down:
    down_key_down = false;
    return 1;
  case FL_Up:
    up_key_down = false;
    return 1;
  case FL_Left:
    left_key_down = false;
    return 1;
  case FL_Right:
    right_key_down = false;
    return 1;
  default:
    return 0;
  }
}
