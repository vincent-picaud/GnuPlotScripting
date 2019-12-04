#include "GnuPlotScripting/global_config.hpp"

#include <gtest/gtest.h>

using namespace GnuPlotScripting;

TEST(Global_Config_As, basic_use)
{
  EXPECT_EQ(global_config().cerr_log(), true);
  global_config().set_cerr_log(false);
  EXPECT_EQ(global_config().cerr_log(), false);
}