/**
 * @file Anthill.h
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef ANTHILL_H
#define ANTHILL_H

#include "agents-ant/Agent.hpp"
class Anthill : public Agent {
private:
  float m_quantity = 0;

public:
  Anthill(Environment *environment, const Vector2<float> &pos);
  void depositFood(float quantity);
  void update() override;
};

#endif