#include <iostream>
#include <cstdlib>
#include <cassert>

#include "Core.hpp"

Core::Core(int n)
  : qtree(new Quadtree(XY(800/2, 600/2), XY(800/2, 600/2)))
{
  window.create(sf::VideoMode(800, 600, 32), "My window", sf::Style::Default, sf::ContextSettings());
  for (int i = 0; i < n; ++i) {
    _items.push_back(new Item(rand() % 800 + 1, rand() % 600 + 1, rand() % 2 + 1));
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

void printQTree(sf::RenderWindow* w, Quadtree* t) {
  if (!t) return;
  sf::RectangleShape drawable;

  //drawable.setOrigin(t->boundary.halfDimension.x, t->boundary.halfDimension.y);
  drawable.setPosition(t->boundary.center.x - t->boundary.halfDimension.x,
                       t->boundary.center.y - t->boundary.halfDimension.y);
  drawable.setSize(sf::Vector2f(t->boundary.halfDimension.x * 2, t->boundary.halfDimension.y *2));
  drawable.setFillColor(sf::Color(10 * (long long unsigned int)t, 171 * (unsigned long long int)t, 111, 0));
  drawable.setOutlineColor(sf::Color(100, 171, 111, 100));
  drawable.setOutlineThickness(2);
  w->draw(drawable);
  printQTree(w, t->NE);
  printQTree(w, t->NW);
  printQTree(w, t->SE);
  printQTree(w, t->SW);
}

void Core::Update() {
  // clear
  window.clear(sf::Color(70, 70, 70));
  qtree->clear();

  // set alpha = 0 & make items moving
  for (int i = 0; i < _items.size(); ++i) {
    _items[i]->drawable.setFillColor(sf::Color(0, 0, 0, 0));
    _items[i]->Move();
    qtree->insert(_items[i]);
  }

  // get collision list
  std::vector<Item*> lCol;
  for (int i = 0; i < _items.size(); ++i) {
    XY center(_items[i]->x, _items[i]->y);
    XY half(_items[i]->radius, _items[i]->radius);
    /* XY half(50, 50); */
    qtree->queryRange(lCol, AABB(center, half));
    assert(lCol.size() > 0);
  }
  for (std::vector<Item*>::iterator it = lCol.begin(); it != lCol.end(); ++it) {
    /* std::cout << (*it)->x << " " << (*it)->y << std::endl; */
  }
  /* std::cout << "LAP" << std::endl; */

  /* qtree->getCollision(& lCol); */

  // color only collided items
  for (std::vector<Item *>::iterator it = lCol.begin(); it != lCol.end(); ++it) {
    /* std::cout << (*it)->getX() << " " << (*it)->getY() << std::endl; */
    (*it)->drawable.setFillColor(sf::Color(0, 171, 111, 100));
  }

  // draw
  for (int i = 0 ; i < _items.size(); ++i)
    window.draw(_items[i]->drawable);

  printQTree(&window, qtree);
}

bool Core::checkForCollision(Item * a, Item * b) {
  float AB = sqrt(pow(b->x - a->x, 2) + pow(b->y - a->y, 2));
  return AB - (a->radius + b->radius) < 0;
}
