/**
 * @file AntBase.cpp
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "agents-ant/AntBase.hpp"
#include "agents-env/Environment.hpp"
#include "agents-env/Food.hpp"
#include "renderer/Renderer.hpp"
#include "utils/Timer.hpp"
AntBase::AntBase(Environment *environment, Anthill *anthill)
    : Agent(environment, anthill->getPosition(), 1.5f), /** Rayon par défaut 1.5 */
      m_anthill(anthill), m_dir(Vector2<float>::random().normalized()), m_speed(1.0f),
      m_lifetime(MathUtils::random(1000, 2500)), m_foodCarried(0) {}

const float AntBase::OPENING_ANGLE = MathUtils::piDiv2;

void AntBase::move() { translate(m_dir * m_speed * Timer::dt()); }

void AntBase::rotate(float angle) { m_dir = m_dir.rotate(angle); }

void AntBase::turnAround() { m_dir = -m_dir; }

void AntBase::orientTowards(const Vector2<float> &target) {
  m_dir = (target - getPosition()).normalized();
}

void AntBase::dropFood() {
  if (m_foodCarried > 0) {
    m_anthill->depositFood(m_foodCarried);
    m_foodCarried = 0;
  }
}

void AntBase::collectFood(Food *foodsource) {
  float collected = foodsource->collectFood(MAX_FOOD - m_foodCarried);
  m_foodCarried += collected;
}

void AntBase::update() {
  Renderer::getInstance()->drawPixel(getPosition(), (m_foodCarried > 0)
                                                        ? Renderer::Color(128, 255, 128, 255)
                                                        : Renderer::Color(255, 255, 255, 255));
  m_lifetime -= Timer::dt();
  if (m_lifetime <= 0)
    setStatus(destroy);
}

Anthill *AntBase::getAnthill() const { return m_anthill; }

bool AntBase::hasFood() const { return m_foodCarried > 0; }

const Vector2<float> &AntBase::getDirection() const { return m_dir; }