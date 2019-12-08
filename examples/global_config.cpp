#include "GnuPlotScripting/GnuPlotScripting.hpp"

#include <iostream>

using namespace GnuPlotScripting;

void
this_is_my_logger(const char *const msg)
{
  std::cerr << "============> My logger " << msg << std::endl;
}

int
main()
{
  global_config().set_log(this_is_my_logger);
  // If you want to remove logger:  global_config().set_log();

  // If you want to globally overwrite Script_File_Mode_Enum::Silent do:
  global_config().set_script_file_mode(Script_File_Mode_Enum::Persistent);
  // comment me to switch back to the locally defined mode (here Silent)

  for (size_t i = 0; i < 5; i++)
  {
    Script_File script(fmt::format("script_{}.gp", i), Script_File_Mode_Enum::Silent);

    script.free_form("plot sin({0}*x) t 'sin({0}*x)'", i);
  }
}
