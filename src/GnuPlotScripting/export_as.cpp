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
          "set terminal pop\n",
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
    free_form(const std::string& option)
    {
      if (not option.empty())
      {
        return option + " ";
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
    clip(const std::optional<bool>& option)
    {
      if (option.has_value())
      {
        if (*option)
        {
          return "clip ";
        }
        else
        {
          return "noclip ";
        }
      }
      return "";
    }

    std::string
    standalone(const std::optional<bool>& option)
    {
      if (option.has_value())
      {
        if (*option)
        {
          return "standalone ";
        }
        else
        {
          return "input ";
        }
      }
      return "";
    }

    std::string
    color(const std::optional<bool>& option)
    {
      if (option.has_value())
      {
        if (*option)
        {
          return "color ";
        }
        else
        {
          return "monochrome ";
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

    std::string
    header(const std::optional<std::string>& option)
    {
      if (option.has_value())
      {
        return "header \"" + *option + "\" ";
      }
      else
      {
        return "noheader ";
      }
    }
  }

  /////////
  // PNG //
  /////////
  //
  struct PNG::PNG_Interface final : public Export_As::Interface
  {
    std::string _free_form;
    std::optional<bool> _enhanced;
    std::optional<bool> _transparent;
    std::optional<bool> _interlace;

    PNG::PNG_Interface*
    clone() const
    {
      return new PNG::PNG_Interface(*this);
    };

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
  const PNG::PNG_Interface&
  PNG::impl() const
  {
    assert(dynamic_cast<PNG_Interface*>(_pimpl.get()));

    return static_cast<PNG_Interface&>(*_pimpl.get());
  }

  PNG::PNG() : Export_As{std::make_unique<PNG_Interface>()} {}

  PNG::PNG(const PNG& to_copy) : Export_As{pimpl_type(to_copy.impl().clone())} {}
  PNG&
  PNG::operator=(const PNG& to_copy)
  {
    _pimpl = pimpl_type(to_copy.impl().clone());
    return *this;
  }

  PNG&
  PNG::set_free_form(const std::string& free_form)
  {
    impl()._free_form = free_form;

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

  /////////
  // EPSLATEX //
  /////////
  //
  struct EPSLATEX::EPSLATEX_Interface final : public Export_As::Interface
  {
    std::string _free_form;
    std::optional<bool> _standalone;
    std::optional<bool> _color;
    std::optional<bool> _clip;
    std::string _header;

    EPSLATEX::EPSLATEX_Interface*
    clone() const
    {
      return new EPSLATEX::EPSLATEX_Interface(*this);
    };

    std::string
    export_as(const std::filesystem::path& filename) const
    {
      std::string options = (free_form(_free_form) + standalone(_standalone) + color(_color) +
                             clip(_clip) + header(_header));

      return scripting_helper("epslatex", ".tex", filename, options);
    }
  };

  EPSLATEX::EPSLATEX_Interface&
  EPSLATEX::impl()
  {
    assert(dynamic_cast<EPSLATEX_Interface*>(_pimpl.get()));

    return static_cast<EPSLATEX_Interface&>(*_pimpl.get());
  }
  const EPSLATEX::EPSLATEX_Interface&
  EPSLATEX::impl() const
  {
    assert(dynamic_cast<EPSLATEX_Interface*>(_pimpl.get()));

    return static_cast<EPSLATEX_Interface&>(*_pimpl.get());
  }

  EPSLATEX::EPSLATEX() : Export_As{std::make_unique<EPSLATEX_Interface>()} {}

  EPSLATEX::EPSLATEX(const EPSLATEX& to_copy) : Export_As{pimpl_type(to_copy.impl().clone())} {}
  EPSLATEX&
  EPSLATEX::operator=(const EPSLATEX& to_copy)
  {
    _pimpl = pimpl_type(to_copy.impl().clone());
    return *this;
  }

  EPSLATEX&
  EPSLATEX::set_free_form(const std::string& free_form)
  {
    impl()._free_form = free_form;

    return *this;
  }

  EPSLATEX&
  EPSLATEX::set_standalone(bool yes_no)
  {
    impl()._standalone = yes_no;

    return *this;
  }
  EPSLATEX&
  EPSLATEX::set_standalone()
  {
    impl()._standalone.reset();

    return *this;
  }

  EPSLATEX&
  EPSLATEX::set_color(bool yes_no)
  {
    impl()._color = yes_no;

    return *this;
  }
  EPSLATEX&
  EPSLATEX::set_color()
  {
    impl()._color.reset();

    return *this;
  }

  EPSLATEX&
  EPSLATEX::set_clip(bool yes_no)
  {
    impl()._clip = yes_no;

    return *this;
  }
  EPSLATEX&
  EPSLATEX::set_clip()
  {
    impl()._clip.reset();

    return *this;
  }
  EPSLATEX&
  EPSLATEX::set_header(const std::string& header)
  {
    impl()._header = header;

    return *this;
  }
}
