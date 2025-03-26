/**
 * @file Pheromone.cpp
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "agents-env/Pheromone.hpp"
#include "agents-ant/Agent.hpp"
#include "agents-env/Environment.hpp"
#include "renderer/Renderer.hpp"
#include "utils/Timer.hpp"
#include "utils/Vector2.hpp"

Pheromone::Pheromone(Environment *environment, const Vector2<float> &pos, float quantity)
    : Agent(environment, pos), m_quantity(quantity) {}

float Pheromone::getQuantity() const { return m_quantity; }

void Pheromone::addQuantity(float q) { m_quantity += q; }

void Pheromone::update() {
  evaporate();
  if (m_quantity < 0.01f)
    setStatus(destroy);
  Renderer::getInstance()->drawCircle(Agent::getPosition(), Agent::getRadius(),
                                      Renderer::Color(0, 128, 128, std::min(255.0f, m_quantity)));
}

void Pheromone::evaporate() { m_quantity -= EVAPORATION_RATE * m_quantity * Timer::dt(); }