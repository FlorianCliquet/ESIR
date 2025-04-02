#ifndef ANTBASEPHEROMONE_H
#define ANTBASEPHEROMONE_H

#include "agents-ant/AntBaseCombat.hpp"
#include "agents-env/Anthill.hpp"
#include "agents-env/Environment.hpp"
#include "agents-env/Pheromone.hpp"

/**
 * @brief Comportement de la fourmis vis à vis des pheromones
 * 
 */
class AntBasePheromone : public AntBaseCombat {
protected:
    static constexpr float MAX_DISTANCE_VIEW_PHEROMONE = 8.0;
    static constexpr float MIN_DISTANCE_VIEW_PHEROMONE = 0.0;
    static constexpr float PHEROMONE_AMOUNT_TO_DROP = 10.0;
    static constexpr float PHEROMONE_AMOUNT_TO_DROP_WHEN_CARRYING_FOOD = 100.0;
    static constexpr float PHEROMONE_AMOUNT_TO_DROP_WHEN_FIGHTING = 200.0;

public:
  AntBasePheromone(Environment *environment, Anthill *anthill)
      : AntBaseCombat(environment, anthill) {}
  
  ~AntBasePheromone(){};
  void putPheromone(float q);

  Pheromone *choosePheromone() const;
  void update() {
    AntBaseCombat::update();
    if (enemy != nullptr)
      putPheromone(PHEROMONE_AMOUNT_TO_DROP_WHEN_FIGHTING);
    else if (hasFood())
      putPheromone(PHEROMONE_AMOUNT_TO_DROP_WHEN_CARRYING_FOOD);
    else
      putPheromone(PHEROMONE_AMOUNT_TO_DROP);
  }
};

#endif
