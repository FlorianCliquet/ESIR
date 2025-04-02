#include "agents-ant/AntBase.hpp"

void AntBase::update() {
    Renderer::getInstance()->drawPixel(getPosition(), (m_foodCarried > 0)
                                                          ? Renderer::Color(128, 255, 128, 255)
                                                          : Renderer::Color(255, 255, 255, 255));
    m_lifetime -= Timer::dt();
    if (m_lifetime <= 0)
      setStatus(destroy);
}

void AntBase::move() { translate(m_dir * (m_speed * Timer::dt())); }

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

bool AntBase::hasFood() const { return m_foodCarried > 0; }

const Vector2<float> &AntBase::getDirection() const { return m_dir; }

Anthill *AntBase::getAnthill() const { return m_anthill; }  