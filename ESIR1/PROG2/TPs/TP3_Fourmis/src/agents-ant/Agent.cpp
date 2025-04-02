#include <set>
#include "agents-ant/Agent.hpp"
std::set<Agent *> Agent::s_agents;


Agent::Status Agent::getStatus() const { return m_status; }

void Agent::setStatus(const Agent::Status newStatus) { m_status = newStatus; }

void Agent::finalize() {
  for (Agent *agent : s_agents)
    delete agent;
  s_agents.clear();
}

void Agent::simulate() {
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