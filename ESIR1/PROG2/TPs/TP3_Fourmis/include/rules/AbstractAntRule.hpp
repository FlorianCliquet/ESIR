#ifndef ABSTRACTANTRULE_H
#define ABSTRACTANTRULE_H

#include "agents-ant/AntBasePheromone.hpp"
#include "rules/AbstractRule.hpp"
class AbstractAntRule : public AbstractRule {
private:
  AntBasePheromone *target;

public:
  explicit AbstractAntRule(AntBasePheromone *target);
  AntBasePheromone *getTarget() const;
};

#endif