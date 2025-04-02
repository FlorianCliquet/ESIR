#include "agents-ant/AntBaseCombat.hpp"

void AntBaseCombat::update(){
  AntBase::update();
  if (m_health_bar <= 0) {
    dropDangerPheromone();
    setStatus(destroy);
  }
}

void AntBaseCombat::move() { translate(m_dir * m_speed * Timer::dt() * stamina / 100); }

float AntBaseCombat::getDamage() const { return m_damage; }

void AntBaseCombat::take_damage(const float amount) {
  assert(amount >= 0);
  m_health_bar -= amount;
}

void AntBaseCombat::heal(const float amount) {
  assert(amount >= 0);
  m_health_bar += amount;
}

float AntBaseCombat::getHealBar() const { return m_health_bar; }

float AntBaseCombat::getStamina() const { return stamina; }

void AntBaseCombat::setStamina(const float qty){ stamina = qty;}

bool AntBaseCombat::isTired() const { return stamina <= STAMINA_THRESHOLD; }

void AntBaseCombat::recoverStamina() {
  if(stamina < 100.f)stamina = std::min(stamina + STAMINA_REGEN, 100.0f);
}

void AntBaseCombat::deathsignal() {
  if(enemy)enemy->enemy = nullptr;
}

void AntBaseCombat::dropDangerPheromone() {
  new Pheromone(getEnvironment(),getPosition(),Pheromone::DANGER_PHEROMONE_QTY,m_anthill,Pheromone::Type::DANGER);
}

AntBaseCombat *AntBaseCombat::getEnemy() const { return enemy; }

void AntBaseCombat::combatsignal(AntBaseCombat *ant) { enemy = ant; }