#include <algorithm>
#include <deque>
#include <gtest/gtest.h>
#include <cstdlib>

// fichier qui contient l'implémentation de la classe Liste
#include "Liste.h"

// fichier qui contient les deux fonctions chercherTri et copierTri de la partie 3
#include "copier.h"

// fonctions utilitaires
#include "common_p1.h"
#include "common_p2.h"
#include "common_p24.h"

//------------------------------------------------------------------------
// tests des autres fonctions de la partie 3
// - recherche dans une liste triée
// - copie triée d'une liste
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// test recherche liste vide
//------------------------------------------------------------------------
TEST(TestList, q321RechercheListeVide)
{
  Liste<double> liste;
  Liste<double>::iterator found = chercherTri(liste.begin(), liste.end(), 3.14159);
  ASSERT_TRUE(liste.end() == found) << "Erreur itérateur résultat";
}

//------------------------------------------------------------------------
// test recherche dans liste de taille 1
//------------------------------------------------------------------------
TEST(TestList, q321RechercheListeTaille1)
{
  Liste<double> liste;
  liste.push_back(3.14159);
  
  // Élément inférieur
  Liste<double>::iterator found = chercherTri(liste.begin(), liste.end(), -999.);
  ASSERT_TRUE(liste.begin() == found) << "Erreur itérateur résultat";

  // Élément égal
  found = chercherTri(liste.begin(), liste.end(), 3.14159);
  ASSERT_TRUE(liste.begin() == found) << "Erreur itérateur résultat";

  // Élément supérieur
  found = chercherTri(liste.begin(), liste.end(), 999.);
  ASSERT_TRUE(liste.end() == found) << "Erreur itérateur résultat";
}

void copier_array_list(const std::deque<double>& array, Liste<double>& liste)
{
  for (auto it = array.begin(); it != array.end(); ++it) {
    liste.push_back(*it);
  }
}

//------------------------------------------------------------------------
// test recherche dans liste triée
//------------------------------------------------------------------------
TEST(TestList, q321RechercheListe)
{
  std::deque<double> array;
  ajouter_elts(array);
  std::sort(array.begin(), array.end());
  
  Liste<double> liste;
  copier_array_list(array, liste);
  
  const double premier = array.front();
  const double dernier = array.back();

  // Test élément inférieur
  auto found = chercherTri(liste.begin(), liste.end(), premier - 1000);
  ASSERT_TRUE(liste.begin() == found) << "Erreur position élément inférieur";

  // Test élément premier
  found = chercherTri(liste.begin(), liste.end(), premier);
  ASSERT_TRUE(liste.begin() == found) << "Erreur position premier élément";

  // Test élément dernier
  found = chercherTri(liste.begin(), liste.end(), dernier);
  ASSERT_TRUE(--liste.end() == found) << "Erreur position dernier élément";

  // Test élément supérieur
  found = chercherTri(liste.begin(), liste.end(), dernier + 1000);
  ASSERT_TRUE(liste.end() == found) << "Erreur position élément supérieur";

  // Vérification de tous les éléments
  for (const auto& val : array) {
    found = chercherTri(liste.begin(), liste.end(), val);
    ASSERT_TRUE(*found == val) << "Erreur valeur trouvée pour " << val;
  }

  // Tests aléatoires
  for (int i = 0; i < 100; ++i) {
    const double x = drand48() * 1000;
    const auto array_it = std::lower_bound(array.begin(), array.end(), x);
    found = chercherTri(liste.begin(), liste.end(), x);
    
    if (array_it == array.end()) {
      ASSERT_TRUE(found == liste.end()) << "Erreur élément supérieur non détecté";
    } else {
      ASSERT_TRUE(*found == *array_it) << "Erreur valeur trouvée pour " << x;
    }
  }
}

//------------------------------------------------------------------------
// test copie triée liste vide
//------------------------------------------------------------------------
TEST(TestList, q322CopieListeVide)
{
  Liste<double> original;
  Liste<double>* copie = copierTri(original);
  
  ASSERT_TRUE(copie != nullptr) << "Pointeur null non autorisé";
  ASSERT_TRUE(copie->empty()) << "Copie devrait être vide";
  ASSERT_TRUE(copie->begin() == copie->end()) << "Itérateurs début/fin incorrects";
  
  delete copie;
}

//------------------------------------------------------------------------
// test copie triée avec modifications
//------------------------------------------------------------------------
TEST(TestList, q322CopieListe)
{
  Liste<double> original;
  std::deque<double> array;
  ajouter_elts(original, array);
  
  Liste<double>* copie = copierTri(original);
  std::sort(array.begin(), array.end());
  
  // Vérification copie initiale
  list_equals_deque_forward(*copie, array);

  // Modifications original
  original.pop_front();
  original.push_back(9999.99);
  
  // Vérification copie inchangée
  list_equals_deque_forward(*copie, array);
  
  delete copie;
}

//------------------------------------------------------------------------
// test copie triée avec modifications de la copie
//------------------------------------------------------------------------
TEST(TestList, q322CopieListeBis)
{
  Liste<double> original;
  std::deque<double> array;
  ajouter_elts(original, array);
  
  Liste<double>* copie = copierTri(original);
  std::deque<double> array_trie = array;
  std::sort(array_trie.begin(), array_trie.end());

  // Modifications copie
  copie->pop_front();
  array_trie.pop_front();
  
  // Vérifications
  list_equals_deque_forward(*copie, array_trie);
  list_equals_deque_forward(original, array);
  
  delete copie;
}