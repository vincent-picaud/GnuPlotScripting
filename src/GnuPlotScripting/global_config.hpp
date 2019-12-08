#pragma once

#include "GnuPlotScripting/script_file_mode_enum.hpp"

#include <functional>
#include <memory>
#include <optional>

namespace GnuPlotScripting
{
  class Global_Config;

  Global_Config& global_config();

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
    const char* gnuplot_exe() const;
    Global_Config& set_gnuplot_exe(const char* const gnuplot_executable);

    Global_Config& set_log();
    Global_Config& set_log(const std::function<void(const char* const msg)>& f);

    bool log() const;
    Global_Config& set_log_message(const char* const msg);

    Global_Config& set_script_file_mode(Script_File_Mode_Enum mode);
    Global_Config& set_script_file_mode();  // reset to default
    std::optional<Script_File_Mode_Enum> script_file_mode() const;
  };

}
