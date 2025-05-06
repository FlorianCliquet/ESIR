#include "mixage/flot/imp_flot.hpp"
#include <cassert>

void imp_flot::inserer(double echantillon) {
  echantillons_.push_back(echantillon);
}

double imp_flot::extraire() {
  assert(!vide() && "Tentative d'extraction sur une collection vide");
  double front = echantillons_.front();
  echantillons_.pop_front();
  return front;
}

bool imp_flot::vide() const { return echantillons_.empty(); }
