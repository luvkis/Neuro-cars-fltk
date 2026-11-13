#include "ai_brain.h"
#include <cmath>
#include <cstdlib>

float randomFloat(float range) {
  return ((rand() % 2000 / 1000.0f) - 1.0f) * range;
}

float Brain::think(float sensor_left, float sensor_diag_left,
                   float sensor_center, float sensor_diag_right,
                   float sensor_right) {
  float sum =
      (sensor_left * weight_left) + (sensor_diag_left * weight_diag_left) +
      (sensor_center * weight_center) +
      (sensor_diag_right * weight_diag_right) + (sensor_right * weight_right);
  return std::tanh(sum);
}

void Brain::mutate(float mutation_rate) {
  weight_left += randomFloat(mutation_rate);
  weight_diag_left += randomFloat(mutation_rate);
  weight_center += randomFloat(mutation_rate);
  weight_diag_right += randomFloat(mutation_rate);
  weight_right += randomFloat(mutation_rate);
}

Brain Brain::crossover(Brain partner) {
  Brain child;
  child.weight_left =
      (rand() % 2 == 0) ? this->weight_left : partner.weight_left;
  child.weight_diag_left =
      (rand() % 2 == 0) ? this->weight_diag_left : partner.weight_diag_left;
  child.weight_center =
      (rand() % 2 == 0) ? this->weight_center : partner.weight_center;
  child.weight_diag_right =
      (rand() % 2 == 0) ? this->weight_diag_right : partner.weight_diag_right;
  child.weight_right =
      (rand() % 2 == 0) ? this->weight_right : partner.weight_right;
  return child;
}