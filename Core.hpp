#ifndef __CORE__
#define __CORE__

#include <vector>
#include <SFML/Graphics.hpp>

#include "Quadtree.hpp"
#include "Item.hpp"

class Core {
 public:
  Core(int);

  void Start();
  void Update();

  int Random(int max) {
    return rand() % max + 1;
  }

  sf::RenderWindow window;
  Quadtree * qtree;
  std::vector<Item *> _items;
};

#endif // __CORE__
