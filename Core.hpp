#ifndef __CORE__
#define __CORE__

#include <vector>
#include <SFML/Graphics.hpp>

#include "Circle.hpp"

class Core {
 public:
  Core();
  Core(int);

  void Start();
  void Update();
  bool checkForCollision(Circle *a, Circle *b);

  std::vector<Circle *> _items;
  sf::RenderWindow window;
};

#endif // __CORE__
