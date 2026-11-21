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
void Car::update(const std::vector<Wall> &walls) {
  if (is_alive) {
    Point old_position = position;

    position.x += speed * std::cos(angle);
    position.y += speed * std::sin(angle);

    for (size_t i = 0; i < walls.size(); ++i) {
      RayHit hit =
          getIntersection(old_position, position, walls[i].start, walls[i].end);
      if (hit.has_hit) {
        is_alive = false;
        position = hit.hit_point;
        break;
      }
    }

    if (is_alive) {
      ++score;
    }
  }
}
// функция определяет то, куда смотрит луч.
std::vector<Point> Car::getSensorEndPoints() {
  std::vector<Point> endpoints;

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
      ((A.x - C.x) * (C.y - D.y) - (A.y - C.y) * (C.x - D.x)) / determinant;
  double u =
      ((A.x - C.x) * (A.y - B.y) - (A.y - C.y) * (A.x - B.x)) / determinant;

  if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
    result.has_hit = true;

    result.hit_point.x = A.x + t * (B.x - A.x);
    result.hit_point.y = A.y + t * (B.y - A.y);

    double first_cath = result.hit_point.x - A.x;
    double second_cath = result.hit_point.y - A.y;
    result.distance =
        std::sqrt(first_cath * first_cath + second_cath * second_cath);
  }

  return result;
}
// функция поворачивает машинку, получая информацию от ИИ
void Car::applySteering(double steer_value) {
  if (is_alive) {
    angle += steer_value * turn_speed;
  }
}
// функция находит минимальное расстояние до стены
std::vector<double> Car::getSensorReadings(const std::vector<Wall> &walls) {
  std::vector<Point> endpoints = getSensorEndPoints();
  std::vector<double> readings;
  for (size_t i = 0; i < endpoints.size(); ++i) {
    double min_distance = sensor_length;

    for (size_t j = 0; j < walls.size(); ++j) {
      RayHit hit =
          getIntersection(position, endpoints[i], walls[j].start, walls[j].end);
      if (hit.has_hit && (hit.distance < min_distance))
        min_distance = hit.distance;
    }
    if (min_distance < radius) {
      is_alive = false;
    }
    readings.push_back(min_distance);
  }
  return readings;
}
