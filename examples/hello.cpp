
#include "GnuPlotScripting/GnuPlotScripting.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <valarray>

using namespace GnuPlotScripting;

int
main()
{
  global_config().set_log(true);

  const size_t n = 500;
  std::valarray<double> x(n), y(n);

  x[0] = 0;
  std::iota(std::begin(x), std::end(x), 1. / (1. * n));

  std::transform(std::begin(x), std::end(x), std::begin(y), [](auto x_i) {
    return x_i == 0 ? 1 : sin(x_i) / x_i;
  });

  Data_Vector data(x, y);

  Script_File script("sin_x_div_x.gp");

  // CAVEAT: with TeX
  script.free_form("plot {} u 1:2 w l t \"{}\"", data, "$\\frac{\\sin(x)}{x}$");
  script.export_as(PNG().set_free_form("large"), "sin_x_div_x");
}
