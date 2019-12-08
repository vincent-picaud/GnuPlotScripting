#include "GnuPlotScripting/GnuPlotScripting.hpp"

#include <iostream>

using namespace GnuPlotScripting;

int
main()
{
  global_config().set_logger(
      [](const char *const msg) { std::cerr << "====> My logger " << msg << std::endl; });
  // If you want to remove logger:  global_config().set_logger();
  // If you want to restore the default one: global_config().set_default_logger();

  // If you want to globally overwrite Script_File_Mode_Enum to Persistent, do:
  global_config().set_script_file_mode(Script_File_Mode_Enum::Persistent);

  for (size_t i = 1; i < 5; i++)
  {
    Script_File script(fmt::format("script_{}.gp", i), Script_File_Mode_Enum::Silent);

    script.free_form("plot sin({0}*x) t 'sin({0}*x)'", i);
  }

  // Now switch back to a regular configuration: stop overwriting
  // local script_file_mode.
  global_config().set_script_file_mode();

  // Now this will silently run scripts
  for (size_t i = 1; i < 5; i++)
  {
    Script_File script(fmt::format("script_{}.gp", i), Script_File_Mode_Enum::Silent);

    script.free_form("plot sin({0}*x) t 'sin({0}*x)'", i);
  }
}
