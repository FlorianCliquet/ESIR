#include "rules/AbstractAntRule.hpp"
#include "agents-ant/AntBasePheromone.hpp"

AbstractAntRule::AbstractAntRule(AntBasePheromone *target) : target(target) {}

AntBasePheromone *AbstractAntRule::getTarget() const { return target; }