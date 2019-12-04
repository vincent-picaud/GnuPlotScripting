#pragma once

#include <filesystem>
#include <memory>
#include <string>

namespace GnuPlotScripting
{
  class Export_As
  {
   public:
    struct Interface
    {
      // NOTE: std::string and not restricted to file as we can use:
      //
      // set term png
      // set output '| display png:-'
      //
      // SEE: http://gnuplot.sourceforge.net/docs_4.2/node409.html
      //
      virtual std::string scripted(const char* const exported_filename_or_pipe) const = 0;

      virtual ~Interface() = default;
    };

   protected:
    using pimpl_type = std::unique_ptr<Interface>;
    pimpl_type _pimpl;

    Export_As(pimpl_type&& pimpl);

   public:
    std::string scripted(const char* const exported_filename_or_pipe) const;
    std::string scripted(const std::string& exported_filename_or_pipe) const;
    std::string scripted(const std::filesystem::path& exported_filename) const;
  };

  class PNG : public Export_As
  {
    struct PNG_Interface;
    PNG_Interface& impl();

   public:
    PNG();

    PNG& set_enhanced(bool yes_no);
    PNG& set_enhanced();  // back to default

    // PNG& set_truecolor(bool yes_no);
    // PNG& set_truecolor();
  };

}
