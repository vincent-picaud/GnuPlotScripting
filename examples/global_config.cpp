#include "GnuPlotScripting/GnuPlotScripting.hpp"

#include <iostream>

using namespace GnuPlotScripting;

int
main()
{
  global_config().set_log(
      [](const char *const msg) { std::cerr << "============> My logger " << msg << std::endl; });
  // If you want to remove logger:  global_config().set_log();

  // If you want to globally overwrite Script_File_Mode_Enum::Silent do:
  global_config().set_script_file_mode(Script_File_Mode_Enum::Persistent);

  for (size_t i = 1; i < 5; i++)
  {
    Script_File script(fmt::format("script_{}.gp", i), Script_File_Mode_Enum::Silent);

    script.free_form("plot sin({0}*x) t 'sin({0}*x)'", i);
  }
}
