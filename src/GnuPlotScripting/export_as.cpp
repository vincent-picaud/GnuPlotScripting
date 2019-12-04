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
                     const char* const filename_or_pipe,
                     const std::string& options)
    {
      return fmt::format(
          "set terminal push\n"
          "set terminal {} {}\n"
          "set output '{}'\n"
          "replot\n"
          "set terminal pop\n"
          "replot\n",
          terminal,
          options,
          filename_or_pipe);
    }

  }

  /////////////////////////////////////
  // Some helpers for common options //
  /////////////////////////////////////
  //
  namespace
  {
    std::string
    enhanced(const std::optional<bool>& option)
    {
      if (option.has_value())
      {
        if (*option)
        {
          return "enhanced ";
        }
        else
        {
          return "noenhanced ";
        }
      }
      return "";
    }
  }

  ///////////////////
  // Export_As_PNG //
  ///////////////////
  //
  struct PNG::PNG_Interface final : public Export_As::Interface
  {
    std::string _free_options;
    std::optional<bool> _enhanced;

    std::string
    scripted(const char* const filename_or_pipe) const
    {
      std::string options = (enhanced(_enhanced));

      return scripting_helper("png", filename_or_pipe, options);
    }
  };

  PNG::PNG_Interface&
  PNG::impl()
  {
    assert(dynamic_cast<PNG_Interface*>(_pimpl.get()));

    return static_cast<PNG_Interface&>(*_pimpl.get());
  }

  PNG::PNG() : Export_As{std::make_unique<PNG_Interface>()} {}

  PNG&
  PNG::set_enhanced(bool yes_no)
  {
    impl()._enhanced = yes_no;

    return *this;
  }
  PNG&
  PNG::set_enhanced()
  {
    impl()._enhanced.reset();

    return *this;
  }

  // PNG&
  // PNG::set_color(bool yes_no)
  // {
  //   assert(dynamic_cast<PNG_Interface*>(_pimpl.get()));

  //   static_cast<PNG_Interface&>(*_pimpl.get()).color = yes_no;

  //   return *this;
  // }
}
