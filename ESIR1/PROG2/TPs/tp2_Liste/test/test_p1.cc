#include <deque>
#include <gtest/gtest.h>
#include <cstdlib>

// fichier qui contient l'implémentation de la classe Liste
#include "Liste.h"

// fonctions utilitaires
#include "common_p1.h"

//------------------------------------------------------------------------
// tests opérations bases liste (q1.1)
//------------------------------------------------------------------------

// initialiser liste vide
// - constructeur
// - empty
// - size
TEST(TestList, q11Init)
{
  Liste<double> liste;
  ASSERT_TRUE(liste.empty()) << "Liste devrait être vide";
  EXPECT_EQ(
	    (unsigned int) 0,
	    (unsigned int) liste.size()) << "Erreur taille liste";

  // test const : empty, size
  const Liste<double> & cl(liste);
  ASSERT_TRUE(cl.empty()) << "Liste devrait être vide";
  EXPECT_EQ(
	    (unsigned int) 0,
	    (unsigned int) cl.size()) << "Erreur taille liste";
}

#ifndef VALGRIND
// front() : assertion ! empty()
TEST(TestList, q11FrontAssert)
{
  Liste<double> liste;
  ASSERT_DEATH(liste.front(), "Assertion.*failed");
}
#endif

#ifndef VALGRIND
// front() const : assertion ! empty()
TEST(TestList, q11FrontAssertConst)
{
  const Liste<double> liste;
  ASSERT_DEATH(liste.front(), "Assertion.*failed");
}
#endif

// push_front, empty, size, front
TEST(TestList, q11Front)
{
  Liste<double> liste;
  unsigned int i;
  double x = 1.1;
  for (i = 1; i <= 5; ++i) {
    liste.push_front(i * x * x);
    ASSERT_TRUE(! liste.empty()) << "Liste ne devrait pas être vide";
    EXPECT_EQ(
	      (unsigned int) i,
	      (unsigned int) liste.size()) << "Erreur taille liste";
    EXPECT_EQ(
	      i * x * x,
	      liste.front()) << "Erreur élément tête";
    // accès modifiable ?
    liste.front() *= 9.9;
    EXPECT_EQ(
	      i * x * x * 9.9,
	      liste.front()) << "Erreur élément tête après modification";
  }

  // test const : empty, size, front
  const Liste<double> & cl(liste);
  ASSERT_TRUE(! cl.empty()) << "Liste ne devrait pas être vide";
  EXPECT_EQ(
	    (unsigned int) (i-1),
	    (unsigned int) cl.size()) << "Erreur taille liste";
  EXPECT_EQ(
	    (i-1) * x * x * 9.9,
	    cl.front()) << "Erreur élément tête";
}

#ifndef VALGRIND
// back() : assertion ! empty()
TEST(TestList, q11BackAssert)
{
  Liste<double> liste;
  ASSERT_DEATH(liste.back(), "Assertion.*failed");
}
#endif

#ifndef VALGRIND
// back() const : assertion ! empty()
TEST(TestList, q11BackAssertConst)
{
  const Liste<double> liste;
  ASSERT_DEATH(liste.back(), "Assertion.*failed");
}
#endif

// push_back, empty, size, back
TEST(TestList, q11Back)
{
  Liste<double> liste;
  unsigned int i;
  double x = 1.1;
  for (i = 1; i <= 5; ++i) {
    liste.push_back(i * x + 1);
    ASSERT_TRUE(! liste.empty()) << "Liste ne devrait pas être vide";
    EXPECT_EQ(
	      (unsigned int) i,
	      (unsigned int) liste.size()) << "Erreur taille liste";
    EXPECT_EQ(
	      i * x + 1,
	      liste.back()) << "Erreur élément queue";
    // accès modifiable ?
    liste.back() *= 9.9;
    EXPECT_EQ(
	      (i * x + 1) * 9.9,
	      liste.back()) << "Erreur élément queue après modification";
  }

  // test const : empty, size, back
  const Liste<double> & cl(liste);
  ASSERT_TRUE(! cl.empty()) << "Liste ne devrait pas être vide";
  EXPECT_EQ(
	    (unsigned int) (i-1),
	    (unsigned int) cl.size()) << "Erreur taille liste";
  EXPECT_EQ(
	    ((i-1) * x + 1) * 9.9,
	    cl.back()) << "Erreur élément queue";
}

// push_front/back, empty, size, front/back
TEST(TestList, q11FrontAndBack)
{
  Liste<double> liste;
  unsigned int i;
  double x = 1.1;
  for (i = 1; i <= 5; ++i) {
    liste.push_front(i * x * x);
    liste.push_back(i * x + 1);
    ASSERT_TRUE(! liste.empty()) << "Liste ne devrait pas être vide";
    EXPECT_EQ(
	      (unsigned int) (i * 2),
	      (unsigned int) liste.size()) << "Erreur taille liste";
    EXPECT_EQ(
	      i * x * x,
	      liste.front()) << "Erreur élément tête";
    EXPECT_EQ(
	      i * x + 1,
	      liste.back()) << "Erreur élément queue";
  }

  // test const : empty, size, front/back
  const Liste<double> & cl(liste);
  ASSERT_TRUE(! cl.empty()) << "Liste ne devrait pas être vide";
  EXPECT_EQ(
	    (unsigned int) (i-1)*2,
	    (unsigned int) cl.size()) << "Erreur taille liste";
  EXPECT_EQ(
	    (i-1) * x * x,
	    cl.front()) << "Erreur élément tête";
  EXPECT_EQ(
	    (i-1) * x + 1,
	    cl.back()) << "Erreur élément queue";
}

#ifndef VALGRIND
// pop_front() : assertion ! empty()
TEST(TestList, q11PopFrontAssert)
{
  Liste<double> liste;
  ASSERT_DEATH(liste.pop_front(), "Assertion.*failed");
}
#endif

// push_front, empty, size, front, pop_front
TEST(TestList, q11PopFront)
{
  Liste<double>	liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, front);
  list_equals_deque(liste, array, front);
}

#ifndef VALGRIND
// pop_back() : assertion ! empty()
TEST(TestList, q11PopBackAssert)
{
  Liste<double> liste;
  ASSERT_DEATH(liste.pop_back(), "Assertion.*failed");
}
#endif

// push_back, empty, size, back, pop_back
TEST(TestList, q11PopBack)
{
  Liste<double>	liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, back);
  list_equals_deque(liste, array, back);
}

TEST(TestList, q11Tout)
{
  Liste<double>		liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, alea);
  list_equals_deque(liste, array, alea);
}
