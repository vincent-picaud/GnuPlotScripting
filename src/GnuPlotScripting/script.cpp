#include "GnuPlotScripting/script.hpp"

#include <fstream>
#include <iostream>

namespace GnuPlotScripting
{
  ////////////
  // Script //
  ////////////

  //////////////// Constructors ////////////////
  //
  Script::Script(pimpl_type&& pimpl) : _pimpl(std::move(pimpl))
  {
  }

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
    struct Script_File_Pimpl : public Script::Implementation
    {
      std::filesystem::path _filename;
      std::ofstream _file;

      void write(const std::string& s)
      {
        _file << s;
      }
      void writeln(const std::string& s)
      {
        write(s);
        write("\n");
      }
      void flush()
      {
        _file << std::flush;
      }

      Script_File_Pimpl(const std::filesystem::path& filename) : _filename(filename), _file{_filename.c_str()}
      {
        assert(_file.is_open());
      }
      ~Script_File_Pimpl()
      {
        _file.close();

        const std::string command = fmt::format("gnuplot -p \"{0}\"", _filename.c_str());
        int error = std::system(command.c_str());
        if (error)
        {
          std::cerr << "*** Error: " << command;
        }

        // if (_run_gnuplot)
        // {
        //   std::stringstream command;
        //   // TODO / FIXME: windows, maybe gnuplot.exe
        //   command << "gnuplot -p " << _filename.c_str();
        //   int error = std::system(command.str().c_str());
        //   if (error)
        //   {
        //     std::cerr << "*** Error: the command \"" << command.str() << "\" returned error code:" << error;
        //   }
        // }
      }
    };

  }  // namespace

  Script_File::Script_File(const std::filesystem::path& filename) : Script(std::make_unique<Script_File_Pimpl>(filename))
  {
  }

}  // namespace GnuPlotScripting
