#ifndef __MIXAGE__FILTRE__OPERATION_BINAIRE__H
#define __MIXAGE__FILTRE__OPERATION_BINAIRE__H

#include "mixage/filtre/filtre_base.hpp"

#include <cassert>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	operation_binaire
///
/// \brief	Classe générique représentant une opération binaire appliquée à
/// deux entrées.
///         Cette classe hérite de filtre_base et permet de traiter deux
///         entrées, puis d'insérer le résultat de l'opération dans la sortie.
///
/// \tparam T Le type de l'opération binaire (doit être callable avec deux
/// doubles).
/// 
/// \author	Florian Cliquet
/// \date	09/04/2025
template <class T>
class operation_binaire : public filtre_base {
 public:
  /// \brief Constructeur par défaut de l'opération binaire.
  /// \details Initialise le filtre avec une sortie et deux entrées (hérité de filtre_base).
  operation_binaire() : filtre_base(1, 2) {}

  /// \brief Vérifie que le type T est constructible par défaut.
  static_assert(std::is_default_constructible<T>::value,
                "T doit être constructible par défaut");

  /// \brief Vérifie que le type T est callable avec deux doubles et retourne un double.
  static_assert(std::is_invocable_r<double, T, double, double>::value,
                "T doit être appelable avec deux doubles et retourner un double");

  /// \brief Calcule le résultat de l'opération binaire et l'insère dans la sortie.
  ///
  /// \pre Ya des échantillons disponibles dans les deux entrées.
  /// \details Cette méthode extrait deux échantillons des entrées, applique l'opération binaire 
  ///          (définie par le type T), et insère le résultat dans la sortie.
  void calculer() override {
    assert(yaDesEchantillons() && "Il n'y a pas d'échantillons disponibles dans les entrées");

    T operation;
    double result =
        operation(getEntree(0)->extraire(), getEntree(1)->extraire());

    getSortie(0)->inserer(result);
  }
};

#endif // __MIXAGE__FILTRE__OPERATION_BINAIRE__H
