/**
 * @file Food.h
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef FOOD_H
#define FOOD_H

#include "agents-ant/Agent.hpp"
#include "utils/MathUtils.hpp"
class Food : public Agent {
private:
  float m_quantity;

public:
  Food(Environment *environment, const Vector2<float> &pos, float quantity);
  float getFoodQuantity() const;
  float collectFood(float quantity);
  void update() override;
};

#endif