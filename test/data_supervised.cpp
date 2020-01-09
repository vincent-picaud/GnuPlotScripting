#include "GnuPlotScripting/data_supervised.hpp"

#include <gtest/gtest.h>

using namespace GnuPlotScripting;

TEST(Data_Supervised, labels)
{
  std::array<double, 10> X_1 = {0.1, 0.3, 0.1, 0.6, 0.4, 0.6, 0.5, 0.9, 0.4, 0.7};  // X_1 feature
  std::array<double, 10> X_2 = {0.1, 0.4, 0.5, 0.9, 0.2, 0.3, 0.6, 0.2, 0.4, 0.6};  // X_2 feature
  std::array<int, 10> Y      = {1, 3, 1, 1, 1, 0, 2, 0, 0, 2};  // category (=label)

  Data_Supervised test(Y, X_1, X_2);  // note: the category vector Y is always the _first_ argument

  ASSERT_EQ(test.data(),
            "0.6 0.3 0 \n0.9 0.2 0 \n0.4 0.4 0 \n\n\n0.1 0.1 1 \n0.1 0.5 1 \n0.6 0.9 1 \n0.4 0.2 1 "
            "\n\n\n0.5 0.6 2 \n0.7 0.6 2 \n\n\n0.3 0.4 3 \n");

  ASSERT_EQ(test.I_size(), 10);
  ASSERT_EQ(test.J_size(), 2);      // CAVEAT J_size = X column size (hence here 2 and not 3)
  ASSERT_EQ(test.index_size(), 4);  // 4 categories: 0,1,2,3
}
