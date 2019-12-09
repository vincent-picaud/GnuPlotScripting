#include "GnuPlotScripting/GnuPlotScripting.hpp"

#include <iostream>

using namespace GnuPlotScripting;

int
main()
{
  Script_File script("available_export_format.gp");

  script.free_form("plot sin(x) t 'sin(x)'");

  script.export_as(PNG(), "available_export_format");
  script.export_as(EPSLATEX().set_standalone(true), "available_export_format");
  script.export_as(SVG(), "available_export_format");
}
