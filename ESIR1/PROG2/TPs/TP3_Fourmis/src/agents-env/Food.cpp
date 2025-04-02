#include "agents-env/Food.hpp"
#include "renderer/Renderer.hpp"
Food::Food(Environment *environment, const Vector2<float> &pos, float quantity)
    : Agent(environment, pos, MathUtils::circleRadius(quantity)), m_quantity(quantity) {}

float Food::getFoodQuantity() const { return m_quantity; }

float Food::collectFood(float quantity) {
  float collected = (quantity > m_quantity) ? m_quantity : quantity;
  m_quantity -= collected;
  return collected;
}

void Food::update() {
  setRadius(MathUtils::circleRadius(m_quantity));
  Renderer::getInstance()->drawCircle(getPosition(), getRadius(),
                                      Renderer::Color(154, 235, 38, 255));
  if (m_quantity <= 0)
    setStatus(destroy);
}