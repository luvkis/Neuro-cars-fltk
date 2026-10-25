#include "ai_brain.h"
#include <cmath>
#include <cstdlib>

float randomFloat(float range) {
  return ((rand() % 2000 / 1000.0f) - 1.0f) * range;
}

float Brain::think(float sensor_left, float sensor_center, float sensor_right) {
  float sum = (sensor_left * weight_left) + (sensor_center * weight_center) +
              (sensor_right * weight_right);
  return std::tanh(sum);
}

void Brain::mutate(float mutation_rate) {
  weight_left += randomFloat(mutation_rate);
  weight_center += randomFloat(mutation_rate);
  weight_right += randomFloat(mutation_rate);
}

Brain Brain::crossover(Brain partner) {
  Brain child;
  child.weight_left =
      (rand() % 2 == 0) ? this->weight_left : partner.weight_left;
  child.weight_center =
      (rand() % 2 == 0) ? this->weight_center : partner.weight_center;
  child.weight_right =
      (rand() % 2 == 0) ? this->weight_right : partner.weight_right;
  return child;
}