#pragma once

#include "GnuPlotScripting/data.hpp"

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
    }

    // template <typename... ARGS>
    // void plot(const Data& d,ARGS&&... args)
    // {
    //   pimpl->write(data);
    //   pimpl->write(
    // }
  };

  class Script_File final : public Script
  {
   public:
    Script_File(const std::filesystem::path& out);
  };

}  // namespace GnuPlotScripting
