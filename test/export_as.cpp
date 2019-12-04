#include "GnuPlotScripting/export_as.hpp"

#include <gtest/gtest.h>

using namespace GnuPlotScripting;

TEST(Export_As, PNG)
{
  PNG png;
  char ans[] =
      "set terminal push\nset terminal png\nset output 'file.png' color true\nreplot\nset terminal "
      "pop\nreplot\n";

  EXPECT_EQ(png.scripted("file.png"), ans);
}
