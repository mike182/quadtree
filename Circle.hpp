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
  void SetPosition(float, float);
  float genRandomFloat(float, float);

  float x, y, radius;
  bool col;
  sf::CircleShape drawable;

  struct dir {

    void reset() { up = 0; down = 0; left = 0; right = 0; }
    void toMove(Circle * circle) {
      if (up) {
        int x = circle->x;
        int y = circle->y;
        --y;
        circle->SetPosition(x, y);
      }
      if (down) {
        int x = circle->x;
        int y = circle->y;
        ++y;
        circle->SetPosition(x, y);
      }
      if (left) {
        int x = circle->x;
        int y = circle->y;
        x--;
        circle->SetPosition(x, y);
      }
      if (right) {
        int x = circle->x;
        int y = circle->y;
        x++;
        circle->SetPosition(x, y);
      }
    }
    int up;
    int down;
    int left;
    int right;

  } d;

};

#endif // __CIRCLE__
