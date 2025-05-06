#include "mixage/producteur/signal_constant.hpp"

#include <cassert>
#include <memory>

#include "mixage/producteur.hpp"
#include "mixage/flot/imp_flot.hpp"

signal_constant::signal_constant(double signal_value)
    : signal_(std::make_shared<imp_flot>()), signal_value_(signal_value) {}

signal_constant::signal_constant(const signal_constant& other)
    : producteur(other),
      signal_(other.signal_),
      signal_value_(other.signal_value_) {}

signal_constant::~signal_constant() = default;

signal_constant& signal_constant::operator=(const signal_constant& other) {
  if (this != &other) {
    signal_ = other.signal_;
    signal_value_ = other.signal_value_;
  }
  return *this;
}

void signal_constant::calculer() {
  signal_->inserer(signal_value_);
}

unsigned int signal_constant::nbSorties() const {
  return 1;
}

const std::shared_ptr<flot>& signal_constant::getSortie(
    unsigned int numsortie) const {
  assert(numsortie == 0 && "signal_constant ne possède qu'une seule sortie (index 0)");
  return signal_;
}
