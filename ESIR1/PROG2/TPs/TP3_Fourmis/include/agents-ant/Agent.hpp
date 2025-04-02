#ifndef AGENT_H
#define AGENT_H

#include "agents-env/Environment.hpp"
#include "utils/Vector2.hpp"


/**
 * @brief Class Agent qui hérite de LocalizedEntity, c'est donc une entité placée dans
l'envrionnement et est capable d'intéragir avec en se repérant dans l'espace avec m_position , m_radius et m_environment
 * 
 */
class Agent : public Environment::LocalizedEntity {
public:
  enum Status { running, destroy };

private:
  // Herité de Environment::LocalizedEntity:
  // Vector2<float> m_positions;
  // float m_radius;
  // Envrionment *m_environment;
  Status m_status;
  static std::set<Agent *> s_agents;

public:
  Agent(Environment *environment, const Vector2<float> &position,
        float radius = Environment::LocalizedEntity::defaultRadius())
      : Environment::LocalizedEntity(environment, position, radius), m_status(running) {
    addAgent(this);
  };

  virtual ~Agent() {}
  
  virtual void update() = 0;

  Status getStatus() const;

  void setStatus(const Status newStatus);
  static void simulate();
  static void finalize();

private:
  static void addAgent(Agent *agent) { s_agents.insert(agent); }

  static void removeAgent(Agent *agent) { s_agents.erase(agent); }
  
};

#endif