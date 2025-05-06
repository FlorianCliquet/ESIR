#ifndef __MIXAGE__FILTRE__VOLUME__H
#define __MIXAGE__FILTRE__VOLUME__H

#include "mixage/filtre/filtre_base.hpp"
#include "mixage/filtre/multiplicateur.hpp"
#include "mixage/producteur/signal_constant.hpp"

#include <memory>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	volume
///
/// \brief	Classe représentant un filtre qui applique un changement de volume à un signal.
///         Cette classe multiplie le signal d'entrée par un facteur de volume. Elle utilise
///         un objet `multiplicateur` pour effectuer l'opération et un objet `signal_constant`
///         pour gérer le volume constant.
///
/// \author	Florian Cliquet
/// \date	09/04/2025
class volume : public filtre_base {
 private:
  multiplicateur filtre_multi_;  ///< Filtre qui applique la multiplication sur le signal d'entrée.
  signal_constant cst_;          ///< Signal constant utilisé pour le volume.

 public:
  /// \brief Constructeur de la classe volume.
  /// \param volume Le facteur de volume à appliquer.
  explicit volume(const double volume);

  /// \brief Connecte une entrée à ce filtre de volume.
  /// \param f Le flot à connecter à l'entrée.
  /// \param numentree L'indice de l'entrée à connecter.
  void connecterEntree(const std::shared_ptr<flot> &f, unsigned int numentree) override;

  /// \brief Récupère la sortie du filtre.
  /// \param numsortie L'indice de la sortie à récupérer.
  /// \return La sortie correspondante.
  const std::shared_ptr<flot> &getSortie(unsigned int numsortie) const override;

  /// \brief Change le facteur de volume.
  /// \param new_volume Le nouveau facteur de volume.
  void change_volume(const double new_volume);

  /// \brief Calcule le nouveau signal en appliquant le facteur de volume.
  /// \details Extrait l'échantillon de l'entrée, applique le filtre multiplicateur et insère
  ///          le résultat dans la sortie.
  void calculer() override;
};


#endif //  __MIXAGE__FILTRE__VOLUME__H