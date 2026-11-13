#pragma once
#include <vector>

struct Point {
  double x;
  double y;
};

struct RayHit {
  bool has_hit;
  double distance;
  Point hit_point;
};

class Car {
public:
  Point position;
  double angle;
  double speed;

  Car(double start_x, double start_y, double start_angle, double start_speed);

  void update();

  std::vector<Point> getSensorEndPoints();

  RayHit getIntersection(Point A, Point B, Point C, Point D);
};