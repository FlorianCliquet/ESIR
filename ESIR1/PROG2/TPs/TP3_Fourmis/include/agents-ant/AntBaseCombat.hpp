#ifndef ANTBASECOMBAT_H
#define ANTBASECOMBAT_H

#include "agents-ant/Agent.hpp"
#include "agents-ant/AntBase.hpp"
#include "agents-env/Pheromone.hpp"
#include <algorithm>

/**
 * @brief Mise en place des caractéristiques de la fourmis et différentes méthodes utilisées quand elle devra se battre pour défendre son territoire
 * 
 */
class AntBaseCombat : public AntBase {
protected:
  float m_health_bar = 100.0;
  float stamina = 100.0;
  float m_damage = 5;
  AntBaseCombat *enemy = nullptr; ///< Pointeur non propriétaire
public:
  static constexpr float HIT_RADIUS = 1.5;
  static constexpr float TRIGGER_RADIUS = 15.0;
  static const float COMBAT_OPENING_ANGLE;
  static constexpr float MAX_DISTANCE_VIEW_ANT = 10.0;
  static constexpr float STAMINA_REGEN = 5.0f;
  static constexpr float STAMINA_THRESHOLD = 20.0f;

  AntBaseCombat(Environment *environment, Anthill *anthill) : AntBase(environment, anthill) {
    enemy = nullptr;
  }

  ~AntBaseCombat() { enemy = nullptr; }
  
  void update() override;

  void move() override;

  float getDamage() const;

  void take_damage(const float amount);

  void heal(const float amount);

  float getHealBar() const;

  float getStamina() const;

  void setStamina(const float qty);

  bool isTired() const;

  void recoverStamina();

  void deathsignal();

  void dropDangerPheromone();

  AntBaseCombat *getEnemy() const;

  void combatsignal(AntBaseCombat *ant);  
};

#endif