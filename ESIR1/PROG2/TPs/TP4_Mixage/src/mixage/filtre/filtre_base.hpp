#ifndef __MIXAGE__FILTRE__FILTRE_BASE__H
#define __MIXAGE__FILTRE__FILTRE_BASE__H

#include "mixage/filtre.hpp"
#include "mixage/consommateur/consommateur_base.hpp"
#include "mixage/producteur/producteur_base.hpp"

/// \class filtre_base
///
/// \brief Classe représentant un filtre de traitement sonore.
/// 
/// \author  Florian Cliquet
/// \date    09/04/2025
class filtre_base : public producteur_base, public consommateur_base, public filtre {
public:
  /// \brief Constructeur de la classe filtre_base.
  /// \param nb_sorties Le nombre de sorties de ce filtre.
  /// \param nb_entrees Le nombre d'entrées de ce filtre.
  filtre_base(const unsigned int nb_sorties, const unsigned int nb_entrees);

  /// Destructeur par défaut.
  ~filtre_base() override = default;

  /// \brief Retourne le nombre d'entrées de ce filtre.
  /// \return Le nombre d'entrées.
  unsigned int nbEntrees() const override;

  /// \brief Retourne l'entrée spécifiée par son indice.
  /// \param numentre L'indice de l'entrée à récupérer.
  /// \return Un objet `shared_ptr` vers l'entrée.
  const std::shared_ptr<flot>& getEntree(unsigned int numentre) const override;

  /// \brief Connecte un flux de type `flot` à une entrée spécifiée par son indice.
  /// \param f Le flux de type `flot` à connecter.
  /// \param numentree L'indice de l'entrée à connecter.
  void connecterEntree(const std::shared_ptr<flot>& f, unsigned int numentree) override;

  /// \brief Vérifie si toutes les entrées ont des échantillons disponibles.
  /// \return `true` si toutes les entrées ont des échantillons, sinon `false`.
  bool yaDesEchantillons() const override;

  /// \brief Retourne le nombre de sorties du filtre.
  /// \return Le nombre de sorties.
  unsigned int nbSorties() const override;

  /// \brief Retourne la sortie spécifiée par son indice.
  /// \param numsortie L'indice de la sortie à récupérer.
  /// \return Un objet `shared_ptr` vers la sortie.
  const std::shared_ptr<flot>& getSortie(unsigned int numsortie) const override;
};

#endif // __MIXAGE__FILTRE__FILTRE_BASE__H