#pragma once

#include <string>

namespace GnuPlotScripting
{
  class Data_Uuid
  {
    std::string _uuid;

   public:
    Data_Uuid();

    std::string_view as_string_view() const;

    bool operator<(const Data_Uuid& other) const;
  };

}
