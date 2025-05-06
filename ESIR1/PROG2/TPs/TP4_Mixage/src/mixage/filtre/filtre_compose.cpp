#include "mixage/filtre/filtre_compose.hpp"

filtre_compose::filtre_compose(unsigned int nb_sorties, unsigned int nb_entrees)
    : filtre_base(nb_sorties, nb_entrees) {}

void filtre_compose::connecterEntree(const std::shared_ptr<flot>& f,
                                     unsigned int numentree) {
  filtre_base::connecterEntree(f, numentree);

  // Vérifie si un lien a été enregistré pour cette entrée
  if (liens_.find(numentree) != liens_.end()) {
    auto& [composant_input_index, composant_ptr] = liens_.at(numentree);
    composant_ptr->connecterEntree(getEntree(numentree), composant_input_index);
  }
}

void filtre_compose::calculer() {
  for (auto &c : composants_)
    c->calculer();
}

void filtre_compose::ajoutComposant(
    const std::shared_ptr<composant> &new_composant) {
  composants_.push_back(new_composant);
}

void filtre_compose::ajoutLienInput(const unsigned int input_index,
                                    const std::shared_ptr<filtre> &composant,
                                    const unsigned int composant_input_index) {
  liens_.insert({input_index,{composant_input_index,composant}});
}

void filtre_compose::ajoutLienOutput(
    const unsigned int output_index, const std::shared_ptr<filtre> &composant,
    const unsigned int composant_output_index) {
  connecterSortie(composant->getSortie(composant_output_index), output_index);
}