#include "GnuPlotScripting/export_as.hpp"
#include "GnuPlotScripting/global_config.hpp"

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

      if (global_config().has_logger())
      {
        global_config().set_log_message(fmt::format("Exporting: {}", filename_ext.c_str()).c_str());
      }

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
    boolean_option(const std::optional<bool>& option,
                   const char* const form_true,
                   const char* const form_false,
                   const char* const form_undef = "")
    {
      if (option.has_value())
      {
        if (*option)
        {
          return form_true;
        }
        else
        {
          return form_false;
        }
      }
      return form_undef;
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

#define SETTER(CLASS, KEYWORD)             \
  CLASS& CLASS::set_##KEYWORD(bool yes_no) \
  {                                        \
    impl()._##KEYWORD = yes_no;            \
                                           \
    return *this;                          \
  }                                        \
  CLASS& CLASS::set_##KEYWORD()            \
  {                                        \
    impl()._##KEYWORD.reset();             \
                                           \
    return *this;                          \
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
      std::string options =
          (free_form(_free_form) + boolean_option(_enhanced, "enhanced ", "noenhanced ") +
           boolean_option(_transparent, "transparent ", "notransparent ") +
           boolean_option(_interlace, "interlace ", "nointerlace "));

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

  SETTER(PNG, enhanced);
  SETTER(PNG, transparent);
  SETTER(PNG, interlace);

  //////////////
  // EPSLATEX //
  //////////////
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
      std::string options =
          (free_form(_free_form) + boolean_option(_standalone, "standalone ", "input ") +
           boolean_option(_color, "color ", "monochrome ") +
           boolean_option(_clip, "clip ", "noclip ") + header(_header));

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

  SETTER(EPSLATEX, standalone);
  SETTER(EPSLATEX, color);
  SETTER(EPSLATEX, clip);

  EPSLATEX&
  EPSLATEX::set_header(const std::string& header)
  {
    impl()._header = header;

    return *this;
  }

  /////////
  // SVG //
  /////////
  //
  struct SVG::SVG_Interface final : public Export_As::Interface
  {
    std::string _free_form;
    std::optional<bool> _t_dynamic_f_fixed;
    std::optional<bool> _t_solid_f_dashed;
    std::optional<bool> _enhanced;

    SVG::SVG_Interface*
    clone() const
    {
      return new SVG::SVG_Interface(*this);
    };

    std::string
    export_as(const std::filesystem::path& filename) const
    {
      std::string options =
          (free_form(_free_form) + boolean_option(_t_dynamic_f_fixed, "dynamic ", "fixed ") +
           boolean_option(_t_solid_f_dashed, "solid ", "dashed ") +
           boolean_option(_enhanced, "enhanced ", "noenhanced "));

      return scripting_helper("svg", filename, options);
    }
  };

  SVG::SVG_Interface&
  SVG::impl()
  {
    assert(dynamic_cast<SVG_Interface*>(_pimpl.get()));

    return static_cast<SVG_Interface&>(*_pimpl.get());
  }
  const SVG::SVG_Interface&
  SVG::impl() const
  {
    assert(dynamic_cast<SVG_Interface*>(_pimpl.get()));

    return static_cast<SVG_Interface&>(*_pimpl.get());
  }

  SVG::SVG() : Export_As{std::make_unique<SVG_Interface>()} {}

  SVG::SVG(const SVG& to_copy) : Export_As{pimpl_type(to_copy.impl().clone())} {}
  SVG&
  SVG::operator=(const SVG& to_copy)
  {
    _pimpl = pimpl_type(to_copy.impl().clone());
    return *this;
  }

  SVG&
  SVG::set_free_form(const std::string& free_form)
  {
    impl()._free_form = free_form;

    return *this;
  }
  SVG&
  SVG::set_dynamic()
  {
    impl()._t_dynamic_f_fixed = true;
    return *this;
  }
  SVG&
  SVG::set_fixed()
  {
    impl()._t_dynamic_f_fixed = false;
    return *this;
  }

  SVG&
  SVG::set_solid()
  {
    impl()._t_solid_f_dashed = true;
    return *this;
  }
  SVG&
  SVG::set_dashed()
  {
    impl()._t_solid_f_dashed = false;
    return *this;
  }

  SETTER(SVG, enhanced);

  //////////
  // TGIF //
  //////////
  //
  struct TGIF::TGIF_Interface final : public Export_As::Interface
  {
    std::string _free_form;
    std::optional<bool> _t_portrait_f_landscape;
    std::optional<bool> _t_solid_f_dashed;
    std::optional<bool> _color;

    TGIF::TGIF_Interface*
    clone() const
    {
      return new TGIF::TGIF_Interface(*this);
    };

    std::string
    export_as(const std::filesystem::path& filename) const
    {
      std::string options = (free_form(_free_form) +
                             boolean_option(_t_portrait_f_landscape, "portrait ", "landscape ") +
                             boolean_option(_t_solid_f_dashed, "solid ", "dashed ") +
                             boolean_option(_color, "color ", "monochrome "));

      return scripting_helper("tgif", "obj", filename, options);
    }
  };

  TGIF::TGIF_Interface&
  TGIF::impl()
  {
    assert(dynamic_cast<TGIF_Interface*>(_pimpl.get()));

    return static_cast<TGIF_Interface&>(*_pimpl.get());
  }
  const TGIF::TGIF_Interface&
  TGIF::impl() const
  {
    assert(dynamic_cast<TGIF_Interface*>(_pimpl.get()));

    return static_cast<TGIF_Interface&>(*_pimpl.get());
  }

  TGIF::TGIF() : Export_As{std::make_unique<TGIF_Interface>()} {}

  TGIF::TGIF(const TGIF& to_copy) : Export_As{pimpl_type(to_copy.impl().clone())} {}
  TGIF&
  TGIF::operator=(const TGIF& to_copy)
  {
    _pimpl = pimpl_type(to_copy.impl().clone());
    return *this;
  }

  TGIF&
  TGIF::set_free_form(const std::string& free_form)
  {
    impl()._free_form = free_form;

    return *this;
  }
  TGIF&
  TGIF::set_portrait()
  {
    impl()._t_portrait_f_landscape = true;
    return *this;
  }
  TGIF&
  TGIF::set_landscape()
  {
    impl()._t_portrait_f_landscape = false;
    return *this;
  }

  TGIF&
  TGIF::set_solid()
  {
    impl()._t_solid_f_dashed = true;
    return *this;
  }
  TGIF&
  TGIF::set_dashed()
  {
    impl()._t_solid_f_dashed = false;
    return *this;
  }

  SETTER(TGIF, color);

}
