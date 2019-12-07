#include "GnuPlotScripting/GnuPlotScripting.hpp"

#include <iostream>
#include <vector>

using namespace GnuPlotScripting;

// From: https://www.cs.hmc.edu/~vrable/gnuplot/using-gnuplot.html

int
main()
{
  std::vector<double> time, angle, stdvar;

  time = {0.0,  1.0,  2.1,  3.1,  4.2,  5.2,  6.2,  7.2,  8.2,  9.1,  10.0, 11.0, 12.0,
          12.9, 13.8, 14.9, 15.9, 17.0, 17.9, 18.9, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0,
          26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 32.9, 33.8, 34.7, 35.7, 36.6, 37.7};

  angle = {-14.7, 8.6,  28.8, 46.7, 47.4, 36.5, 37.0, 5.1,  -11.2, -22.4, -35.5, -33.6, -21.1,
           -15.0, -1.6, 19.5, 27.5, 32.6, 27.5, 20.2, 13.8, -1.3,  -24.5, -25.0, -25.0, -20.2,
           -9.9,  5.8,  14.7, 21.8, 29.8, 21.4, 24.6, 25.8, 0.6,   -16.6, -24.0, -24.6, -19.8};

  stdvar = {3.6, 3.6, 3.0, 3.4, 3.5, 3.4, 10.3, 3.4,  3.4, 3.5, 3.6, 3.9, 3.9,
            4.2, 2.7, 3.2, 2.8, 3.5, 2.7, 3.3,  3.4,  4.2, 6.7, 3.3, 3.1, 3.6,
            3.2, 3.2, 3.0, 3.5, 2.7, 4.1, 2.7,  12.0, 2.9, 3.2, 3.7, 3.8, 3.5};

  Script_File script("plot.gp");

  Data_Vector data(
      time, angle, stdvar);  // <- you can stack as many vector/valarray etc.. as you want
                             //    only size() and operator[] are required.

  script.free_form("set title 'Cavendish Data'");
  script.free_form("set xlabel 'Time (s)'");
  script.free_form("set ylabel 'Angle (mrad)'");
  script.free_form("set grid");
  script.free_form("plot {} with yerrorbars notitle", data);
  script.free_form("replot {} u 1:2 with lines title '{}'", data, "raw data");
  script.free_form("theta(t) = theta0 + a * exp(-t / tau) * sin(2 * pi * t / T + phi)");
  script.free_form("fit theta(x) {} using 1:2:3 via a, tau, phi, T, theta0", data);
  script.free_form("replot theta(x) lw {} lc {} title 'best-fit curve'", 2, 4);
  script.export_as(PNG(), "plot");
}
