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
  std::unique_ptr<OrRule> compositeRule; /**regroupement des différentes règles qui s'applique aux fourmis*/
  void initializeRules();

  // ─── Inner Rule Classes ──────────────────────────────────────────────────────
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
  class RuleCombat : public AbstractAntRule {
  public:
    RuleCombat(AntWithRules *ant) : AbstractAntRule(ant) {}
    virtual bool condition(const EvaluationContext &ctx) override;
    virtual void action(const EvaluationContext &ctx) override;
  };
};

#endif