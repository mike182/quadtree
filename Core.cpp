#include <iostream>
#include <cstdlib>
#include <cassert>

#include "Core.hpp"


void printQTree(sf::RenderWindow*, Quadtree*);
AABB rangeFromItem(Item*);

Core::Core(int n)
  : qtree(new Quadtree(XY(800/2, 600/2), XY(800/2, 600/2)))
{
  window.create(sf::VideoMode(800, 600, 32), "My window", sf::Style::Default, sf::ContextSettings());
  for (int i = 0; i < n; ++i) {
    _items.push_back(new Item(Random(800), Random(600), Random(30) + 5));
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
  typedef std::vector<Item*> clist;

  clist coll;
  coll.reserve(10);
  for (int i = 0; i < _items.size(); ++i) {
    coll.clear();
    qtree->queryRange(coll, rangeFromItem(_items[i]));
    for (int i = 0; i < coll.size(); ++i)
      for (int j = i + 1; j < coll.size(); ++j) {
        if (coll[i]->checkForCollision(coll[j])) {
          coll[i]->drawable.setFillColor(sf::Color(0, 171, 111, 100));
          coll[j]->drawable.setFillColor(sf::Color(0, 171, 111, 100));
        }
      }
    /* if (coll.size() == 2) */
    /*   if (checkForCollision(coll[0], coll[1])) */
    /*     /1* coll[0]->drawable.setFillColor(sf::Color(0, 171, 111, 100)); *1/ */
    /*     /1* coll[1]->drawable.setFillColor(sf::Color(0, 171, 111, 100)); *1/ */
    /*     _items[i]->drawable.setFillColor(sf::Color(0, 171, 111, 100)); */
  }

  // draw
  for (int i = 0 ; i < _items.size(); ++i)
    window.draw(_items[i]->drawable);
  printQTree(&window, qtree);
}

AABB rangeFromItem(Item* a) {
  return AABB(XY(a->x, a->y), XY(a->radius * 2, a->radius * 2));
}

void printQTree(sf::RenderWindow* w, Quadtree* t) {
  if (!t) return;
  sf::RectangleShape drawable;

  //drawable.setOrigin(t->boundary.halfDimension.x, t->boundary.halfDimension.y);
  drawable.setPosition(t->boundary.center.x - t->boundary.halfDimension.x,
                       t->boundary.center.y - t->boundary.halfDimension.y);
  drawable.setSize(sf::Vector2f(t->boundary.halfDimension.x * 2, t->boundary.halfDimension.y * 2));
  drawable.setFillColor(sf::Color(10 * (long long unsigned int)t, 171 * (unsigned long long int)t, 111, 0));
  drawable.setOutlineColor(sf::Color(100, 171, 111, 100));
  drawable.setOutlineThickness(1);
  w->draw(drawable);
  printQTree(w, t->NE);
  printQTree(w, t->NW);
  printQTree(w, t->SE);
  printQTree(w, t->SW);
}
