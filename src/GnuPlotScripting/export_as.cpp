#include "GnuPlotScripting/export_as.hpp"

#include <fmt/format.h>

#include <cassert>
#include <optional>

namespace GnuPlotScripting
{
  Export_As::Export_As(pimpl_type&& pimpl) : _pimpl(std::move(pimpl)) { assert(_pimpl); }

  std::string
  Export_As::export_as(const std::filesystem::path& filename) const
  {
    return _pimpl->export_as(filename);
  }

  //////////////////
  // Some helpers //
  //////////////////
  //
  namespace
  {
    std::filesystem::path
    change_filename_extension(const std::filesystem::path& filename,
                              const std::string& new_extension)
    {
      std::string filename_no_ext_as_string = filename.stem();

      if (new_extension.empty())
      {
        return filename_no_ext_as_string;
      }

      if (new_extension.front() != '.') filename_no_ext_as_string += '.';

      filename_no_ext_as_string += new_extension;

      return filename_no_ext_as_string;
    }

    std::string
    scripting_helper(const std::string& terminal,
                     const std::string& extension,
                     const std::filesystem::path& filename,
                     const std::string& options)
    {
      std::filesystem::path filename_ext = change_filename_extension(filename, extension);

      return fmt::format(
          "set terminal push\n"
          "set terminal {} {}\n"
          "set output '{}'\n"
          "replot\n"
          "set terminal pop\n"
          "replot\n",
          terminal,
          options,
          filename_ext.native());
    }
    std::string
    scripting_helper(const std::string& terminal,
                     const std::filesystem::path& filename,
                     const std::string& options)
    {
      return scripting_helper(terminal, terminal, filename, options);
    }

    //////////////// Common Options ////////////////
    //
    std::string
    free_form(const std::optional<std::string>& option)
    {
      if (option.has_value())
      {
        return (*option) + " ";
      }
      return "";
    }

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

    std::string
    transparent(const std::optional<bool>& option)
    {
      if (option.has_value())
      {
        if (*option)
        {
          return "transparent ";
        }
        else
        {
          return "notransparent ";
        }
      }
      return "";
    }

    std::string
    interlace(const std::optional<bool>& option)
    {
      if (option.has_value())
      {
        if (*option)
        {
          return "interlace ";
        }
        else
        {
          return "nointerlace ";
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
    std::optional<std::string> _free_form;
    std::optional<bool> _enhanced;
    std::optional<bool> _transparent;
    std::optional<bool> _interlace;

    std::string
    export_as(const std::filesystem::path& filename) const
    {
      std::string options = (free_form(_free_form) + enhanced(_enhanced) +
                             transparent(_transparent) + interlace(_interlace));

      return scripting_helper("png", filename, options);
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
  PNG::set_free_form(const std::string& free_form)
  {
    impl()._free_form = free_form;

    return *this;
  }
  PNG&
  PNG::set_free_form()
  {
    impl()._free_form.reset();

    return *this;
  }

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

  PNG&
  PNG::set_transparent(bool yes_no)
  {
    impl()._transparent = yes_no;

    return *this;
  }
  PNG&
  PNG::set_transparent()
  {
    impl()._transparent.reset();

    return *this;
  }

  PNG&
  PNG::set_interlace(bool yes_no)
  {
    impl()._interlace = yes_no;

    return *this;
  }
  PNG&
  PNG::set_interlace()
  {
    impl()._interlace.reset();

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
