/**
 * @file AbstractAntRule.cpp
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "rules/AbstractAntRule.hpp"
#include "agents-ant/AntBasePheromone.hpp"

AbstractAntRule::AbstractAntRule(AntBasePheromone *target) : target(target) {}

AntBasePheromone *AbstractAntRule::getTarget() const {
  return target;
}