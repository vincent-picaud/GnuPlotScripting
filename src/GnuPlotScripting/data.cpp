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

    class Interface_Impl : public Data::Interface
    {
      std::string _uuid;
      std::string _data;

     public:
      Interface_Impl(std::string&& embedded_data)
          : _uuid("$D" + generate_uuid(5)), _data(std::move(embedded_data)){};
      Interface_Impl(const std::string& embedded_data)
          : _uuid("$D" + generate_uuid(5)), _data(embedded_data){};

      const std::string&
      uuid() const final
      {
        return _uuid;
      }
      const std::string&
      data() const final
      {
        return _data;
      }
    };
  }

  Data::Data(std::string&& embedded_data)
      : _pimpl(std::make_shared<const Interface_Impl>(std::move(embedded_data)))
  {
  }
  Data::Data(const std::string& embedded_data)
      : _pimpl(std::make_shared<const Interface_Impl>(embedded_data))
  {
  }

  const std::string&
  Data::uuid() const
  {
    return _pimpl->uuid();
  }
  const std::string&
  Data::data() const
  {
    return _pimpl->data();
  }

}
