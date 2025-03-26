/**
 * @file AntBasePheromone.cpp
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "agents-ant/AntBasePheromone.hpp"
#include "agents-ant/AntBase.hpp"
#include "agents-env/Anthill.hpp"
#include "agents-env/Environment.hpp"
#include "agents-env/Pheromone.hpp"

AntBasePheromone::AntBasePheromone(Environment *environment, Anthill *anthill)
    : AntBase(environment, anthill) {}

void AntBasePheromone::putPheromone(float q) {
  std::vector<Pheromone *> curr_pheromone = LocalizedEntity::perceive<Pheromone>();
  if (curr_pheromone.empty())
    new Pheromone(getEnvironment(), getPosition(), q);
  else
    curr_pheromone.front()->addQuantity(q);
}

Pheromone *AntBasePheromone::choosePheromone() const {
  const auto perceivedPheromones = LocalizedEntity::perceive<Pheromone>(
      getDirection(), OPENING_ANGLE, MAX_DISTANCE_VIEW_PHEROMONE, MIN_DISTANCE_VIEW_PHEROMONE);

  if (perceivedPheromones.empty())
    return nullptr;

  std::vector<float> weights;
  weights.reserve(perceivedPheromones.size());
  for (const auto &pheromone : perceivedPheromones) {
    weights.push_back(pheromone->getQuantity());
  }

  const size_t chosenIndex = MathUtils::randomChoose(weights);
  return perceivedPheromones[chosenIndex];
}

void AntBasePheromone::update() {
  AntBase::update();
  if (hasFood())
    putPheromone(PHEROMONE_AMOUNT_TO_DROP_WHEN_CARRYING_FOOD);
  else
    putPheromone(PHEROMONE_AMOUNT_TO_DROP);
}