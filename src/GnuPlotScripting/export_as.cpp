#include "GnuPlotScripting/export_as.hpp"

#include <fmt/format.h>

#include <cassert>

namespace GnuPlotScripting
{
  Export_As::Export_As(pimpl_type&& pimpl) : _pimpl(std::move(pimpl)) { assert(_pimpl); }

  std::string
  Export_As::scripted(const char* const exported_filename_or_pipe) const
  {
    return _pimpl->scripted(exported_filename_or_pipe);
  }

  std::string
  Export_As::scripted(const std::string& exported_filename_or_pipe) const
  {
    return scripted(exported_filename_or_pipe.c_str());
  }
  std::string
  Export_As::scripted(const std::filesystem::path& exported_filename) const
  {
    return scripted(exported_filename.c_str());
  }

  namespace
  {
    std::string
    scripting_helper(const std::string& terminal,
                     const std::string& options,
                     const char* const filename_or_pipe)
    {
      return fmt::format(
          "set terminal push\n"
          "set terminal {}\n"
          "set output '{}' {}\n"
          "replot\n"
          "set terminal pop\n"
          "replot\n",
          terminal,
          options,
          filename_or_pipe);
    }

  }

  ///////////////////
  // Export_As_PNG //
  ///////////////////
  //
  namespace
  {
    struct Export_As_PNG_Interface final : public Export_As::Interface
    {
      bool color = true;

      std::string
      scripted(const char* const filename_or_pipe) const
      {
        return scripting_helper("png", fmt::format("color {}", color), filename_or_pipe);
      }
    };
  }

  Export_As_PNG::Export_As_PNG() : Export_As{std::make_unique<Export_As_PNG_Interface>()} {}

  Export_As_PNG&
  Export_As_PNG::set_color(bool yes_no)
  {
    assert(dynamic_cast<Export_As_PNG_Interface*>(_pimpl.get()));

    static_cast<Export_As_PNG_Interface&>(*_pimpl.get()).color = yes_no;

    return *this;
  }
}
