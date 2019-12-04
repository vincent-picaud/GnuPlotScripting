#pragma once

#include <memory>

namespace GnuPlotScripting
{
  class Global_Config;

  Global_Config& global_config();

  enum class Script_File_Mode_Enum
  {
    None,       // never automatically run generated file scripts
    Silent,     // silently run generated file scripts
    Persistent  // run generated file scripts using persistent mode GnuPlot
  };

  class Global_Config
  {
   protected:
    struct Interface;
    using pimpl_type = std::unique_ptr<Interface>;
    pimpl_type _pimpl;

    friend Global_Config& global_config();

    Global_Config();
    ~Global_Config();

    Global_Config(const Global_Config&) = delete;
    Global_Config(Global_Config&&)      = delete;
    Global_Config& operator=(const Global_Config&) = delete;
    Global_Config& operator=(Global_Config&&) = delete;

   public:
    // action logging
    Global_Config& set_log(bool on_off);
    bool log() const;
    Global_Config& set_log_message(const char* const msg);

    // run file scripts
    Global_Config& set_file_script_mode(Script_File_Mode_Enum mode);
    Script_File_Mode_Enum file_script_mode() const;
  };

}
