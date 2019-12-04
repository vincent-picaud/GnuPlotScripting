#include "GnuPlotScripting/export_as.hpp"

#include <gtest/gtest.h>

using namespace GnuPlotScripting;

TEST(Export_As, PNG)
{
  Export_As_PNG png;
  EXPECT_EQ(png.scripted("file.png"), "jkljl");
}
