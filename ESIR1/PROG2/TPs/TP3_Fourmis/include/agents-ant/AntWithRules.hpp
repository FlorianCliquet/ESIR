/**
 * @file AntWithRules.hpp
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef ANTWITHRULES_H
#define ANTWITHRULES_H

#include "agents-ant/AntBasePheromone.hpp"
#include "agents-env/Anthill.hpp"
#include "agents-env/Environment.hpp"
#include "rules/OrRule.hpp"
#include "rules/AbstractAntRule.hpp"
class AntWithRules : public AntBasePheromone {
public:
  AntWithRules(Environment *environment, Anthill *anthill);
  void update() override;
  ~AntWithRules() override;
private:
  OrRule *compositeRule; /**grouping all the ant's behaviour rules */
  void initializeRules();

  // ─── Inner Rule Classes ──────────────────────────────────────────────────────
  /**
   * @brief Echa rule inherits from AbstractAntRule which keeps a pointer to the ant
   *
   */
  class RulePickUpFood : public AbstractAntRule {
  public:
    RulePickUpFood(AntWithRules *ant) : AbstractAntRule(ant) {}
    virtual bool condition(const EvaluationContext &ctx) override;
    virtual void action(const EvaluationContext &ctx) override;
  };

  class RuleMoveTowardFood : public AbstractAntRule {
  public:
    RuleMoveTowardFood(AntWithRules *ant) : AbstractAntRule(ant) {}
    virtual bool condition(const EvaluationContext &ctx) override;
    virtual void action(const EvaluationContext &ctx) override;
  };
  class RuleFollowPheromone : public AbstractAntRule {
  public:
    RuleFollowPheromone(AntWithRules *ant) : AbstractAntRule(ant) {}
    virtual bool condition(const EvaluationContext &ctx) override;
    virtual void action(const EvaluationContext &ctx) override;
  };
  class RuleRandomPathing : public AbstractAntRule {
  public:
    RuleRandomPathing(AntWithRules *ant) : AbstractAntRule(ant) {}
    virtual bool condition(const EvaluationContext &ctx) override;
    virtual void action(const EvaluationContext &ctx) override;
  };
  class RuleDepositFood : public AbstractAntRule {
  public:
    RuleDepositFood(AntWithRules *ant) : AbstractAntRule(ant) {}
    virtual bool condition(const EvaluationContext &ctx) override;
    virtual void action(const EvaluationContext &ctx) override;
  };
  class RulePathingToAnthill : public AbstractAntRule {
  public:
    RulePathingToAnthill(AntWithRules *ant) : AbstractAntRule(ant) {}
    virtual bool condition(const EvaluationContext &ctx) override;
    virtual void action(const EvaluationContext &ctx) override;
  };
};

#endif