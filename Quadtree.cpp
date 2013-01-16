#include "Quadtree.hpp"

Quadtree::Quadtree(XY _center, XY _halfDimension)
  : boundary(_center, _halfDimension), nodeCapacity(4)
{
  NW = NE = SW = SE = NULL;
  points.reserve(nodeCapacity);
}

bool Quadtree::insert(Item * a) {
  if (!boundary.containsPoint(a))
    return false;

  if (points.size() < nodeCapacity) {
    points.push_back(a);
    return true;
  }

  if (NW == NULL) subdivide();

  if (NW->insert(a)) return true;
  if (NE->insert(a)) return true;
  if (SW->insert(a)) return true;
  if (SE->insert(a)) return true;

  return false; // should never happen
}

void Quadtree::subdivide() {
  XY center(boundary.center.x, boundary.center.y);
  XY half(boundary.center.x, boundary.center.y);

  NW = new Quadtree(XY(center.x - half.x, center.y - half.y), XY(half.x / 2, half.y / 2));
  NE = new Quadtree(XY(center.x + half.x, center.y - half.y), XY(half.x / 2, half.y / 2));
  SW = new Quadtree(XY(center.x - half.x, center.y + half.y), XY(half.x / 2, half.y / 2));
  SE = new Quadtree(XY(center.x + half.x, center.y + half.y), XY(half.x / 2, half.y / 2));
}

void Quadtree::queryRange(std::vector<Item*> & list, AABB range) {
  if (!boundary.intersectsAABB(range)) return ; // list is empty

  for (int i = 0; i < points.size(); ++i)
    if (range.containsPoint(points[i]))
      list.push_back(points[i]);

  if (NW == NULL) return ;

  NW->queryRange(list, range);
  NE->queryRange(list, range);
  SW->queryRange(list, range);
  SE->queryRange(list, range);
}

void Quadtree::runThrought() {
  if (NW != NULL) runThrought();
  if (NE != NULL) runThrought();
  if (SW != NULL) runThrought();
  if (SE != NULL) runThrought();
  for (int i = 0; i < points.size(); ++i) {
  /* std::cout << points[i]->x << std::endl; */
  }
  /* std::cout << std::endl; */
}

/* // scan the tree and remove all node/Item* */
void Quadtree::clear() {
  if (NW != NULL) NW->clear();
  NW = NULL;
  if (NE != NULL) NE->clear();
  NE = NULL;
  if (SW != NULL) SW->clear();
  SW = NULL;
  if (SE != NULL) SE->clear();
  SE = NULL;
}

/* bool Quadtree::getCollision(std::vector<Item*> l) { */
/* } */
