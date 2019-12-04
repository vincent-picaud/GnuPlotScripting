#pragma once

#include "GnuPlotScripting/data.hpp"
#include "GnuPlotScripting/export_as.hpp"

#include "fmt/format.h"

#include <filesystem>
#include <memory>
#include <set>
#include <string>

namespace GnuPlotScripting
{
  class Script
  {
   public:
    class Interface
    {
      std::set<std::string> _uuid_set;

     public:
      Interface()          = default;
      virtual ~Interface() = default;

      virtual void write(const std::string&) = 0;
      virtual void flush()                   = 0;

      virtual void writeln(const std::string&) final;
      virtual void write(const Data&) final;
    };

   protected:
    using pimpl_type = std::unique_ptr<Interface>;
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
    void
    fmt_free_form(ARGS&&... args)
    {
      auto register_data_if_any = [this](const auto& arg) {
        using arg_type = std::decay_t<decltype(arg)>;
        if constexpr (std::is_base_of_v<Data, arg_type>)
        {
          this->_pimpl->write(arg);
        }
      };
      (register_data_if_any(args), ...);

      _pimpl->writeln(fmt::format(std::forward<ARGS>(args)...));
    }

    void export_as(const Export_As& export_as, const char* const output);
    void export_as(const Export_As& export_as, const std::string& output);
  };

  /////////////////
  // Script_File //
  /////////////////
  //
  // Write script in a file
  //
  class Script_File final : public Script
  {
   public:
    Script_File(const std::filesystem::path& filename);
  };

}  // namespace GnuPlotScripting
