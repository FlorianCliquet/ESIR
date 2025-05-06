#include "mixage/producteur/lecteur_fichier.hpp"

#include <iostream> 

lecteur_fichier::lecteur_fichier(const std::string& fp,
                                 const unsigned int nb_sortie)
    : producteur_base(nb_sortie), fichier_(fp, std::ios::binary),
      nb_sorties_(nb_sortie) {
  if (!fichier_.is_open())
    std::cerr << "Erreur : impossible d'ouvrir le fichier " << fp << std::endl;
}

lecteur_fichier::~lecteur_fichier() {
  if (fichier_.is_open())
    fichier_.close();
}

bool lecteur_fichier::can_read() {
  return fichier_.is_open() && !fichier_.eof();
}

void lecteur_fichier::calculer() {
  if (!can_read()) {
    fichier_.close();
    return;
  };

  for (unsigned int i = 0; i < nb_sorties_; ++i) {
    short data = 0;

    // Lecture de 2 octets pour chaque sortie (format PCM 16 bits signé)
    fichier_.read(reinterpret_cast<char*>(&data), sizeof(short));

    double echantillon = static_cast<double>(data) / 32768.0;

    // Insertion dans la sortie correspondante
    getSortie(i)->inserer(echantillon);
    if (!fichier_.good())
      return;
    if (fichier_.eof())
      fichier_.close();
  }
}
