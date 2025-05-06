#ifndef __MIXAGE__FILTRE__MIXEUR__H
#define __MIXAGE__FILTRE__MIXEUR__H

#include "mixage/filtre/filtre_compose.hpp"
#include "mixage/filtre/additionneur.hpp"
#include "mixage/filtre/volume.hpp"

#include <vector>
#include <memory>

/// \class mixeur
///
/// \brief Filtre composé permettant de mélanger plusieurs signaux d'entrée
///        avec des coefficients de volume donnés. Chaque entrée est connectée
///        à un filtre de type `volume_compose`, qui est ensuite relié à un `additionneur`.
///
/// \details
///        Ce filtre possède une sortie unique.
///        Chaque entrée est pondérée selon le volume spécifié au constructeur.
///
/// \author Cliquet Florian
/// \date 10/04/2025
class mixeur : public filtre_compose {
 public:
  /// \brief Constructeur du filtre mixeur.
  ///
  /// \param volumes Un vecteur de coefficients de volume (un par entrée).
  ///        La taille du vecteur détermine le nombre d’entrées du mixeur.
  explicit mixeur(const std::vector<double>& volumes)
      : filtre_compose(1, volumes.size()) {// 1 sortie, autant d'entrées que de volumes
  // Création d’un additionneur avec autant d’entrées que de volumes
  std::shared_ptr<additionneur> filtre_add =
      std::make_shared<additionneur>(volumes.size());
  // Pour chaque volume fourni :
  for (size_t i = 0; i < volumes.size(); ++i) {
    // Création d’un filtre de type volume avec le coefficient donné
      std::shared_ptr<volume> filtre_volume =
          std::make_shared<volume>(volumes.at(i));

    // L’entrée i du mixeur est reliée à l’entrée 0 du filtre_volume
      ajoutLienInput(i, filtre_volume, 0);
      
    // La sortie du filtre_volume est reliée à l’entrée i de l’additionneur
      filtre_add->connecterEntree(filtre_volume->getSortie(0), i);
      

    // Ajout du filtre_volume à la liste des composants internes
      ajoutComposant(filtre_volume);
    }

    // La sortie du mixeur correspond à la sortie 0 de l’additionneur
    ajoutLienOutput(0, filtre_add, 0);

    // Ajout de l’additionneur comme composant du mixeur
    ajoutComposant(filtre_add);
  }
};

#endif  // __MIXAGE__FILTRE__MIXEUR__H
