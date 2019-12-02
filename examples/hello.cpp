#include "GnuPlotScripting/hello.hpp"
#include <iostream>
#include "fmt/format.h"

using namespace GnuPlotScripting;

int main()
{
  std::string s = fmt::format("I'd rather be {1} than {0}.", "right", "happy");
  std::cout << hello() << " from examples/ " << std::endl;
}
