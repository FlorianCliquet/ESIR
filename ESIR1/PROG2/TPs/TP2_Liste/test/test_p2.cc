#include <deque>
#include <gtest/gtest.h>
#include <cstdlib>

// fichier qui contient l'implémentation de la classe Liste
#include "Liste.h"

// fonctions utilitaires
#include "common_p1.h"
#include "common_p2.h"

//------------------------------------------------------------------------
// tests const_iterator (2.1, 2.2, 2.3)
//------------------------------------------------------------------------

// const_iterator : tester begin et op *
TEST(TestList, q22Begin)
{
  Liste<double>		liste;
  liste.push_back(5.5);
  const Liste<double> & const_liste(liste);
  Liste<double>::const_iterator it_liste  = const_liste.begin();
  ASSERT_EQ(
	    5.5,
	    *it_liste)
    << "Erreur valeur élément de tête";
}

#ifndef VALGRIND
// const_iterator : tester assertion op *
TEST(TestList, q23AssertOpEtoile)
{
  Liste<double>		liste;
  liste.push_back(5.5);
  const Liste<double> & const_liste(liste);
  Liste<double>::const_iterator it_liste  = const_liste.end();
  ASSERT_DEATH(*it_liste , "Assertion.*failed");
}
#endif

#ifndef VALGRIND
// const_iterator : tester assertion op ++
TEST(TestList, q23AssertOpInc)
{
  const Liste<double>		liste;
  Liste<double>::const_iterator it  = liste.begin();
  ASSERT_DEATH(++it, "Assertion.*failed");
}
#endif

#ifndef VALGRIND
// const_iterator : tester assertion op --
TEST(TestList, q23AssertOpDec)
{
  const Liste<double>		liste;
  Liste<double>::const_iterator it  = liste.begin();
  ASSERT_DEATH(--it, "Assertion.*failed");
}
#endif

// const_iterator : tester == et !=
TEST(TestList, q23EgaliteIterateurs)
{
  Liste<double>		liste;
  const Liste<double> & const_liste(liste);
  Liste<double>::const_iterator it_gauche = const_liste.begin();
  Liste<double>::const_iterator it_droite = const_liste.end();

  // itérateurs begin() et end() dans une liste vide
  EXPECT_TRUE (it_gauche == it_droite) << "ERREUR : les deux itérateurs devraient être égaux";
  EXPECT_FALSE(it_gauche != it_droite) << "ERREUR : les deux itérateurs ne devraient pas être différents";

  // itérateurs begin() et end() dans une liste non vide
  liste.push_back(5.5);
  it_gauche = const_liste.begin();
  it_droite = const_liste.end();
  EXPECT_FALSE(it_gauche == it_droite) << "ERREUR : les deux itérateurs ne devraient pas être égaux";
  EXPECT_TRUE (it_gauche != it_droite) << "ERREUR : les deux itérateurs devraient être différents";

  // itérateurs sur deux éléments de même valeur
  // requiert ++
  liste.push_back(5.5);
  it_gauche = const_liste.begin();
  it_droite = const_liste.begin();
  ++it_droite;
  EXPECT_FALSE(it_gauche == it_droite) << "ERREUR : les deux itérateurs ne devraient pas être égaux";
  EXPECT_TRUE (it_gauche != it_droite) << "ERREUR : les deux itérateurs devraient être différents";
}

#ifndef VALGRIND
// const_iterator : assertion op ->
TEST(TestList, q23AssertionOpFleche)
{
  const Liste<std::string> liste;
  Liste<std::string>::const_iterator it(liste.begin());
  ASSERT_DEATH(it->size(), "Assertion.*failed");
}
#endif

// const_iterator : tester op ->
TEST(TestList, q23OpFleche)
{
  Liste<std::string> liste;
  std::deque<unsigned int>    longueurs;
  // mettre des chaînes de longueurs différentes dans la liste
  for (unsigned int i = 0; i <= 5; ++i) {
    liste.push_front(std::string(i+1, i + 'A'));
    liste.push_back (std::string(i+1, i + '1'));
    longueurs.push_front(i+1);
    longueurs.push_back (i+1);
  }
  // vérifier les longueurs des éléments : op ->
  const Liste<std::string> & const_liste(liste);
  Liste<std::string>::const_iterator it_liste = const_liste.begin();
  Liste<std::string>::const_iterator it_fin   = const_liste.end();
  unsigned int i = 0;
  while (it_liste != it_fin) {
    EXPECT_EQ(
	      longueurs[i],
	      it_liste->size()
	      )
      << "Erreur longueur élément " << i;
    ++it_liste;
    ++i;
  }
}

// const_iterator : parcours de liste en marche avant
TEST(TestList, q23Forward)
{
  Liste<double>		liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, alea);
  const Liste<double> & const_liste(liste);
  list_equals_deque_forward(const_liste, array);
}

// idem marche arrière
TEST(TestList, q23Backward)
{
  Liste<double>		liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, alea);
  const Liste<double> & const_liste(liste);
  list_equals_deque_backward(const_liste, array);
}
