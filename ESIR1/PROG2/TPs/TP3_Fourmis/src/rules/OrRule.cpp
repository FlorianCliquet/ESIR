#include "rules/OrRule.hpp"
#include <cassert>
 
// Constructor taking two unique_ptr
OrRule::OrRule(std::unique_ptr<AbstractRule> cond1, std::unique_ptr<AbstractRule> cond2)
    : cond1(std::move(cond1)), cond2(std::move(cond2)) {}
 
// Constructor taking a vector of unique_ptr<AbstractRule>
// This constructor assumes that there are at least two rules.
OrRule::OrRule(std::vector<std::unique_ptr<AbstractRule>> rules) {
  assert(rules.size() >= 2 && "There must be at least 2 conditions in OrRule");
  if (rules.size() == 2) {
    cond1 = std::move(rules[0]);
    cond2 = std::move(rules[1]);
  } else {
    // More than two rules: use the first one as cond1 and combine the rest into cond2.
    cond1 = std::move(rules[0]);
    // Create a new vector for the remaining rules.
    std::vector<std::unique_ptr<AbstractRule>> remainingRules;
    remainingRules.reserve(rules.size() - 1);
    for (size_t i = 1; i < rules.size(); i++) {
      remainingRules.push_back(std::move(rules[i]));
    }
    cond2 = std::make_unique<OrRule>(std::move(remainingRules));
  }
}
 
bool OrRule::condition(const EvaluationContext &ctx) {
  return cond1->condition(ctx) || cond2->condition(ctx);
}
 
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