#pragma once

#include <memory>
#include <string>

namespace GnuPlotScripting
{
  class Data
  {
   public:
    struct Interface
    {
      virtual const std::string& uuid() const = 0;
      virtual const std::string& data() const = 0;

      virtual ~Interface() = default;
    };

   protected:
    using pimpl_type = std::shared_ptr<const Interface>;
    pimpl_type _pimpl;

    Data(std::string&& embedded_data);
    Data(const std::string& embedded_data);

    Data& operator=(const Data&) = default;  // block object slicing

   public:
    const std::string& uuid() const;
    const std::string& data() const;

    // used by fmt::format
    operator const char*() const { return uuid().c_str(); };
  };

}
