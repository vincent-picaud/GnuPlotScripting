#include <iostream>
#include "GnuPlotScripting/script.hpp"
#include "fmt/format.h"

using namespace GnuPlotScripting;

int main()
{
  std::string s = fmt::format("I'd rather be {1} than {0}.", "right", "happy");

  Script_File test("test.gp");
}
