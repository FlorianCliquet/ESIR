/**
 * @file AntBasePheromone.h
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef ANTBASEPHEROMONE_H
#define ANTBASEPHEROMONE_H

#include "agents-ant/AntBase.hpp"
#include "agents-env/Anthill.hpp"
#include "agents-env/Environment.hpp"
#include "agents-env/Pheromone.hpp"
class AntBasePheromone : public AntBase {
protected:
  static constexpr float MAX_DISTANCE_VIEW_PHEROMONE = 8.0;
  static constexpr float MIN_DISTANCE_VIEW_PHEROMONE = 3.0;
  static constexpr float PHEROMONE_AMOUNT_TO_DROP = 10.0;
  static constexpr float PHEROMONE_AMOUNT_TO_DROP_WHEN_CARRYING_FOOD = 100.0;

public:
  AntBasePheromone(Environment *environment, Anthill *anthill);
  void putPheromone(float q);
  Pheromone *choosePheromone() const;
  void update() override;
};

#endif