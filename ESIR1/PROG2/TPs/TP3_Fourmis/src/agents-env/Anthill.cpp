#include "agents-env/Anthill.hpp"
#include "agents-ant/Agent.hpp"
#include "agents-ant/AntWithRules.hpp"
#include "renderer/Renderer.hpp"
 
Anthill::Anthill(Environment *environment, const Vector2<float> &pos)
     : Agent(environment, pos, ::Anthill::INITIAL_ANT_COUNT / 5.0) {
  for (int i = 0; i < Anthill::INITIAL_ANT_COUNT; i++) {
    new AntWithRules(environment, this);
  }
}
 
void Anthill::depositFood(float quantity) { 
  m_quantity += quantity; 
}

void Anthill::deathsignal() {
  number_of_ants--;
}
void Anthill::update() {
  Renderer::getInstance()->drawCircle(getPosition(),std::max(number_of_ants / 5.0f, 10.0f), Renderer::Color(0, 0, 255, 255));
 
  if (m_quantity >= Anthill::QUANTITY_THRESHOLD) {
    m_quantity -= Anthill::QUANTITY_THRESHOLD;
    new AntWithRules(getEnvironment(), this);
    number_of_ants++;
  }
  if (number_of_ants == 0)
    setStatus(destroy);
} 