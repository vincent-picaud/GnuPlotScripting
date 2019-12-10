#pragma once

#include "GnuPlotScripting/data.hpp"
#include "GnuPlotScripting/export_as.hpp"
#include "GnuPlotScripting/global_config.hpp"
#include "GnuPlotScripting/script_pipe_mode_enum.hpp"

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
    void flush();

    template <typename... ARGS>
    Script&
    free_form(ARGS&&... args)
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

      return *this;
    }

    // NOTE: automatically sets the right filename extension
    Script& export_as(const Export_As& export_as, const std::filesystem::path& output);
  };

  /////////////////
  // Script_File //
  /////////////////
  //
  // Writes script in a file
  //
  class Script_File final : public Script
  {
   public:
    Script_File(const std::filesystem::path& filename,
                Script_File_Mode_Enum script_file_mode = Script_File_Mode_Enum::Persistent);
  };

  /////////////////
  // Script_Pipe //
  /////////////////
  //
  // Writes script in a pipe
  //
  class Script_Pipe final : public Script
  {
   public:
    Script_Pipe(Script_Pipe_Mode_Enum script_pipe_mode = Script_Pipe_Mode_Enum::Persistent);
  };

}  // namespace GnuPlotScripting
