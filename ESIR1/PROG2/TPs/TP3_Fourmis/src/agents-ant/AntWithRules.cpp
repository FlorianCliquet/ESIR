/**
 * @file AntWithRules.cpp
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "agents-ant/AntWithRules.hpp"
#include "agents-ant/AntBasePheromone.hpp"
#include "agents-env/Anthill.hpp"
#include "agents-env/Environment.hpp"
#include "agents-env/Food.hpp"
#include "agents-env/Pheromone.hpp"
#include "rules/OrRule.hpp"
#include <cmath>
#include <vector>
#include "utils/Timer.hpp"

// ─── Antwithrules Implementation ─────────────────────────────────────────────

AntWithRules::AntWithRules(Environment *environment, Anthill *anthill)
    : AntBasePheromone(environment, anthill) {
  initializeRules();
}

AntWithRules::~AntWithRules() { delete compositeRule; }

void AntWithRules::initializeRules() {
  std::vector<AbstractRule *> rules;
  rules.reserve(6);

  rules.emplace_back(new RulePickUpFood(this));
  rules.emplace_back(new RuleMoveTowardFood(this));
  rules.emplace_back(new RuleFollowPheromone(this));
  rules.emplace_back(new RuleRandomPathing(this));
  rules.emplace_back(new RuleDepositFood(this));
  rules.emplace_back(new RulePathingToAnthill(this));

  compositeRule = new OrRule(rules);
}


void AntWithRules::update() {
  /**Deposit pheromones on every move:
    100 units if carrying food; otherwise 10 units.
    */
  OrRule::EvaluationContext ctx;
  ctx.PickUpFood = LocalizedEntity::perceive<Food>();
  ctx.ConeFood = LocalizedEntity::perceive<Food>(getDirection(), OPENING_ANGLE,
                                                 MAX_DISTANCE_VIEW_FOOD, MIN_DISTANCE_VIEW_FOOD);
  ctx.pheromone = choosePheromone();
  ctx.close_anthill = ((getPosition() - getAnthill()->getPosition()).norm() <= 2.0f);
    AntBasePheromone::update();
  if (compositeRule)
    compositeRule->evaluate(ctx);  
}

// ─── Inner Rule Implementations ──────────────────────────────────────────────

/**
 * @brief If the Ant is not carrying food and is directly on the top of food, pick it up
 * 
 * @return true 
 * @return false 
 */
bool AntWithRules::RulePickUpFood::condition(const EvaluationContext &ctx) {
  if (getTarget()->hasFood())
    return false;
  return !ctx.PickUpFood.empty();
}

void AntWithRules::RulePickUpFood::action(const EvaluationContext &ctx) {
  Food *food = ctx.PickUpFood.front();
  getTarget()->collectFood(food);
}

/**
 * @brief If the ant (not carrying food) perceives food in a cone then it sets its direction toward
 * the food and moves forward
 *
 */
bool AntWithRules::RuleMoveTowardFood::condition(const EvaluationContext &ctx) {
  if (getTarget()->hasFood())
    return false;
  return !ctx.ConeFood.empty();
}

void AntWithRules::RuleMoveTowardFood::action(const EvaluationContext &ctx) {
  Food *target = ctx.ConeFood.front();
  getTarget()->orientTowards(target->getPosition());
  getTarget()->move();
}

/**
 * @brief If the ant (still not carrying food) perceives pheromones, follow one of them
 *
 */
bool AntWithRules::RuleFollowPheromone::condition(const EvaluationContext &ctx) {
  if (getTarget()->hasFood())
    return false;
  return(ctx.pheromone != nullptr);
}

void AntWithRules::RuleFollowPheromone::action(const EvaluationContext &ctx) {
  getTarget()->orientTowards(ctx.pheromone->getPosition());
  getTarget()->move();
}

/**
 * @brief If no food or pheromones are perceived, the ant rotates by a random angle and moves
 * forward
 *
 */
bool AntWithRules::RuleRandomPathing::condition(const EvaluationContext &ctx) {
  return !getTarget()->hasFood();
}

void AntWithRules::RuleRandomPathing::action(const EvaluationContext &ctx) {
  float dt = Timer::dt();
  float new_angle = MathUtils::random(-M_PI / 10 * dt, M_PI / 10 * dt);
  getTarget()->rotate(new_angle);
  getTarget()->move();
}

/**
 * @brief When carrying Food but not (yet) on the anthill, orient toward the anthill
 *
 */
bool AntWithRules::RuleDepositFood::condition(const EvaluationContext &ctx) {
    return(ctx.close_anthill);
}

void AntWithRules::RuleDepositFood::action(const EvaluationContext &ctx) {
  getTarget()->dropFood();
  getTarget()->turnAround();
  getTarget()->move();
}

bool AntWithRules::RulePathingToAnthill::condition(const EvaluationContext &ctx) {
  return(!ctx.close_anthill);
}

void AntWithRules::RulePathingToAnthill::action(const EvaluationContext &ctx) {
    getTarget()->orientTowards(getTarget()->getAnthill()->getPosition());
    Pheromone *pheromone = getTarget()->choosePheromone();
    if (pheromone)
      getTarget()->orientTowards(pheromone->getPosition());
    getTarget()->move();
}
