#include "GnuPlotScripting/export_as.hpp"

#include <gtest/gtest.h>

using namespace GnuPlotScripting;

TEST(Export_As, PNG)
{
  PNG png;
  char ans[] =
      "set terminal push\nset terminal png \nset output 'file.png'\nreplot\nset terminal "
      "pop\n";

   EXPECT_EQ(png.export_as("file.png"), ans);
}
