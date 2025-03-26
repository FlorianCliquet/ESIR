/**
 * @file Agent.cpp
 * @brief Implementation of the Agent class functions.
 * @author
 * @date 2025-03-21
 */

#include "agents-ant/Agent.hpp"
#include "utils/Vector2.hpp"
#include <set>

/** Definition of the static agent set */
std::set<Agent *> Agent::s_agents;

Agent::Agent(Environment *environment, const Vector2<float> &position, float radius)
    : Environment::LocalizedEntity(environment, position, radius), m_environment(environment),
      m_status(running) {
  s_agents.insert(this);
}

Agent::Status Agent::getStatus() const { return m_status; }

void Agent::setStatus(Status newStatus) { m_status = newStatus; }

void Agent::simulate() {
  // Iterate over agents; update running ones, remove and delete those marked for destruction.
  for (std::set<Agent *>::iterator it = s_agents.begin(); it != s_agents.end();) {
    Agent *agent = *it;
    if (agent->getStatus() == running) {
      agent->update();
      ++it;
    } else {
      it = s_agents.erase(it);
      delete agent;
    }
  }
}

void Agent::finalize() {
  // Delete all remaining agents and clear the set.
  for (Agent *agent : s_agents) {
    delete agent;
  }
  s_agents.clear();
}
