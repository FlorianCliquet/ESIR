#ifndef QTEST_H
#define QTEST_H

#include <tuple>
#include <utility>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class    QTest
///
/// \brief    Classe permettant de gérer et d'exécuter une série de tests unitaires.
///
/// \author   Florian Cliquet
/// \date     11/04/25
class QTest {
 public:
  /// \brief Exécute le test Q2.
  void Q2();

  /// \brief Exécute le test Q5.
  void Q5();

  /// \brief Exécute le test Q9.
  void Q9();

  /// \brief Exécute le test Q11.
  void Q11();

  /// \brief Exécute le test Q12.
  void Q12();

  /// \brief Exécute le test Q15.
  void Q15();

  /// \brief Exécute le test Q16.
  void Q16();

  /// \brief Exécute le test Q17.
  void Q17();

  /// \brief Exécute le test Q18_1.
  void Q18_1();

  /// \brief Exécute le test Q18_2.
  void Q18_2();

  /// \brief Exécute le test Q18Compression.
  void Q18Compression();

  /// \brief Exécute le test Q18Echo.
  void Q18Echo();

  /// \brief Exécute le test Q18Panning.
  void Q18Panning();

  /// \brief Retourne la liste de tous les tests.
  /// \return Un tuple contenant tous les tests à exécuter.
  auto GetTests() const {
    return std::make_tuple(
        &QTest::Q2,
        &QTest::Q5,
        &QTest::Q9,
        &QTest::Q11,
        &QTest::Q12,
        &QTest::Q15,
        &QTest::Q16,
        &QTest::Q17,
        &QTest::Q18_1,
        &QTest::Q18_2,
        &QTest::Q18Compression,
        &QTest::Q18Echo,
        &QTest::Q18Panning
    );
  }

  /// \brief Exécute tous les tests dans le tuple.
  /// \tparam Tuple Type du tuple contenant les méthodes de tests.
  /// \tparam I Indices des tests dans le tuple.
  template <typename Tuple, std::size_t... I>
  void RunAllTestsImpl(const Tuple& tests, std::index_sequence<I...>) {
    ((this->*std::get<I>(tests))(), ...);
  }

  /// \brief Lance l'exécution de tous les tests.
  void RunAllTests() {
    auto tests = GetTests();
    RunAllTestsImpl(tests, std::make_index_sequence<std::tuple_size_v<decltype(tests)>>{});
  }
};

#endif // QTEST_H