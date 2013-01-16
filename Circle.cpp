#include <SFML/Graphics.hpp>
#include "Circle.hpp"

Circle::Circle(float _x, float _y, float _radius)
: x(_x), y(_y), radius(_radius), col(false) {

  // RANDOM DIRECTION  INITIALISATION FOR BOUNCEING ENMMIES
  int dice;
  d.up = d.down = d.left = d.right = speed = 0;

  // y dir
  dice = rand() % 100 + 1;
  (dice < 50 ? d.up = 1 : d.down = 1);
  // x dir
  dice = rand() % 100 + 1;
  (dice < 50 ? d.left = 1 : d.right = 1);
  // speed
  speed = genRandomFloat(1.0, 10.0);
#define COUT(x) std::cout << x << std::endl;
  COUT(speed);

  drawable.setOrigin(radius, radius);
  drawable.setPosition(x, y);
  drawable.setRadius(radius);
  drawable.setFillColor(sf::Color(0, 171, 111, 0));
  drawable.setOutlineColor(sf::Color(0, 171, 111, 255));
  drawable.setOutlineThickness(2);
}

void Circle::Move() {
  // BOUNCING BALLS
  if (x - radius <= 0) { d.right = 1, d.left = 0; d.toMove(this); }
  if (x + radius>= 800) { d.left = 1, d.right = 0; d.toMove(this); }
  if (y - radius<= 0) { d.up = 0, d.down = 1; d.toMove(this); }
  if (y + radius>= 600) { d.down = 0, d.up = 1; d.toMove(this); }
  // MOVEMENT DIRECTION
  d.toMove(this);
}

float Circle::genRandomFloat(float min, float max) {
  return (rand() % (static_cast<int>(max) * 100) + min) / 100.0;
}

void SetColor(sf::Color) {
}
