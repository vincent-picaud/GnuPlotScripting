#include <iostream>
#include "GnuPlotScripting/script.hpp"
#include "fmt/format.h"

#include "GnuPlotScripting/data_std_vector.hpp"

#include <type_traits>

using namespace GnuPlotScripting;

template <typename... ARGS>
void
foo(ARGS&&... args)
{
  auto register_data = [](const auto& arg) {
    using arg_type = std::decay_t<decltype(arg)>;
    if constexpr (std::is_base_of_v<Data, arg_type>) std::cerr << "\n got one";
  };
  (register_data(args), ...);
}

template <typename T>
void
printType()
{
  std::cerr << __PRETTY_FUNCTION__ << std::endl;
}

struct Test
{
  Test() = delete;

  // template <typename T, typename... Ts>
  // Test(const T& t, const Ts&... ts)
  // {
  //   printType<T>();
  // }

  // template <typename T>
  // Test(const T& t)
  // {
  //   printType<T>();
  // }
};

int
main()
{
  std::vector<double> v1(10, 5);
  Data_Vector test_1(v1);

  Script_File test("test.gp");

  test.free_form("plot sin(x) t \"super\"");
  test.free_form("replot {} w l t \"ca marche?\"", test_1);
  test.free_form("replot {} u ($1)+2 w l lw 3 t \"oui!?\"", test_1);
}
