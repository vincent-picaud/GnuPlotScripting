#include "GnuPlotScripting/GnuPlotScripting.hpp"
#include "GnuPlotScripting/data_supervised.hpp"

#include <array>
#include <iostream>

using namespace GnuPlotScripting;

std::array<double, 10> X_1 = {0.1, 0.3, 0.1, 0.6, 0.4, 0.6, 0.5, 0.9, 0.4, 0.7};
std::array<double, 10> X_2 = {0.1, 0.4, 0.5, 0.9, 0.2, 0.3, 0.6, 0.2, 0.4, 0.6};
std::array<int, 10> Y      = {1, 1, 1, 1, 1, 0, 0, 0, 0, 0};

int
main()
{
  Data_Supervised data(Y, X_1, X_2);

  Script_File script("density_plot.gp");

  script.free_form("set pm3d map");
  script.free_form("set palette model RGB defined ( 0 'gray80', 1 'white' )");
  script.free_form("set contour base");
  script.free_form("set cntrparam levels discrete 0.5");
  script.free_form("unset colorbox");  // no palette

  // CAVEAT: for contour use pm3d and not image
  script.free_form("splot 'density_plot_data.txt' u ($1/60):($2/60):3 matrix with pm3d lw 2");

  for (size_t i = 0; i < 2; i++)
  {
    // CAVEAT: to prevent
    //         <<warning: Cannot contour non grid data. Please use "set dgrid3d">>
    //         do not forget "nocontour"
    script.free_form(
        "replot {0} index {1} u 1:2:3 with points pt '{1}' ps 2 notitle nocontour", data, i);
  }

  return EXIT_SUCCESS;
}
