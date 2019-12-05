
#include "GnuPlotScripting/GnuPlotScripting.hpp"

#include <iostream>

using namespace GnuPlotScripting;

// Example from: https://stackoverflow.com/questions/27045964/multiple-palettes-and-empty-labels-from-file-entries-using-matrix-with-image-in/27049991#27049991
// Another matrix example: https://stackoverflow.com/questions/32458753/gnuplot-2d-plot-of-a-matrix-of-data
int
main()
{
  Data_Ascii data(
      "-1 -1 0    # A\n"
      "-1  1 0    # B\n"
      " 1  0 0    # C\n"
      " 0  0 1.75 # D\n"
      "\n\n"
      "-1 -1 0   -1 1 0     \n"
      "-1 -1 0    1 0 0     \n"
      "-1 -1 0    0 0 1.750 \n"
      "-1  1 0    1 0 0     \n"
      "-1  1 0    0 0 1.75  \n"
      " 1  0 0    0 0 1.75  \n");

  Script_File script_a("graph_3D.gp");

  script_a.free_form("unset border");
  script_a.free_form("unset tics");
  script_a.free_form("unset key");
  script_a.free_form("set view 75,35");
  script_a.free_form("splot {} index 0 with points pointtype 7 pointsize 3", data);
  script_a.free_form("replot {} index 1 u 1:2:3:($4-$1):($5-$2):($6-$3) with vectors nohead", data);
  script_a.free_form("pause -1");

   Script_File script_b("graph_2D.gp");

  script_b.free_form("unset border");
  script_b.free_form("unset tics");
  script_b.free_form("unset key");
  script_b.free_form("plot {} index 0 with points pointtype 7 pointsize 3", data);
  script_b.free_form("replot {} index 1 u 1:2:($4-$1):($5-$2) with vectors nohead", data);
  script_b.free_form("pause -1");
}
