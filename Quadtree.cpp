#include <cassert>
#include "Quadtree.hpp"

Quadtree::Quadtree(XY _center, XY _halfDimension)
  : boundary(_center, _halfDimension), nodeCapacity(4)
{
  NW = NE = SW = SE = NULL;
  points.reserve(nodeCapacity);
}

bool Quadtree::insert(Item * a) {
  /* std::cout << "insert" << std::endl; */
  if (!boundary.containsPoint(a))
    return false;

  if (points.size() < nodeCapacity) {
    points.push_back(a);
    return true;
  }
  /* assert(false); */

  if (NW == NULL) subdivide();

  //assert(false);
  if (NW->insert(a)) return true;
  if (NE->insert(a)) return true;
  if (SW->insert(a)) return true;
  if (SE->insert(a)) return true;

  assert(false);
  return false; // should never happen
}

void Quadtree::subdivide() {
  /* std::cout << "subdivide" << std::endl; */
  XY center = boundary.center;
  XY newDim(boundary.halfDimension.x / 2, boundary.halfDimension.y / 2);

  NW = new Quadtree(XY(center.x - newDim.x, center.y - newDim.y), newDim);
  NE = new Quadtree(XY(center.x + newDim.x, center.y - newDim.y), newDim);
  SW = new Quadtree(XY(center.x - newDim.x, center.y + newDim.y), newDim);
  SE = new Quadtree(XY(center.x + newDim.x, center.y + newDim.y), newDim);
}

void Quadtree::queryRange(std::vector<Item*> & list, AABB range) {
  /* std::cout << boundary.center.x << " " << boundary.center.y << " | " << boundary.halfDimension.x << " " << boundary.halfDimension.y << std::endl; */
  //std::cout << range.center.x << " " << range.center.y << " | " << range.halfDimension.x << " " << range.halfDimension.y << std::endl;
  if (!boundary.intersectsAABB(range)) return ; // list is empty
  /* assert(false && "cool"); */

  for (int i = 0; i < points.size(); ++i)
    if (range.containsPoint(points[i]))
      list.push_back(points[i]);

  if (NW == NULL) return ;

  NW->queryRange(list, range);
  NE->queryRange(list, range);
  SW->queryRange(list, range);
  SE->queryRange(list, range);
}

void Quadtree::runThrough() {
  if (this == NULL) return;
  NW->runThrough();
  NE->runThrough();
  SW->runThrough();
  SE->runThrough();
  /* for (int i = 0; i < points.size(); ++i) { */
  /* } */
}

/* // scan the tree and remove all node/Item* */
void Quadtree::clear() {
  if (this == NULL) return;
  points.clear();

  NW->clear();
  delete NW;
  NW = NULL;
  NE->clear();
  delete NE;
  NE = NULL;
  SW->clear();
  delete SW;
  SW = NULL;
  SE->clear();
  delete SE;
  SE = NULL;
}

/* bool Quadtree::getCollision(std::vector<Item*> l) { */
/* } */
