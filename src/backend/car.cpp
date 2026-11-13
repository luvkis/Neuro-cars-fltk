#include "car.h"
#include <array>
#include <cmath>
#include <vector>

Car::Car(double start_x, double start_y, double start_angle,
         double start_speed) {
  position.x = start_x;
  position.y = start_y;
  angle = start_angle;
  speed = start_speed;
}
// функция определяет положение машинки.
void Car::update() {
  position.x += speed * std::cos(angle);
  position.y += speed * std::sin(angle);
}
// функция определяет то, куда смотрит луч.
std::vector<Point> Car::getSensorEndPoints() {
  std::vector<Point> endpoints;
  double sensor_length = 100.0;

  std::array<double, 5> ray_angles = {-1.5708, -0.7854, 0.0, 0.7854, 1.5708};

  for (size_t i = 0; i < ray_angles.size(); ++i) {
    double total_angle = angle + ray_angles[i];

    Point end;
    end.x = position.x + sensor_length * std::cos(total_angle);
    end.y = position.y + sensor_length * std::sin(total_angle);

    endpoints.push_back(end);
  }

  return endpoints;
}
// функция определяет утыкаются ли лучи в стенку или нет.
// смысл в том, что есть параметр t(число от 0 до 1), который показывает то, на
// каком расстоянии наш луч попал в стену(отношение) если t > 1, то не достает
// до стены параметр u то же самое, но уже для самой стены.
RayHit Car::getIntersection(Point A, Point B, Point C, Point D) {
  RayHit result;
  result.has_hit = false; // по умолчанию мы никуда не врезались
  double determinant =
      (A.x - B.x) * (C.y - D.y) -
      (A.y - B.y) * (C.x - D.x); // определитель матрицы векторов AB, CD

  if (determinant == 0.0) {
    return result;
  }

  double t =
      ((A.x - C.x) * (C.y - D.y) - (A.y - C.y) * (C.x - D.y)) / determinant;
  double u =
      ((A.x - C.x) * (A.y - B.y) - (A.y - C.y) * (A.x - B.x)) / determinant;

  if (t > 0 && t < 1 && u > 0 && u < 1) {
    result.has_hit = true;

    result.hit_point.x = A.x + t * (B.x - A.x);
    result.hit_point.x = A.y + t * (B.y - A.y);

    double first_cath = result.hit_point.x - A.x;
    double second_cath = result.hit_point.y - A.y;
    result.distance =
        std::sqrt(first_cath * first_cath + second_cath * second_cath);
  }

  return result;
}