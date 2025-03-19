#include <deque>
#include <gtest/gtest.h>
#include <cstdlib>

// fichier qui contient l'implémentation de la classe Liste
#include "Liste.h"

// fonctions utilitaires
#include "common_p1.h"
#include "common_p2.h"
#include "common_p24.h"

//------------------------------------------------------------------------
// test find q3.1.1
//------------------------------------------------------------------------
TEST(TestList, q311Find)
{
  Liste<std::string> liste;
  std::deque<int>    longueurs;
  for (unsigned int i = 0; i <= 5; ++i) {
    liste.push_front(std::string(i+1, i + 'A'));
    liste.push_back (std::string(i+1, i + '1'));
    longueurs.push_front(i+1);
    longueurs.push_back (i+1);
    std::cout << std::string(i+1, i + 'A') << " - " << std::string(i+1, i + '1') << std::endl;
  }

  std::string x("A");
  Liste<std::string>::iterator it1(liste.begin());
  Liste<std::string>::iterator it2(liste.end());
  Liste<std::string>::iterator it3(find(it1, it2, x));
  ASSERT_TRUE(it3 != it2) << "Les 2 itérateurs devraient être différents";
  ASSERT_TRUE(it3 != it2) << "Les 2 itérateurs devraient être différents";
  ASSERT_TRUE(*it3 == x) << "it3 devrait pointer sur " << x;
  x = "666666";
  it3 = find(it1, it2, x);
  ASSERT_TRUE(it3 != it2) << "Les 2 itérateurs devraient être différents";
  ASSERT_TRUE(*it3 == x) << "it3 devrait pointer sur " << x;
  ++it1;
  ++it1;
  x = "FFFFFF";
  it3 = find(it1, it2, x);
  ASSERT_TRUE(it3 == it2);
}

// test find dans liste vide
TEST(TestList, q311FindListeVide)
{
  Liste<double> liste;
  Liste<double>::iterator pos = find(liste.begin(), liste.end(), 3.141519);
  ASSERT_TRUE(liste.end() == pos) << "Erreur recherche liste vide";
}
