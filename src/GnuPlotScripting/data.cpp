#include "GnuPlotScripting/data.hpp"

#include <random>
#include <sstream>

namespace GnuPlotScripting
{
  ///////////////////
  // Generate UUID //
  ///////////////////
  //
  namespace
  {
    unsigned int
    random_char()
    {
      static std::random_device rd;
      static std::mt19937 gen(rd());
      static std::uniform_int_distribution<> dis(0, 255);
      return dis(gen);
    }

    std::string
    generate_uuid(const size_t len)
    {
      std::stringstream ss;
      for (size_t i = 0; i < len; i++)
      {
        const auto rc = random_char();
        std::stringstream hexstream;
        hexstream << std::hex << rc;
        auto hex = hexstream.str();
        ss << (hex.length() < 2 ? '0' + hex : hex);
      }
      return ss.str();
    }
  }

  ///////////////
  // Data_Uuid //
  ///////////////
  //
  Data_Uuid::Data_Uuid() : _uuid("data_" + generate_uuid(5)) {}

  std::string_view
  Data_Uuid::as_string_view() const
  {
    return std::string_view(_uuid);
  }

  bool
  Data_Uuid::operator<(const Data_Uuid& other) const
  {
    return _uuid < other._uuid;
  }
}
