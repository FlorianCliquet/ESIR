/**
 * @file OrRule.cpp
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "rules/OrRule.hpp"
#include "rules/AbstractRule.hpp"
#include <vector>
#include <cassert>
OrRule::OrRule(AbstractRule *cond1, AbstractRule *cond2)
    // : cond1(std::unique_ptr<AbstractRule>(cond1)),
    //   cond2(std::unique_ptr<AbstractRule>(cond2)) {}
    : cond1(cond1),
      cond2(cond2){}

OrRule::OrRule(const std::vector<AbstractRule *> &rules) {
  assert(rules.size() >= 2 && "Why would you use a vector when there is less than 2 conditions ?");
  if (rules.size() == 2) {
    cond1 = rules[0];
    cond2 = rules[1];
  } else {
    cond1 = rules[0];
    std::vector<AbstractRule *> remainingRules(rules.begin() + 1, rules.end());
    cond2 = new OrRule(remainingRules);
  }
}

bool OrRule::condition(const EvaluationContext &ctx) {
  return cond1->condition(ctx) || cond2->condition(ctx); }

void OrRule::action(const EvaluationContext &ctx) {
  if (cond1->condition(ctx))
    cond1->action(ctx);
  else if (cond2->condition(ctx))
    cond2->action(ctx);
}

void OrRule::evaluate(const EvaluationContext &ctx) {
  if (this->condition(ctx))
      this->action(ctx);
}