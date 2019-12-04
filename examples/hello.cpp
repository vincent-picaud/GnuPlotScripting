#include "GnuPlotScripting/data_vector.hpp"
#include "GnuPlotScripting/script.hpp"

#include <iostream>
#include <type_traits>
#include <valarray>

using namespace GnuPlotScripting;

int
main()
{
  std::vector<double> v1(10, 5);
  std::valarray<int> v2(10);
  std::string v3("01234567891");
  Data_Vector data(v1, v2, v3);

  Script_File script("script.gp");

  script.free_form("plot sin(x) t \"super\"");
  script.free_form("replot {} w l t \"ca marche?\"", data);
  script.free_form("replot {} u ($1)+2 w l lw 3 t \"oui!?\"", data);
}
