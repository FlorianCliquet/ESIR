/**
 * @file Ant.cpp
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "agents-ant/Ant.hpp"
#include "agents-ant/AntBasePheromone.hpp"
#include "agents-env/Anthill.hpp"
#include "agents-env/Environment.hpp"
#include "utils/Timer.hpp"
Ant::Ant(Environment *environment, Anthill *anthill) : AntBasePheromone(environment, anthill) {}
void Ant::update() {
  AntBasePheromone::update();

  if (hasFood()) {
    auto anthills = LocalizedEntity::perceive<Anthill>();
    if (!anthills.empty() && anthills.front() == getAnthill()) {
      dropFood();
      turnAround();
    } else {
      orientTowards(getAnthill()->getPosition());
      if (auto *p = choosePheromone())
        orientTowards(p->getPosition());
      move();
    }
    return;
  }

  auto foodOnSpot = LocalizedEntity::perceive<Food>();
  if (!foodOnSpot.empty()) {
    collectFood(foodOnSpot.front());
    return;
  }

  auto foodInView = LocalizedEntity::perceive<Food>(getDirection(), OPENING_ANGLE,
                                                    MAX_DISTANCE_VIEW_FOOD, MIN_DISTANCE_VIEW_FOOD);
  if (!foodInView.empty())
    orientTowards(foodInView.front()->getPosition());
  else if (auto *p = choosePheromone())
    orientTowards(p->getPosition());
  else
    rotate(
        MathUtils::random((-MathUtils::pi / 10) * Timer::dt(), (MathUtils::pi / 10) * Timer::dt()));
  move();
}
