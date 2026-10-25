#pragma once

struct Brain {
  float weight_left;
  float weight_center;
  float weight_right;

  float fitness = 0.0f;

  float think(float sensor_left, float sensor_center, float sensor_right);
  void mutate(float mutation_rate);
  Brain crossover(Brain partner);
};

float randomFloat(float range);