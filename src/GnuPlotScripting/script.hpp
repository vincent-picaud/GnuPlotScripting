#pragma once

#include "fmt/format.h"

#include <filesystem>
#include <memory>
#include <string>

namespace GnuPlotScripting
{

  class Script
  {
   public:
    struct Implementation
    {
      virtual void write(const std::string&) = 0;
      virtual void writeln(const std::string&) = 0;
      virtual void flush() = 0;
      virtual ~Implementation() = default;
    };

   protected:
    using pimpl_type = std::unique_ptr<Implementation>;
    pimpl_type _pimpl;

    //////////////// Constructors ////////////////
    //
   protected:
    Script(pimpl_type&& pimpl);
    ~Script();

    //////////////// Methods ////////////////
    //
   public:
    template <typename... ARGS>
    void free_form(ARGS&&... args)
    {
      _pimpl->writeln(fmt::format(std::forward<ARGS>(args)...));
    }
  };

  class Script_File final : public Script
  {
   public:
    Script_File(const std::filesystem::path& out);
  };

}  // namespace GnuPlotScripting
