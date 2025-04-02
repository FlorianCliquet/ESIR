#ifndef ANTBASE_H
#define ANTBASE_H

#include "agents-ant/Agent.hpp"
#include "agents-env/Anthill.hpp"
#include "agents-env/Environment.hpp"
#include "agents-env/Food.hpp"
#include "utils/MathUtils.hpp"
#include "utils/Vector2.hpp"
#include "utils/Timer.hpp"
#include "renderer/Renderer.hpp"

/**
 * @brief Comportement de Base des fourmis -> Chercher à manger -> prendre nourriture -> déposer la nourriture
 * 
 */
class AntBase : public Agent {
protected:
  Anthill *m_anthill;
  Vector2<float> m_dir;
  float m_speed;
  float m_lifetime;
  float m_foodCarried;

public:
  const float OPENING_ANGLE = MathUtils::piDiv2;
  static constexpr float MAX_FOOD = 5;
  static constexpr float MAX_DISTANCE_VIEW_FOOD = 3;
  static constexpr float MIN_DISTANCE_VIEW_FOOD = 0.5;

  AntBase(Environment *envionment, Anthill *anthill)
      : Agent(envionment, anthill->getPosition(), 1.5f), m_anthill(anthill),
        m_dir(Vector2<float>(1.0f, 0.01f)), m_speed(1.0f),
        m_lifetime(MathUtils::random(1000, 2500)), m_foodCarried(0) {}

  virtual ~AntBase() { getAnthill()->deathsignal(); }
  

  void update() override;

  virtual void move();

  void rotate(float angle);

  void turnAround();

  void orientTowards(const Vector2<float> &target);

  void dropFood();

  void collectFood(Food *foodsource);

  bool hasFood() const;

  const Vector2<float> &getDirection() const;

  Anthill *getAnthill() const;
  
};

#endif