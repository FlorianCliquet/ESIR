#include <gtest/gtest.h>
#include "Liste.h"

// instancier Liste avec double puis string pour forcer le compilateur à
// compiler toutes les méthodes, même celles qui ne sont pas utilisées.
template class Liste<double>;
template class Liste<std::string>;

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::FLAGS_gtest_death_test_style = "threadsafe"; // ok
  return RUN_ALL_TESTS();
}
