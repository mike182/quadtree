#ifndef __CORE__
#define __CORE__

#include <vector>
#include <SFML/Graphics.hpp>

#include "Quadtree.hpp"
#include "Item.hpp"

class Core {
 public:
  Core();
  Core(int);

  void Start();
  void Update();
  int GetRandomColor(int);
  bool checkForCollision(Item *a, Item *b);

  std::vector<Item *> _items;
  sf::RenderWindow window;
  Quadtree * qtree;
};

#endif // __CORE__
