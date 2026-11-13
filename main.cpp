#include "src/backend/car.h"
#include <iostream>

int main() {
  Car myCar(0.0, 0.0, 0.0, 5.0);

  std::cout << "На старте: X = " << myCar.position.x
            << ", Y = " << myCar.position.y << std::endl;

  myCar.update();
  std::cout << "Шаг 1: X = " << myCar.position.x << ", Y = " << myCar.position.y
            << std::endl;

  myCar.angle = 1.5708;

  myCar.update();
  std::cout << "Шаг 2 (поворот): X = " << myCar.position.x
            << ", Y = " << myCar.position.y << std::endl;

  std::vector<Point> rays = myCar.getSensorEndPoints();

  std::cout << "\nКоординаты концов 5 лучей:" << std::endl;
  for (size_t i = 0; i < rays.size(); ++i) {
    std::cout << "Луч " << i + 1 << ": X = " << rays[i].x
              << ", Y = " << rays[i].y << std::endl;
  }
  Point wall_start = {20.0, -50.0};
  Point wall_end = {20.0, 50.0};

  Point ray_start = myCar.position;
  Point ray_end = rays[2];

  RayHit hit = myCar.getIntersection(ray_start, ray_end, wall_start, wall_end);

  std::cout << "\n--- Тест радара ---" << std::endl;
  if (hit.has_hit) {
    std::cout << "Удар! Стена найдена на расстоянии: " << hit.distance
              << std::endl;
    std::cout << "Координаты удара: X = " << hit.hit_point.x
              << ", Y = " << hit.hit_point.y << std::endl;
  } else {
    std::cout << "Путь чист, стена не задета." << std::endl;
  }
  return 0;
}