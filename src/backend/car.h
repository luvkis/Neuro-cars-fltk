#pragma once
#include <vector>

struct Point {
  double x;
  double y;
};

struct Wall {
  Point start;
  Point end;
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
  bool is_alive = true;
  double score = 0.0;
  double turn_speed = 0.05;
  double sensor_length = 100.0;
  double radius = 5;

  Car(double start_x, double start_y, double start_angle, double start_speed);

  void update(const std::vector<Wall> &walls);

  std::vector<Point> getSensorEndPoints();

  RayHit getIntersection(Point A, Point B, Point C, Point D);

  void applySteering(double steer_value);

  std::vector<double> getSensorReadings(const std::vector<Wall> &walls);
};