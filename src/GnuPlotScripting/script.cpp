#include "GnuPlotScripting/script.hpp"

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

        const std::string command = fmt::format("gnuplot -p \"{0}\"", _filename.c_str());
        int error                 = std::system(command.c_str());
        if (error)
        {
          std::cerr << "*** Error: " << command;
        }
      }
    };

  }

  Script_File::Script_File(const std::filesystem::path& filename)
      : Script(std::make_unique<Script_File_Interface_Impl>(filename))
  {
  }

}
