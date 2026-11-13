#pragma once
#include <fstream>
#include <string>
#include <vector>

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

struct EvolutionManager {
  std::vector<Brain> population;
  int current_generation = 0;
  int alive_cars_count = 0;

  void init(int population_size);
  void breedNextGeneration();
  Brain &getBrain(int index);
  void carCrashed();
  void saveBestBrain(std::string filename);
  void loadBestBrain(std::string filename);
};

float randomFloat(float range);