#include "GnuPlotScripting/global_config.hpp"

#include <cassert>
#include <iostream>

namespace GnuPlotScripting
{
  namespace
  {
    void
    default_logger(const char* const msg)
    {
      std::cerr << "[GnuPlotScripting] " << msg << std::endl;
    }
  }

  struct Global_Config::Interface
  {
    void (*_f)(const char* const msg) = default_logger;
    std::optional<Script_File_Mode_Enum> _script_file_mode{};
    std::string _gnuplot_exe
#if defined(WIN32)
        = "gnuplot.exe";
#else
        = "gnuplot";
#endif
  };

  Global_Config::Global_Config() : _pimpl(std::make_unique<Interface>()) {}
  Global_Config::~Global_Config() {}
  const char*
  Global_Config::gnuplot_exe() const
  {
    return _pimpl->_gnuplot_exe.c_str();
  }
  Global_Config&
  Global_Config::set_gnuplot_exe(const char* const gnuplot_executable)
  {
    _pimpl->_gnuplot_exe = gnuplot_executable;
    return *this;
  }

  Global_Config&
  Global_Config::set_log(void (*f)(const char* const msg))
  {
    _pimpl->_f = f;
    return *this;
  }
  bool
  Global_Config::log() const
  {
    return (_pimpl->_f != nullptr);
  }
  Global_Config&
  Global_Config::set_log_message(const char* const msg)
  {
    if (log())
    {
      _pimpl->_f(msg);
    }
    return *this;
  }

  Global_Config&
  Global_Config::set_script_file_mode(Script_File_Mode_Enum mode)
  {
    _pimpl->_script_file_mode = mode;
    return *this;
  }
  Global_Config&
  Global_Config::set_script_file_mode()
  {
    _pimpl->_script_file_mode.reset();
    return *this;
  }

  std::optional<Script_File_Mode_Enum>
  Global_Config::script_file_mode() const
  {
    return _pimpl->_script_file_mode;
  }

  ////////////////////////////////////////////////////////////////

  Global_Config&
  global_config()
  {
    static Global_Config config;
    return config;
  }
}
