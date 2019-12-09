#pragma once

#include <filesystem>
#include <memory>
#include <string>

namespace GnuPlotScripting
{
  ///////////////
  // Export_As //
  ///////////////
  //
  class Export_As
  {
   protected:
    struct Interface
    {
      virtual Interface* clone() const = 0;

      virtual std::string export_as(const std::filesystem::path& filename) const = 0;

      virtual ~Interface() = default;
    };

    using pimpl_type = std::unique_ptr<Interface>;
    pimpl_type _pimpl;

    Export_As(pimpl_type&& pimpl);

   public:
    // generates commands, by example:
    //
    // set terminal push
    // set terminal png
    // set output 'filename.png'
    // replot
    // set terminal pop
    //
    std::string export_as(const std::filesystem::path& filename) const;
  };

  /////////
  // PNG //
  /////////
  //
  class PNG : public Export_As
  {
    struct PNG_Interface;
    PNG_Interface& impl();
    const PNG_Interface& impl() const;

   public:
    PNG();
    PNG(const PNG&);
    PNG& operator=(const PNG&);

    PNG& set_free_form(const std::string& free_form = "");

    PNG& set_enhanced(bool yes_no);
    PNG& set_enhanced();  // back to default

    PNG& set_transparent(bool yes_no);
    PNG& set_transparent();  // back to default

    PNG& set_interlace(bool yes_no);
    PNG& set_interlace();  // back to default
  };

  //////////////
  // EPSLATEX //
  //////////////
  //
  class EPSLATEX : public Export_As
  {
    struct EPSLATEX_Interface;
    EPSLATEX_Interface& impl();
    const EPSLATEX_Interface& impl() const;

   public:
    EPSLATEX();
    EPSLATEX(const EPSLATEX&);
    EPSLATEX& operator=(const EPSLATEX&);

    EPSLATEX& set_free_form(const std::string& free_form = "");

    EPSLATEX& set_standalone(bool yes_no);
    EPSLATEX& set_standalone();  // back to default

    EPSLATEX& set_color(bool yes_no);
    EPSLATEX& set_color();  // back to default

    EPSLATEX& set_clip(bool yes_no);
    EPSLATEX& set_clip();  // back to default

    EPSLATEX& set_header(const std::string& header = "");
  };

  /////////
  // SVG //
  /////////
  //
  class SVG : public Export_As
  {
    struct SVG_Interface;
    SVG_Interface& impl();
    const SVG_Interface& impl() const;

   public:
    SVG();
    SVG(const SVG&);
    SVG& operator=(const SVG&);

    SVG& set_free_form(const std::string& free_form = "");

    SVG& set_dynamic();
    SVG& set_fixed();

    SVG& set_solid();
    SVG& set_dashed();

    SVG& set_enhanced(bool yes_no);
    SVG& set_enhanced();  // back to default
  };
  
  //////////
  // TGIF //
  //////////
  //
  // see http://bourbon.usc.edu/tgif/
  //
  class TGIF : public Export_As
  {
    struct TGIF_Interface;
    TGIF_Interface& impl();
    const TGIF_Interface& impl() const;

   public:
    TGIF();
    TGIF(const TGIF&);
    TGIF& operator=(const TGIF&);

    TGIF& set_free_form(const std::string& free_form = "");

    TGIF& set_portrait();
    TGIF& set_landscape();

    TGIF& set_solid();
    TGIF& set_dashed();

    TGIF& set_color(bool yes_no);
    TGIF& set_color();  // back to default
  };

}
