#include <iostream>
#include <cstdlib>

#include "Core.hpp"

Core::Core(int n)
  : qtree(new Quadtree(XY(800/2, 600/2), XY(800/2, 600/2)))
{
  window.create(sf::VideoMode(800, 600, 32), "My window", sf::Style::Default, sf::ContextSettings());
  for (int i = 0; i < n; ++i) {
    _items.push_back(new Item(rand() % 800 + 1, rand() % 600 + 1, rand() % 20 + 10));
  }
}

void Core::Start() {
  window.setFramerateLimit(60);
  while (window.isOpen())
  {
    sf::Event event;
    while (true) {
      if (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close(), exit(1);
        if ((event.type == sf::Event::KeyPressed) && 
            (event.key.code == sf::Keyboard::Escape)) window.close(), exit(1);
      }
      Update();
      window.display();
    }
  }
}

int Core::GetRandomColor(int max) {
  return rand() % max + 1;
}

void Core::Update() {
  // clear
  window.clear(sf::Color(70, 70, 70));
  /* qtree->clear(); */

  // set alpha = 0 & make items moving
  for (int i = 0; i < _items.size(); ++i) {
    _items[i]->drawable.setFillColor(sf::Color(0, 0, 0, 0));
    _items[i]->Move();
    qtree->insert(_items[i]);
  }

  // get collision list
  std::vector<Item*> lCol;

  
  /* qtree->getCollision(& lCol); */

  // color only collided items
  for (std::vector<Item *>::iterator it = lCol.begin(); it != lCol.end(); ++it) {
    std::cout << (*it)->getX() << " " << (*it)->getY() << std::endl;
    (*it)->drawable.setFillColor(sf::Color(0, 171, 111, 100));
  }

  // draw
  for (int i = 0 ; i < _items.size(); ++i)
    window.draw(_items[i]->drawable);
}

bool Core::checkForCollision(Item * a, Item * b) {
  float AB = sqrt(pow(b->x - a->x, 2) + pow(b->y - a->y, 2));
  return AB - (a->radius + b->radius) < 0;
}
