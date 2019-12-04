#include "GnuPlotScripting/script.hpp"
#include "GnuPlotScripting/global_config.hpp"

#include <fstream>
#include <iostream>
#include <set>

namespace GnuPlotScripting
{
  ////////////
  // Script //
  ////////////

  //////////////// Script::Interface ////////////////
  //
  void
  Script::Interface::writeln(const std::string& s)
  {
    write(s);
    write("\n");
  };

  void
  Script::Interface::write(const Data& d)
  {
    if (_uuid_set.find(d.uuid()) == _uuid_set.end())
    {
      write(fmt::format("{} << EOD\n", d.uuid()));
      write(d.data());
      writeln("EOD");
      _uuid_set.insert(d.uuid());
    }
  };

  //////////////// Script ////////////////
  //
  Script::Script(pimpl_type&& pimpl) : _pimpl(std::move(pimpl)) {}

  Script::~Script()
  {
    if (_pimpl)
    {
      _pimpl->flush();
    }
  }

  Script&
  Script::set_title(const char* const title)
  {
    _pimpl->writeln(fmt::format("set title \"{}\"", title));

    return *this;
  }

  Script&
  Script::export_as(const Export_As& export_as, const char* const output)
  {
    _pimpl->write(export_as.scripted(output));

    return *this;
  }
  Script&
  Script::export_as(const Export_As& export_as_, const std::string& output)
  {
    export_as(export_as_, output.c_str());

    return *this;
  }

  /////////////////
  // Script_File //
  /////////////////

  namespace
  {
    struct Script_File_Interface_Impl : public Script::Interface
    {
      std::filesystem::path _filename;
      std::ofstream _file;

      void
      write(const std::string& s)
      {
        _file << s;
      }

      void
      flush()
      {
        _file << std::flush;
      }

      Script_File_Interface_Impl(const std::filesystem::path& filename)
          : _filename(filename), _file{_filename.c_str()}
      {
        assert(_file.is_open());
      }
      ~Script_File_Interface_Impl()
      {
        _file.close();

        std::string command;
        switch (global_config().file_script_mode())
        {
          case Script_File_Mode_Enum::Persistent:
            command = fmt::format("gnuplot -p \"{}\"", _filename.c_str());
            break;
          case Script_File_Mode_Enum::Silent:
            command = fmt::format("gnuplot \"{}\"", _filename.c_str());
            break;
          default:
            return;
        }

        if (global_config().log())
        {
          global_config().set_log_message(fmt::format("Running : {}", command).c_str());
        }
        int error = std::system(command.c_str());
        if (error)
        {
          if (global_config().log())
          {
            global_config().set_log_message(fmt::format("Got error code : {}", error).c_str());
          }
        }
      }
    };

  }

  Script_File::Script_File(const std::filesystem::path& filename)
      : Script(std::make_unique<Script_File_Interface_Impl>(filename))
  {
    if (global_config().log())
    {
      global_config().set_log_message(
          fmt::format("Creating : {}", filename.c_str()).c_str());
    }
  }
}
