#pragma once

namespace GnuPlotScripting
{
  enum class Script_File_Mode_Enum
  {
    None,       // never automatically run generated file scripts
    Silent,     // silently run generated file scripts
    Persistent  // run generated file scripts using persistent mode GnuPlot
  };

}
