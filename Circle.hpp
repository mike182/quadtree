#ifndef __CIRCLE__
#define __CIRCLE__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Circle {

 public:

  Circle() {}
  Circle(float, float, float);
  void Move();
  void SetColor(sf::Color);
  float genRandomFloat(float, float);

  float x, y, radius, speed;
  bool col;
  sf::CircleShape drawable;

  struct dir {

    void reset() { up = 0; down = 0; left = 0; right = 0; }
    void toMove(Circle * c) {
      if (up)    --c->y * c->speed, c->drawable.setPosition(c->x, c->y);
      if (down)  ++c->y * c->speed, c->drawable.setPosition(c->x, c->y);
      if (left)  --c->x * c->speed, c->drawable.setPosition(c->x, c->y);
      if (right) ++c->x * c->speed, c->drawable.setPosition(c->x, c->y);
    }
    int up;
    int down;
    int left;
    int right;

  } d;

};

#endif // __CIRCLE__
