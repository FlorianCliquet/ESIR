#include "agents-ant/AntWithRules.hpp"
#include "agents-ant/AntBaseCombat.hpp"
#include "agents-ant/AntBasePheromone.hpp"
#include "agents-env/Anthill.hpp"
#include "agents-env/Environment.hpp"
#include "agents-env/Food.hpp"
#include "agents-env/Pheromone.hpp"
#include "rules/OrRule.hpp"
#include <cmath>
#include <vector>
#include "utils/MathUtils.hpp"
#include "utils/Timer.hpp"
#include <vector>

// ─── Antwithrules Implementation ─────────────────────────────────────────────

AntWithRules::AntWithRules(Environment *environment, Anthill *anthill)
    : AntBasePheromone(environment, anthill) {
  initializeRules();
}

AntWithRules::~AntWithRules() { }

void AntWithRules::initializeRules() {
  std::vector<std::unique_ptr<AbstractRule>> rules;
  rules.reserve(7);

  rules.push_back(std::make_unique<RuleCombat>(this));
  rules.push_back(std::make_unique<RulePickUpFood>(this));
  rules.push_back(std::make_unique<RuleMoveTowardFood>(this));
  rules.push_back(std::make_unique<RuleFollowPheromone>(this));
  rules.push_back(std::make_unique<RuleRandomPathing>(this));
  rules.push_back(std::make_unique<RuleDepositFood>(this));
  rules.push_back(std::make_unique<RulePathingToAnthill>(this));

  compositeRule = std::make_unique<OrRule>(std::move(rules));
}

void AntWithRules::update() {
  OrRule::EvaluationContext ctx;
  ctx.PickUpFood = LocalizedEntity::perceive<Food>();
  ctx.ConeFood = LocalizedEntity::perceive<Food>(getDirection(), OPENING_ANGLE,
                                                 MAX_DISTANCE_VIEW_FOOD, MIN_DISTANCE_VIEW_FOOD);
  ctx.pheromone = choosePheromone();
  ctx.close_anthill = ((getPosition() - getAnthill()->getPosition()).norm() <= 2.0f);

  recoverStamina();
  if (compositeRule)
    compositeRule->evaluate(ctx);
  AntBasePheromone::update();
}

// ─── Inner Rule Implementations ──────────────────────────────────────────────

bool AntWithRules::RuleCombat::condition(const EvaluationContext &ctx) {
  AntBasePheromone *ant = getTarget();
  if (ant->getEnemy() && ant->getEnemy()->getStatus() != Agent::running && (ant->getPosition() - ant->getEnemy()->getPosition()).norm() > TRIGGER_RADIUS)
    ant->combatsignal(nullptr);
  if (ant->getEnemy() == nullptr) {
    ::std::vector<AntWithRules*> ennemies = ant->LocalizedEntity::perceive<AntWithRules>(ant->getDirection(), ant->OPENING_ANGLE,
                                                 MAX_DISTANCE_VIEW_FOOD);
    for (AntWithRules *new_enemy : ennemies){
      if (new_enemy && new_enemy->getStatus() == Agent::running && new_enemy->getAnthill() != ant->getAnthill()) {
        ant->combatsignal(new_enemy);
        break;
      }
    }
  }
  if (ant->getEnemy() && ant->getEnemy()->getStatus() == Agent::running && ant->getEnemy() != ant) {
    return true;
  }
  return false;
}

void AntWithRules::RuleCombat::action(const EvaluationContext &ctx) {
  AntBasePheromone *ant = getTarget();
  float distance = (ant->getPosition() - ant->getEnemy()->getPosition()).norm();
  if (distance <= HIT_RADIUS && ant->getStamina() > 0) {
    ant->getEnemy()->take_damage(ant->getDamage());
    ant->setStamina(ant->getStamina() - ant->getDamage()*2);
  }else if(distance <= TRIGGER_RADIUS && ant->getStamina() > 0){
    ant->orientTowards(ant->getEnemy()->getPosition());
    ant->move();
  }
}

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
  // 20% to not follow the pheromone
  return(ctx.pheromone != nullptr && MathUtils::compute_prob(80));
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