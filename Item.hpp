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
  bool checkForCollision(Item * other) {
    float AB = sqrt(pow(other->x - x, 2) + pow(other->y - y, 2));
    return AB <= radius + other->radius;
  }
  bool checkForCollision(Item * a, Item * b) {
    float AB = sqrt(pow(b->x - a->x, 2) + pow(b->y - a->y, 2));
    return AB <= a->radius + b->radius;
  }
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
