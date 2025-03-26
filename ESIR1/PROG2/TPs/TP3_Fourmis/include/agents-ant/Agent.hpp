/**
 * @file Agent.hpp
 * @brief Declaration of the Agent abstract class.
 * @author
 * @date 2025-03-25
 */

#ifndef AGENT_H
#define AGENT_H

#include "agents-env/Environment.hpp"
#include <set>

/**
 * @brief Abstract base class representing an agent in the environment.
 */
class Agent : public Environment::LocalizedEntity {
public:
  enum Status { running, destroy };

private:
  Environment *m_environment;        ///< Pointer to the environment
  Status m_status;                   ///< Current status of the agent
  static std::set<Agent *> s_agents; ///< Set of all agents

public:
  /**
   * @brief Constructs an Agent.
   * @param environment Pointer to the environment.
   * @param position Initial position.
   * @param radius Agent radius (default obtained from LocalizedEntity::defaultRadius()).
   */
  Agent(Environment *environment, const Vector2<float> &position,
        float radius = Environment::LocalizedEntity::defaultRadius());

  /**
   * @brief Pure virtual update function to be implemented by derived classes.
   */
  virtual void update() = 0;

  /**
   * @brief Gets the current status of the agent.
   * @return Agent status.
   */
  Status getStatus() const;

  /**
   * @brief Sets a new status for the agent.
   * @param newStatus The new status.
   */
  void setStatus(Status newStatus);

  /**
   * @brief Simulates agents: updates those running and removes those marked for destruction.
   */
  static void simulate();

  /**
   * @brief Finalizes simulation by destroying all active agents.
   */
  static void finalize();
};

#endif // AGENT_H
