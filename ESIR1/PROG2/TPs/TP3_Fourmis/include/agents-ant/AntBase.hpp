/**
 * @file AntBase.h
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef ANTBASE_H
#define ANTBASE_H

#include "agents-ant/Agent.hpp"
#include "agents-env/Anthill.hpp"
#include "agents-env/Food.hpp"
#include "utils/Vector2.hpp"
class AntBase : public Agent {
protected:
  Anthill *m_anthill;   /** Fourmilière de la fourmi */
  Vector2<float> m_dir; /** Vecteur de norme 1 */
  float m_speed;        /** par défaut 1cm/s */
  float m_lifetime;
  float m_foodCarried; /** max 5 */
public:
  static const float OPENING_ANGLE;
  static constexpr float MAX_FOOD = 5;
  static constexpr float MAX_DISTANCE_VIEW_FOOD = 3;
  static constexpr float MIN_DISTANCE_VIEW_FOOD = 0.5;
  AntBase(Environment *environment, Anthill *anthill);
  void move();
  void rotate(float angle);
  void turnAround();
  void orientTowards(const Vector2<float> &target);
  void dropFood();
  void collectFood(Food *foodsource);
  void update() override;

  Anthill *getAnthill() const;
  bool hasFood() const;
  const Vector2<float> &getDirection() const;
};
#endif