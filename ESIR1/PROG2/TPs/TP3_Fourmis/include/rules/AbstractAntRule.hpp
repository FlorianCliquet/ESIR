/**
 * @file AbstractAntRule.hpp
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef ABSTRACTANTRULE_H
#define ABSTRACTANTRULE_H

#include "agents-ant/AntBasePheromone.hpp"
#include "rules/AbstractRule.hpp"
class AbstractAntRule : public AbstractRule {
private:
  AntBasePheromone *target;

public:
  explicit AbstractAntRule(AntBasePheromone *target);
  AntBasePheromone *getTarget() const;
};

#endif