#ifndef __QUADTREE__
#define __QUADTREE__

#include "Item.hpp"

struct XY {
  XY(float _x, float _y) : x(_x), y(_y) {}

  float x, y;
};

struct AABB {
  AABB(XY _center, XY _halfDimension) : center(_center), halfDimension(_halfDimension) {}

  bool containsPoint(Item* item) {
    XY p(item->x, item->y);
    return ((p.x > center.x - halfDimension.x || p.x < center.x + halfDimension.x) &&
            (p.y > center.y - halfDimension.y || p.y < center.y + halfDimension.y));
  }

  bool intersectsAABB(AABB other) {
    return !(center.x - halfDimension.x > other.center.x + other.halfDimension.x ||
             center.x + halfDimension.x < other.center.x - other.halfDimension.x ||
             center.y - halfDimension.y < other.center.y + other.halfDimension.y ||
             center.y + halfDimension.y > other.center.y - other.halfDimension.y);
  }

  XY center;
  XY halfDimension;
};

class Quadtree {
 public:
  Quadtree(XY, XY);

  bool insert(Item *);
  void subdivide();
  void queryRange(std::vector<Item*> &, AABB);

  void runThrought();
  void clear();
  bool getCollision(std::vector<Item*>);

  AABB boundary;
  int nodeCapacity;

  // leaves
  Quadtree * parent;
  Quadtree * NW;
  Quadtree * NE;
  Quadtree * SW;
  Quadtree * SE;

  // data
  std::vector<Item*> points;
};

#endif // __QUADTREE__
