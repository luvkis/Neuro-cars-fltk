#include "ai_brain.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

int main() {
  srand(time(0));

  int POPULATION_SIZE = 100;
  int MAX_GENERATION_SIZE = 50;
  std::vector<Brain> population;

  for (int i = 0; i < POPULATION_SIZE; i++) {
    Brain intermediate;
    intermediate.weight_left = randomFloat(1.0f);
    intermediate.weight_center = randomFloat(1.0f);
    intermediate.weight_right = randomFloat(1.0f);

    population.push_back(intermediate);
  }
  for (int current_generation = 0; current_generation < MAX_GENERATION_SIZE;
       current_generation++) {
    // заезд машин
    for (int i = 0; i < POPULATION_SIZE; i++) {
      population[i].fitness = 0.0f;
      float turn_1 = population[i].think(0.1f, 0.7f, 1.0f);
      float turn_2 = population[i].think(0.1f, 0.1f, 1.0f);
      float turn_3 = population[i].think(1.0f, 0.5f, 0.2f);

      if (turn_1 > 0) {
        population[i].fitness += 10.0f;
        if (turn_1 > 0.2f && turn_1 < 0.5f)
          population[i].fitness += 10.0f;
      }
      if (turn_2 > 0) {
        population[i].fitness += 5.0f;
        if (turn_2 > 0.7f)
          population[i].fitness += 10.0f;
      }
      if (turn_3 < 0) {
        population[i].fitness += 10.0f;
        if (turn_3 < -0.2f && turn_3 >= -0.6f)
          population[i].fitness += 10.0f;
      }
    }
    // сортировка по расстоянию
    std::sort(
        population.begin(), population.end(),
        [](const Brain &a, const Brain &b) { return a.fitness > b.fitness; });

    std::cout << "Best score is " << population[0].fitness << " metres. \n";
    // new population
    std::vector<Brain> new_population;
    new_population.push_back(population[0]);
    new_population.push_back(population[1]);
    new_population.push_back(population[2]);
    for (int i = 3; i < POPULATION_SIZE; i++) {
      Brain owner_1 = population[rand() % 5];
      Brain owner_2 = population[rand() % 5];

      Brain new_car = owner_1.crossover(owner_2);
      new_car.mutate(0.1f);
      new_car.fitness = 0.0f;

      new_population.push_back(new_car);
    }

    population = new_population;
  }

  return 0;
}