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

  void
  Script::flush()
  {
    _pimpl->flush();
  }

  Script&
  Script::set_title(const char* const title)
  {
    _pimpl->writeln(fmt::format("set title \"{}\"", title));

    return *this;
  }

  Script&
  Script::export_as(const Export_As& export_as_, const std::filesystem::path& output)
  {
    _pimpl->write(export_as_.export_as(output));

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
      Script_File_Mode_Enum _script_file_mode;
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

      Script_File_Interface_Impl(const std::filesystem::path& filename,
                                 Script_File_Mode_Enum script_file_mode)
          : _filename(filename), _script_file_mode(script_file_mode), _file{_filename.c_str()}
      {
        assert(_file.is_open());
      }
      ~Script_File_Interface_Impl()
      {
        _file.close();

        std::optional<Script_File_Mode_Enum> script_file_mode = global_config().script_file_mode();
        if (!script_file_mode.has_value())
        {
          // If global does not have defined value,
          // use our local one
          // TODO...
          script_file_mode = Script_File_Mode_Enum::Persistent;
        }
        assert(script_file_mode.has_value());
        std::string command;
        switch (*script_file_mode)
        {
          case Script_File_Mode_Enum::Persistent:
            command = fmt::format("{} -p \"{}\"", global_config().gnuplot_exe(), _filename.c_str());
            break;
          case Script_File_Mode_Enum::Silent:
            command = fmt::format("{} \"{}\"", global_config().gnuplot_exe(), _filename.c_str());
            break;
          default:
            return;
        }

        if (global_config().log())
        {
          global_config().set_log_message(fmt::format("Running  : {}", command).c_str());
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

  Script_File::Script_File(const std::filesystem::path& filename,
                           const Script_File_Mode_Enum script_file_mode)
      : Script(std::make_unique<Script_File_Interface_Impl>(filename, script_file_mode))
  {
    if (global_config().log())
    {
      global_config().set_log_message(fmt::format("Created  : {}", filename.c_str()).c_str());
    }
  }

  /////////////////
  // Script_Pipe //
  /////////////////
  //
  // NOTE: not tested under windows, must have to add something like:
  //      - #ifdef WIN32 _pclose(fp)
  //      - #ifdef WIN32 _popen("gnuplot.exe", "w")
  // etc... see https://stackoverflow.com/a/8249232/2001017
  //

  namespace
  {
    struct Script_Pipe_Interface_Impl : public Script::Interface
    {
      static void
      close_pipe(std::FILE* fp)
      {
        pclose(fp);
      }
      static std::FILE*
      open_gnuplot_pipe(const Script_Pipe_Mode_Enum persistent)
      {
        assert((persistent == Script_Pipe_Mode_Enum::Persistent) or
               (persistent == Script_Pipe_Mode_Enum::Not_Persistent));

        std::FILE* fp;
        std::string cmd = global_config().gnuplot_exe();
        if (persistent == Script_Pipe_Mode_Enum::Persistent)
        {
          cmd += " -p";
        }
        fp = popen(cmd.c_str(), "w");

        if (fp == nullptr)
        {
          if (global_config().log())
          {
            global_config().set_log_message(
                fmt::format("Cannot popen GnuPlot executable {}", cmd).c_str());
          }
        }
        return fp;
      }

      Script_Pipe_Mode_Enum _script_pipe_mode;
      std::unique_ptr<FILE, decltype(&close_pipe)> _pipe;

      void
      write(const std::string& s)
      {
        assert(_pipe);
        fputs(s.c_str(), _pipe.get());
      }

      void
      flush()
      {
        assert(_pipe);
        fflush(_pipe.get());
      }

      Script_Pipe_Interface_Impl(Script_Pipe_Mode_Enum script_pipe_mode)
          : _script_pipe_mode(script_pipe_mode),
            _pipe{open_gnuplot_pipe(_script_pipe_mode), &close_pipe}
      {
        assert(_pipe);
      }
      ~Script_Pipe_Interface_Impl() = default;
    };

  }

  Script_Pipe::Script_Pipe(Script_Pipe_Mode_Enum script_pipe_mode)
      : Script(std::make_unique<Script_Pipe_Interface_Impl>(script_pipe_mode))
  {
    if (global_config().log())
    {
      global_config().set_log_message("Created  : GnuPlot pipe");
    }
  }

}
