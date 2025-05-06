#ifndef __MIXAGE__PRODUCTEUR__LECTEUR_FICHIER__H
#define __MIXAGE__PRODUCTEUR__LECTEUR_FICHIER__H

#include "mixage/producteur/producteur_base.hpp"

#include <fstream>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class  lecteur_fichier
///
/// \brief  Producteur qui lit des échantillons depuis un fichier. 
///         Chaque ligne du fichier doit contenir un ou plusieurs échantillons (doubles),
///         séparés par des espaces ou tabulations, en fonction du nombre de sorties.
///
/// \author Florian Cliquet
/// \date   10/04/2025
class lecteur_fichier : public producteur_base {
 private:
  std::ifstream fichier_;       ///< Flux du fichier d'entrée à lire.
  const unsigned int nb_sorties_;  ///< Nombre de sorties du producteur.

 public:
  /// \brief Constructeur.
  /// \param fd Nom du fichier à ouvrir en lecture.
  /// \param nb_sortie Nombre de sorties attendues.
  lecteur_fichier(const std::string& fd, const unsigned int nb_sortie);

  /// \brief Destructeur : ferme le fichier s’il est encore ouvert.
  ~lecteur_fichier() override;

  /// \brief Vérifie si le fichier est prêt pour la lecture.
  /// \return true si le fichier est ouvert et non terminé, false sinon.
  bool can_read();

  /// \brief Lecture d’une ligne du fichier et insertion des échantillons dans les sorties.
  void calculer() override;
};

#endif  // __MIXAGE__PRODUCTEUR__LECTEUR_FICHIER__H