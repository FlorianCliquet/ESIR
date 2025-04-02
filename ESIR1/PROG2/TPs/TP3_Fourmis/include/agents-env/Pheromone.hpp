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
#include "agents-env/Anthill.hpp"
class Pheromone : public Agent {
public:
  enum class Type { SAFE, DANGER };
  static constexpr float DANGER_PHEROMONE_QTY = 400.f;
protected:
  static constexpr float EVAPORATION_RATE = 0.01;
  float m_quantity;
  Anthill *m_anthill;
  Type type;

public:
  Pheromone(Environment *environment, const Vector2<float> &pos, float quantity, Anthill* m_anthill, Type type=Type::SAFE);
  float getQuantity() const;
  void addQuantity(float q);
  Anthill* getAnthill() const;
  void update() override;
  void evaporate();
  Type getType() const { return type; }
  
};

#endif