#include "GnuPlotScripting/array_2.hpp"
#include "GnuPlotScripting/GnuPlotScripting.hpp"

#include <iostream>

using namespace GnuPlotScripting;

int
main()
{
  const double X = 2, Y = 2;
  const std::size_t I = 100, J = 120;

  const auto f = [=](const std::size_t i, const std::size_t j) {
    const double x = (2 * i / double(I - 1) - 1) * X;
    const double y = (2 * j / double(J - 1) - 1) * Y;

    return exp(-x * x - y * y);
  };

  Array_2 array_2(I, J, f);

  Data_Array_2 data(array_2);

  Script_File script("array_2.gp");

  script.free_form("set autoscale fix");
  script.free_form("plot {} matrix using 1:2:3 with image", data);
  script.export_as(PNG(), "array_2");
}
