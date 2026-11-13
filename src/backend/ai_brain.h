#pragma once

struct Brain {
  float weight_left;
  float weight_diag_left;
  float weight_center;
  float weight_diag_right;
  float weight_right;

  float fitness = 0.0f;

  float think(float sensor_left, float sensor_diag_left, float sensor_center,
              float sensor_diag_right, float sensor_right);
  void mutate(float mutation_rate);
  Brain crossover(Brain partner);
};

float randomFloat(float range);