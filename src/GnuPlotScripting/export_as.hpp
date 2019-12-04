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
      virtual std::string export_as(const std::filesystem::path& filename) const = 0;

      virtual ~Interface() = default;
    };

   protected:
    using pimpl_type = std::unique_ptr<Interface>;
    pimpl_type _pimpl;

    Export_As(pimpl_type&& pimpl);

   public:
    std::string export_as(const std::filesystem::path& filename) const;
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
