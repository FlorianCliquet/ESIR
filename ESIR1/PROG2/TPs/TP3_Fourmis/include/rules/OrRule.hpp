/**
 * @file OrRule.hpp
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef OR_RULE_H
#define OR_RULE_H

#include "rules/AbstractRule.hpp"
#include <vector>
// #include <memory>
class OrRule : public AbstractRule {
protected:
  //   std::unique_ptr<AbstractRule> cond1;
  //   std::unique_ptr<AbstractRule> cond2;
  AbstractRule *cond1;
  AbstractRule *cond2;

public:
  OrRule(AbstractRule *cond1, AbstractRule *cond2);
  explicit OrRule(const std::vector<AbstractRule*>& rules);

  bool condition(const EvaluationContext &ctx) override;
  void action(const EvaluationContext &ctx) override;
  void evaluate(const EvaluationContext &ctx);
};
#endif