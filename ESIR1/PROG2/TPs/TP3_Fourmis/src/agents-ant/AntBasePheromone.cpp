#include "agents-ant/AntBasePheromone.hpp"
#include "agents-env/Pheromone.hpp"
#include "utils/MathUtils.hpp"
#include <vector>
void AntBasePheromone::putPheromone(float q) {
  std::vector<Pheromone *> curr_pheromone = LocalizedEntity::perceive<Pheromone>();
  Pheromone *matchingPheromone = nullptr;
  for (Pheromone *p : curr_pheromone)
    if ((p->getAnthill() == m_anthill)) {
      matchingPheromone = p;
      break;
    }
  if (matchingPheromone == nullptr)
    new Pheromone(getEnvironment(), getPosition(), q, m_anthill);
  else
   matchingPheromone->addQuantity(q);
}

Pheromone *AntBasePheromone::choosePheromone() const {
  const auto perceivedPheromones = LocalizedEntity::perceive<Pheromone>(
      getDirection(), OPENING_ANGLE, MAX_DISTANCE_VIEW_PHEROMONE, MIN_DISTANCE_VIEW_PHEROMONE);
  if (perceivedPheromones.empty())
    return nullptr;
  std::vector<float> weights;
  weights.reserve(perceivedPheromones.size());
  for (const auto &pheromone : perceivedPheromones)
    if (pheromone->getAnthill() == m_anthill)
      weights.push_back(pheromone->getQuantity());
  if (weights.empty())
    return nullptr;
  const size_t chosenIndex = MathUtils::randomChoose(weights);
  return perceivedPheromones[chosenIndex];
}