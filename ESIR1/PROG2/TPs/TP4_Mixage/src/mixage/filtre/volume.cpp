#include "mixage/filtre/volume.hpp"
#include "mixage/filtre/filtre_base.hpp"

#include <cassert>

volume::volume(const double volume)
    : filtre_base(1, 1), filtre_multi_(), cst_(volume) {
        filtre_multi_.connecterEntree(cst_.getSortie(0), 0);
}

void volume::connecterEntree(const std::shared_ptr<flot> &f, unsigned int numentree) {
  filtre_base::connecterEntree(f, numentree);
  filtre_multi_.connecterEntree(getEntree(0),1);
}

const std::shared_ptr<flot> &volume::getSortie(unsigned int numsortie) const {
  return filtre_multi_.getSortie(numsortie);
}

void volume::change_volume(const double new_volume) {
  cst_ = signal_constant(new_volume);
}

void volume::calculer() {
  if(!yaDesEchantillons())
    return;
  cst_.calculer();
  filtre_multi_.calculer();
}