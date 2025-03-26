/**
 * @file SillyAnt.cpp
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "agents-ant/SillyAnt.hpp"
#include "agents-ant/AntBase.hpp"
#include "agents-env/Anthill.hpp"
#include "agents-env/Environment.hpp"
#include "utils/Timer.hpp"
SillyAnt::SillyAnt(Environment *environment, Anthill *anthill) : AntBase(environment, anthill) {}

void SillyAnt::update() {
  AntBase::update();
  float dt = Timer::dt();

  if (!m_foodCarried) {

    std::vector<Food *> foodSources = perceive<Food>(m_dir, OPENING_ANGLE, 10.0f);
    if (!foodSources.empty()) {
      Food *targetFood = foodSources[0];
      float distance = (getPosition() - targetFood->getPosition()).norm();
      if (distance < targetFood->getRadius())
        collectFood(targetFood);
      else
        orientTowards(targetFood->getPosition());
    } else {
      float randomAngle = MathUtils::random(-M_PI / 10, M_PI / 10) * dt;
      rotate(randomAngle);
    }
  } else {
    orientTowards(m_anthill->getPosition());
    if ((getPosition() - m_anthill->getPosition()).norm() < m_anthill->getRadius())
      dropFood();
  }

  move();
}