/**
 * @file Pheromone.h
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef PHEROMONE_H
#define PHEROMONE_H

#include "agents-ant/Agent.hpp"
#include "agents-env/Environment.hpp"
#include "utils/Vector2.hpp"
class Pheromone : public Agent {
protected:
  constexpr static float EVAPORATION_RATE = 0.01;
  float m_quantity;

public:
  Pheromone(Environment *environment, const Vector2<float> &pos, float quantity);
  float getQuantity() const;
  void addQuantity(float q);
  void update() override;
  void evaporate();
};

#endif