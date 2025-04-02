#ifndef OR_RULE_H
#define OR_RULE_H
 
#include "rules/AbstractRule.hpp"
#include <vector>
#include <memory>
 
class OrRule : public AbstractRule {
protected:
  std::unique_ptr<AbstractRule> cond1;
  std::unique_ptr<AbstractRule> cond2;
 
public:
  // Constructor that takes ownership of two rules.
  OrRule(std::unique_ptr<AbstractRule> cond1, std::unique_ptr<AbstractRule> cond2);

  // Constructor that takes a vector of unique_ptr<AbstractRule>
  explicit OrRule(std::vector<std::unique_ptr<AbstractRule>> rules);

  bool condition(const EvaluationContext &ctx) override;
  void action(const EvaluationContext &ctx) override;
  void evaluate(const EvaluationContext &ctx);
};
 
#endif
 