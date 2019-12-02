#include "GnuPlotScripting/hello.hpp"
#include <gtest/gtest.h>

using namespace GnuPlotScripting;

TEST(Hello, demo)
{
  ASSERT_EQ(hello(),"Hello GnuPlotScripting");
}
