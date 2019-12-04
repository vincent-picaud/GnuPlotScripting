
#include "GnuPlotScripting/data_vector.hpp"
#include "GnuPlotScripting/global_config.hpp"
#include "GnuPlotScripting/script.hpp"

#include <iostream>
#include <type_traits>
#include <valarray>

using namespace GnuPlotScripting;

int
main()
{
  global_config().set_log(true);

  std::vector<double> v1(10, 5);
  std::valarray<int> v2(10);
  std::string v3("0123456789");
  Data_Vector data(v1, v2, v3);

  Script_File script("script.gp");

  script.fmt_free_form("plot sin(x) t \"super\"");
  script.fmt_free_form("replot {} w l t \"ca marche?\"", data);
  script.fmt_free_form("replot {} u ($1)+2 w l lw 3 t \"oui!?\"", data);
  script.export_as(Export_As_PNG().set_color(false), "test.png");
  script.export_as(Export_As_PNG().set_color(false), fmt::format("{}.png", "test2"));
}
