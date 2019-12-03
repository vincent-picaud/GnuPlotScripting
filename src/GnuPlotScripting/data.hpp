#pragma once

#include <string>

namespace GnuPlotScripting
{
  class Data_Uuid
  {
    std::string _uuid;

   public:
    Data_Uuid();

    bool operator<(const Data_Uuid& other) const;
  };

}
