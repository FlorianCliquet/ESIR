#ifndef __MIXAGE__FILTRE__FILTRE_COMPOSE__H
#define __MIXAGE__FILTRE__FILTRE_COMPOSE__H

#include "mixage/filtre/filtre_base.hpp"

#include <map>
#include <memory>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class filtre_compose
///
/// \brief Cette classe permet de composer plusieurs filtres internes pour former un filtre complexe.
///        Elle hérite de filtre_base, donc gère des entrées/sorties de flots.
///        Les composants internes (de type filtre ou composant) peuvent être liés manuellement
///        via des méthodes pour gérer leur connexion logique.
///
/// \author Florian Cliquet
/// \date 10/04/2025
class filtre_compose : public filtre_base {
private:
   std::vector<std::shared_ptr<composant>>
       composants_; ///< Liste des composants internes du filtre composé.

   std::map<unsigned int, std::pair<unsigned int, std::shared_ptr<filtre>>>
       liens_; ///< Liens entre les entrées du filtre composé et celles des
               ///< composants internes.

 public:
  /// \brief Constructeur du filtre composé.
  /// \param nb_sorties Nombre de sorties globales du filtre composé.
  /// \param nb_entrees Nombre d'entrées globales du filtre composé.
  filtre_compose(unsigned int nb_sorties, unsigned int nb_entrees);

  /// \brief Connecte un flot à une entrée du filtre composé.
  /// \param f Le flot à connecter.
  /// \param numentree L’indice de l’entrée à connecter.
  void connecterEntree(const std::shared_ptr<flot>& f,
                       unsigned int numentree) override;

  /// \brief Lance le calcul de tous les composants internes.
  void calculer() override;

  /// \brief Ajoute un composant au système interne.
  /// \param new_composant Le nouveau composant à intégrer.
  void ajoutComposant(const std::shared_ptr<composant>& new_composant);

  /// \brief Crée un lien entre une entrée du filtre composé et un composant interne.
  /// \param input_index Index de l’entrée du filtre global.
  /// \param composant Le filtre à connecter.
  /// \param composant_input_index L’entrée du composant interne à connecter.
  void ajoutLienInput(unsigned int input_index,
                      const std::shared_ptr<filtre>& composant,
                      unsigned int composant_input_index);

  /// \brief Crée un lien entre une sortie d’un composant interne et une sortie du filtre global.
  /// \param output_index L’index de la sortie du filtre global.
  /// \param composant Le composant concerné.
  /// \param composant_output_index L’indice de sortie dans le composant.
  void ajoutLienOutput(unsigned int output_index,
                       const std::shared_ptr<filtre>& composant,
                       unsigned int composant_output_index);
};

#endif  // __MIXAGE__FILTRE__FILTRE_COMPOSE__H