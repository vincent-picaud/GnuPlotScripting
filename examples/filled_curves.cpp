#include "GnuPlotScripting/GnuPlotScripting.hpp"

using namespace GnuPlotScripting;

int
main()
{
  Script_File script("filled_curve.gp", Script_File_Mode_Enum::Persistent);

  script.set_title("Some sqrt stripes on filled graph background")
      .free_form(
          "plot [0:10] [-8:6] "
          "-8 with filledcurve x2 lt 15, "
          "sqrt(x) with filledcurves y1=-0.5, "
          "sqrt(10-x)-4.5 with filledcurves y1=-5.5");
}
