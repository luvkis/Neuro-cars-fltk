#include "ai_brain.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>

float randomFloat(float range) {
  // get random number
  return ((rand() % 2000 / 1000.0f) - 1.0f) * range;
}

float Brain::think(float sensor_left, float sensor_diag_left,
                   float sensor_center, float sensor_diag_right,
                   float sensor_right) {
  // rotation car
  float sum =
      (sensor_left * weight_left) + (sensor_diag_left * weight_diag_left) +
      (sensor_center * weight_center) +
      (sensor_diag_right * weight_diag_right) + (sensor_right * weight_right);
  return std::tanh(sum);
}
// mutation brain
void Brain::mutate(float mutation_rate) {
  weight_left += randomFloat(mutation_rate);
  weight_diag_left += randomFloat(mutation_rate);
  weight_center += randomFloat(mutation_rate);
  weight_diag_right += randomFloat(mutation_rate);
  weight_right += randomFloat(mutation_rate);
}

// change brains cars
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

// generate population
void EvolutionManager::init(int population_size) {
  population.clear();

  for (int i = 0; i < population_size; ++i) {
    Brain intermediate;
    intermediate.weight_left = randomFloat(1.0f);
    intermediate.weight_diag_left = randomFloat(1.0f);
    intermediate.weight_center = randomFloat(1.0f);
    intermediate.weight_diag_right = randomFloat(1.0f);
    intermediate.weight_right = randomFloat(1.0f);

    population.push_back(intermediate);
  };

  alive_cars_count = population_size;
};

// generate new population
void EvolutionManager::breedNextGeneration() {
  std::sort(
      population.begin(), population.end(),
      [](const Brain &a, const Brain &b) { return a.fitness > b.fitness; });

  // new population
  std::vector<Brain> new_population;
  for (int i = 0; i < 5; ++i) {
    new_population.push_back(population[i]);
  }
  for (int i = 5; i < population.size(); i++) {
    Brain owner_1 = population[rand() % 5];
    Brain owner_2 = population[rand() % 5];

    Brain new_car = owner_1.crossover(owner_2);
    new_car.mutate(0.1f);
    new_car.fitness = 0.0f;

    new_population.push_back(new_car);
  };
  population = new_population;
  alive_cars_count = population.size();
  ++current_generation;
};

// get brain this car
Brain &EvolutionManager::getBrain(int index) { return population[index]; };

// crash car and check amount
void EvolutionManager::carCrashed() {
  --alive_cars_count;
  if (alive_cars_count == 0) {
    breedNextGeneration();
  };
};

// save best car parametrs
void EvolutionManager::saveBestBrain(std::string filename) {
  std::ofstream file(filename);

  if (file.is_open()) {
    Brain best = population[0];

    file << best.weight_left << " " << best.weight_diag_left << " "
         << best.weight_center << " " << best.weight_diag_right << " "
         << best.weight_right << "\n";

    file.close();
  };
};

// load best car parametrs
void EvolutionManager::loadBestBrain(std::string filename) {
  std::ifstream file(filename);
  if (file.is_open()) {

    file >> population[0].weight_left >> population[0].weight_diag_left >>
        population[0].weight_center >> population[0].weight_diag_right >>
        population[0].weight_right;
    file.close();
  }
}
