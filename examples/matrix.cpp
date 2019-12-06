#include "GnuPlotScripting/GnuPlotScripting.hpp"

#include <iostream>

using namespace GnuPlotScripting;

// Example from: https://stackoverflow.com/a/27049991/2001017
// Also see: https://stackoverflow.com/q/32458753/2001017
//
int
main()
{
  Data_Ascii data(
      "0.00 0.65 0.65 0.25\n"
      "0.25 0.00 0.75 0.25\n"
      "0.50 0.60 0.00 0.25\n"
      "0.75 0.25 0.10 0.00\n");

  Script_File script("matrix.gp");

  script.free_form("set autoscale fix");
  script.free_form("set cbrange [-1:1]");
  script.free_form("unset colorbox");
  script.free_form("unset key");
  script.free_form(
      "plot {} matrix using 1:2:3 with image, '' matrix using "
      "1:2:(sprintf('%.2f', $3)) with labels font ',16'",
      data);
  script.export_as(PNG(), "matrix");
  script.export_as(EPSLATEX().set_standalone(true), "matrix");
}
