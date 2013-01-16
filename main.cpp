#include <SFML/Window.hpp>
#include <iostream>
#include "Core.hpp"

/* sf::Window window(sf::VideoMode(800, 600), "My window"); */
#include <vector>

int main()
{
  srand(time(NULL));

  Core core(1000);
  core.Start();

  return 0;
}
