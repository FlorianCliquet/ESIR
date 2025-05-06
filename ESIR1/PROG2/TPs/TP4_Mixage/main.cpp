#include "tests/qtest.hpp"

int main() {
  QTest testing_tools;
  testing_tools.RunAllTests();
  return 0;
}