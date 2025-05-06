#ifndef __MIXAGE__PRODUCTEUR__SIGNAL_CONSTANT__H
#define __MIXAGE__PRODUCTEUR__SIGNAL_CONSTANT__H

#include "mixage/producteur.hpp"

#include <memory>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class  signal_constant
///
/// \brief  Génère un signal constant. Cette classe implémente l'interface producteur
///         en produisant en sortie une suite infinie d’échantillons tous égaux à une
///         valeur fixée lors de la construction de l’objet. La sortie est représentée
///         par un flot interne de type imp_flot.
///
/// \author Florian Cliquet
/// \date   09/04/2025
class signal_constant : public producteur {
private:
  std::shared_ptr<flot> signal_;  ///< Flot de sortie contenant les échantillons constants
  double signal_value_;           ///< Valeur constante à produire

public:
  /// \brief Constructeur principal.
  /// \param signal_value La valeur constante à insérer dans le flot.
  explicit signal_constant(double signal_value);

  /// \brief Constructeur de copie.
  /// \param other L'instance à copier.
  signal_constant(const signal_constant& other);

  /// \brief Destructeur.
  ~signal_constant() override;

  /// \brief Opérateur d'affectation.
  /// \param other L'objet source.
  /// \return Une référence sur l'objet courant après affectation.
  signal_constant& operator=(const signal_constant& other);

  /// \brief Effectue un calcul : insère un échantillon constant dans le flot de sortie.
  void calculer() override;

  /// \brief Retourne le nombre de sorties (toujours 1 pour cette classe).
  /// \return Le nombre de sorties disponibles.
  unsigned int nbSorties() const override;

  /// \brief Accès à la sortie spécifiée.
  /// \pre numsortie inférieur au nombre de sorties
  /// \param numsortie L'index de la sortie (doit être 0).
  /// \return Une référence partagée vers le flot correspondant.
  const std::shared_ptr<flot>& getSortie(unsigned int numsortie) const override;
};

#endif // __MIXAGE__PRODUCTEUR__SIGNAL_CONSTANT__H
