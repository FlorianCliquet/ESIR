#ifndef FOOD_H
#define FOOD_H

#include "agents-ant/Agent.hpp"
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