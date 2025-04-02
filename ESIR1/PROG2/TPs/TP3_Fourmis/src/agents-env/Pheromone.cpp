#include "agents-env/Pheromone.hpp"
#include "agents-ant/Agent.hpp"
#include "agents-env/Anthill.hpp"
#include "agents-env/Environment.hpp"
#include "renderer/Renderer.hpp"
#include "utils/Timer.hpp"
#include "utils/Vector2.hpp"

Pheromone::Pheromone(Environment *environment, const Vector2<float> &pos, float quantity, Anthill* m_anthill, Type type)
    : Agent(environment, pos), m_quantity(quantity), m_anthill(m_anthill),type(type) {}

float Pheromone::getQuantity() const { return m_quantity; }

void Pheromone::addQuantity(float q) { m_quantity += q; }

void Pheromone::update() {
  evaporate();
  if (m_quantity < 0.01f)
    setStatus(destroy);
  Renderer::getInstance()->drawCircle(Agent::getPosition(), Agent::getRadius(),
                                      Renderer::Color(0, 128, 128, std::min(255.0f, m_quantity)));
}

void Pheromone::evaporate() { m_quantity -= EVAPORATION_RATE * m_quantity * Timer::dt() * ((type==Type::DANGER) ? 2 : 1); }

Anthill *Pheromone::getAnthill() const {
  return m_anthill;
}