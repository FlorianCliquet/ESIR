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

// test find dans liste d'un élément
TEST(TestList, q311FindListe1Element)
{
  Liste<double> liste;
  liste.push_back(3.141519);
  
  // Élément absent
  Liste<double>::iterator pos = find(liste.begin(), liste.end(), -10.5);
  ASSERT_TRUE(liste.end() == pos) << "Erreur recherche élément absent";

  // Élément présent
  pos = find(liste.begin(), liste.end(), 3.141519);
  ASSERT_TRUE(liste.begin() == pos) << "Erreur recherche élément présent";
}

// test find dans liste de n éléments
TEST(TestList, q311FindListe)
{
  Liste<double> liste;
  std::deque<double> array;
  ajouter_elts(liste, array);

  for (unsigned int i = 0; i < array.size(); ++i) {
    // Élément présent
    Liste<double>::iterator pos = find(liste.begin(), liste.end(), array[i]);
    ASSERT_TRUE(pos != liste.end()) << "Erreur élément présent indice " << i;
    ASSERT_TRUE(*pos == array[i]) << "Valeur incorrecte à l'indice " << i;

    // Élément absent
    pos = find(liste.begin(), liste.end(), -array[i]-1);
    ASSERT_TRUE(pos == liste.end()) << "Erreur élément absent devrait être introuvable";
  }
}

//------------------------------------------------------------------------
// tests insert q3.1.2
//------------------------------------------------------------------------
#ifndef VALGRIND
TEST(TestList, q312InsertCurrentListAssertion)
{
  Liste<double> liste1;
  liste1.push_back(3.14159);
  Liste<double> liste2;
  liste2.push_back(-77.77); 
  ASSERT_DEATH(liste1.insert(liste2.begin(), 3.14159), "Assertion.*failed");
}
#endif

TEST(TestList, q312InsertListeVide)
{
  Liste<double> liste;
  Liste<double>::iterator new_elt = liste.insert(liste.begin(), 3.14159);
  
  ASSERT_TRUE(!liste.empty());
  ASSERT_TRUE(liste.size() == 1);
  ASSERT_TRUE(*liste.begin() == 3.14159);
  ASSERT_TRUE(new_elt == liste.begin());
}

void inserer_elts(Liste<double>& liste, std::deque<double>& array, Position ici = alea)
{
  const int array_size = 100 + rand() % 100;
  for (int i = 0; i < array_size; ++i) {
    double x = 5 + drand48();
    
    if (ici == front) {
      array.push_front(i * x * x);
      Liste<double>::iterator new_elt = liste.insert(liste.begin(), i * x * x);
      
      ASSERT_TRUE(array.size() == liste.size());
      ASSERT_TRUE(*array.begin() == *liste.begin());
      ASSERT_TRUE(new_elt == liste.begin());
    }
    else if (ici == back) {
      array.push_back(i * x + 1);
      Liste<double>::iterator new_elt = liste.insert(liste.end(), i * x + 1);
      
      ASSERT_TRUE(array.size() == liste.size());
      ASSERT_TRUE(*--array.end() == *--liste.end());
      ASSERT_TRUE(new_elt == --liste.end());
    }
    else {
      int pos = rand() % (1 + array.size());
      auto liste_it = liste.begin();
      auto array_it = array.begin();
      
      for (int p = 0; p < pos; ++p) { ++liste_it; ++array_it; }
      
      liste_it = liste.insert(liste_it, i * i * x + 1);
      array_it = array.insert(array_it, i * i * x + 1);
      
      ASSERT_TRUE(*array_it == *liste_it);
    }
  }
}

TEST(TestList, q312InsertTeteListe)
{
  Liste<double> liste;
  std::deque<double> array;
  ajouter_elts(liste, array);
  
  inserer_elts(liste, array, front);
  list_equals_deque_forward(liste, array);
}

TEST(TestList, q312InsertFinListe)
{
  Liste<double> liste;
  std::deque<double> array;
  ajouter_elts(liste, array);
  
  inserer_elts(liste, array, back);
  list_equals_deque_forward(liste, array);
}

TEST(TestList, q312InsertHasardListe)
{
  Liste<double> liste;
  std::deque<double> array;
  ajouter_elts(liste, array);
  
  inserer_elts(liste, array, alea);
  list_equals_deque_forward(liste, array);
}

//------------------------------------------------------------------------
// tests erase q3.1.3
//------------------------------------------------------------------------
#ifndef VALGRIND
TEST(TestList, q313EraseCurrentListAssertion)
{
  Liste<double> liste1;
  liste1.push_back(3.14159);
  Liste<double> liste2;
  liste2.push_back(-77.77); 
  ASSERT_DEATH(liste1.erase(liste2.begin()), "Assertion.*failed");
}
#endif

#ifndef VALGRIND
TEST(TestList, q313EraseEndListAssertion)
{
  Liste<double> liste;
  ASSERT_DEATH(liste.erase(liste.begin()), "Assertion.*failed");
}
#endif

TEST(TestList, q313EraseListe1Element)
{
  Liste<double> liste;
  liste.push_back(3.14159);
  Liste<double>::iterator next = liste.erase(liste.begin());
  
  ASSERT_TRUE(liste.empty());
  ASSERT_TRUE(next == liste.end());
}

TEST(TestList, q313Erase)
{
  Liste<double> liste;
  std::deque<double> array;
  ajouter_elts(liste, array);
  
  for (unsigned int i = 0; i < array.size(); ++i) {
    int pos = rand() % array.size();
    auto liste_it = liste.begin();
    auto array_it = array.begin();
    
    for (int p = 0; p < pos; ++p) { ++liste_it; ++array_it; }
    
    liste_it = liste.erase(liste_it);
    array_it = array.erase(array_it);
    
    ASSERT_TRUE(array.size() == liste.size());
    ASSERT_TRUE((array_it == array.end()) == (liste_it == liste.end()));
    
    if (array_it != array.end()) {
      ASSERT_TRUE(*array_it == *liste_it);
    }
    
    list_equals_deque_forward(liste, array);
  }
}