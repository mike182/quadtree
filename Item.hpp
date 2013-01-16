#ifndef __ITEM__
#define __ITEM__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Item {

 public:

  Item() {}
  Item(float, float, float);
  void Move();
  void SetColor(sf::Color);
  void SetPosition(float, float);
  float genRandomFloat(float, float);

  float x, y, radius;
  bool col;
  sf::CircleShape drawable;

  struct dir {

    void reset() { up = 0; down = 0; left = 0; right = 0; }
    void toMove(Item * item) {
      if (up) {
        int x = item->x;
        int y = item->y;
        --y;
        item->SetPosition(x, y);
      }
      if (down) {
        int x = item->x;
        int y = item->y;
        ++y;
        item->SetPosition(x, y);
      }
      if (left) {
        int x = item->x;
        int y = item->y;
        x--;
        item->SetPosition(x, y);
      }
      if (right) {
        int x = item->x;
        int y = item->y;
        x++;
        item->SetPosition(x, y);
      }
    }
    int up;
    int down;
    int left;
    int right;

  } d;


  //// 
  float getX() { return x; }
  float getY() { return y; }
  float getHeight() { return radius; }
  float getWidth() { return radius; }
};

#endif // __ITEM__
