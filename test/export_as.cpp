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

TEST(Export_As, Export_Movable_and_Copyable)
{
  // movable
  PNG png;
  png = PNG();
  png = std::move(PNG());

  // copyable
  PNG png2 = PNG().set_enhanced(true);

  char ans[] =
      "set terminal push\nset terminal png enhanced \nset output 'file.png'\nreplot\nset terminal "
      "pop\n";

  EXPECT_EQ(png2.export_as("file.png"), ans);
}
