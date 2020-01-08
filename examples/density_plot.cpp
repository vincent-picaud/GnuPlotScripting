#include "GnuPlotScripting/GnuPlotScripting.hpp"

#include <array>

using namespace GnuPlotScripting;

// std::array<std::pair<double,int  TinyMatrix<double, 10, 2> X;
//   X[0] = std::array{0.1, 0.1};
//   X[1] = std::array{0.3, 0.4};
//   X[2] = std::array{0.1, 0.5};
//   X[3] = std::array{0.6, 0.9};
//   X[4] = std::array{0.4, 0.2};
//   X[5] = std::array{0.6, 0.3};
//   X[6] = std::array{0.5, 0.6};
//   X[7] = std::array{0.9, 0.2};
//   X[8] = std::array{0.4, 0.4};
//   X[9] = std::array{0.7, 0.6};

//   TinyMatrix<double, 10, 2> Y;
//   Y[0] = std::array{1., 0.};
//   Y[1] = std::array{1., 0.};
//   Y[2] = std::array{1., 0.};
//   Y[3] = std::array{1., 0.};
//   Y[4] = std::array{1., 0.};
//   Y[5] = std::array{0., 1.};
//   Y[6] = std::array{0., 1.};
//   Y[7] = std::array{0., 1.};
//   Y[8] = std::array{0., 1.};
//   Y[9] = std::array{0., 1.};

std::array<std::array<double, 2>, 10> X{std::array{0.1, 0.1},
                                        std::array{0.3, 0.4},
                                        std::array{0.1, 0.5},
                                        std::array{0.6, 0.9},
                                        std::array{0.4, 0.2},
                                        std::array{0.6, 0.3},
                                        std::array{0.5, 0.6},
                                        std::array{0.9, 0.2},
                                        std::array{0.4, 0.4},
                                        std::array{0.7, 0.6}};

std::array<double, 10> X_1 = {0.1, 0.3, 0.1, 0.6, 0.4, 0.6, 0.5, 0.9, 0.4, 0.7};
std::array<double, 10> X_2 = {0.1, 0.3, 0.1, 0.6, 0.4, 0.6, 0.5, 0.9, 0.4, 0.7};

int
main()
{
  Data_Ascii data(
      "0.00 0.65 0.65 0.25\n"
      "0.25 0.00 0.75 0.25\n"
      "0.50 0.60 0.00 0.25\n"
      "0.75 0.25 0.10 0.00\n");

  Script_File script("density_plot.gp");

  script.free_form("set pm3d map");

//   for (const auto& X_i : X)
//   {
//     set style line 1 lc rgb 'black' pt 5   # square
// set style line 2 lc rgb 'black' pt 7   # circle
// set style line 3 lc rgb 'black' pt 9   # triangle
      
//     pipe.free_form("{} {}", data_i.first, data_i.second);
//     plot '-' w p ls 1
//   }

  script.free_form("splot 'density_plot_data.txt' u 1:2:3 matrix with pm3d");

  return EXIT_SUCCESS;
}
