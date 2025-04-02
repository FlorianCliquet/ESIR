#ifndef ABSTRACTRULE_H
#define ABSTRACTRULE_H
#include "agents-env/Food.hpp"
#include "agents-env/Pheromone.hpp"
#include <vector>
class AbstractRule {
public:
  struct EvaluationContext {
    std::vector<Food *> PickUpFood;
    std::vector<Food *> ConeFood;
    Pheromone *pheromone;
    bool close_anthill;
  };
  virtual bool condition(const EvaluationContext &ctx) = 0;
  virtual void action(const EvaluationContext &ctx) = 0;
  virtual ~AbstractRule() = default;
};

#endif