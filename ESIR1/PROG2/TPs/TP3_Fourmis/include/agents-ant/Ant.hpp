/**
 * @file Ant.h
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef ANT_H
#define ANT_H

#include "agents-ant/AntBasePheromone.hpp"
#include "agents-env/Environment.hpp"
class Ant : public AntBasePheromone {
public:
  Ant(Environment *environment, Anthill *anthill);
  void update() override;
};
#endif