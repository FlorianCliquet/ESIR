#ifndef __MIXAGE__FLOT__IMP__FLOT__H
#define __MIXAGE__FLOT__IMP__FLOT__H

#include "mixage/flot.hpp"

#include <deque>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	imp_flot
///
/// \brief	 Implémentation de l'interface flot. Cette classe permet de gérer une collection d'échantillons
///        sous forme de deque . Elle offre des fonctionnalités pour insérer des échantillons,
///        les extraire dans un ordre précis et vérifier si la collection est vide.
///
/// \author	Florian Cliquet
/// \date	09/04/2025
class imp_flot : public flot {
private:
  std::deque<double> echantillons_;

public:
  /// \brief Insert le nouvel echantillon dans samples (std::dequeue<double>)
  /// \param le nouvel échantillon
  void inserer(double echantillon) override;

  /// \brief Extrait l'échantillon au top de la deque (et le pop).
  /// \pre !vide()
  /// \return L'échantillon à la tête de la deque.
  double extraire() override;

  /// \brief Indique si la deque est vide ou non
  /// \return True si la deque est vide, False sinon.
  bool vide() const override;
};

#endif // __MIXAGE__FLOT__IMP__FLOT__H