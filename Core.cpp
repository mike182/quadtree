#include <iostream>
#include <cstdlib>

#include "Core.hpp"

Core::Core(int n) {
  window.create(sf::VideoMode(800, 600, 32), "My window", sf::Style::Default, sf::ContextSettings());
  for (int i = 0; i < n; ++i) {
    _items.push_back(new Circle(rand() % 800 + 1, rand() % 600 + 1, rand() % 20 + 10));
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
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) window.close(), exit(1);
      }
      Update();
      window.display();
    }
  }
}

void Core::Update() {
  window.clear(sf::Color(128, 128, 128));
  for (int i = 0; i < _items.size(); ++i) 
    _items[i]->drawable.setFillColor(sf::Color(0, 171, 111, 0));
  for (int i = 0 ; i < _items.size(); ++i) {
    _items[i]->Move();
    for (int j = i; j < _items.size(); ++j) {
      if (i != j && checkForCollision(_items[i], _items[j])) {
        /* std::cout << "COL" << std::endl; */
        _items[i]->drawable.setFillColor(sf::Color(0, 171, 111, 100));
        _items[j]->drawable.setFillColor(sf::Color(0, 171, 111, 100));
      }
    }
    window.draw(_items[i]->drawable);
  }
}

bool Core::checkForCollision(Circle * a, Circle * b) {
  float AB = sqrt(pow(b->x - a->x, 2) + pow(b->y - a->y, 2));
  return AB - (a->radius + b->radius) < 0;
}
