/**
 * @file AbstractRule.hpp
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

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