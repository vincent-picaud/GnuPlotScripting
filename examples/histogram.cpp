#include "GnuPlotScripting/GnuPlotScripting.hpp"

#include <iostream>
#include <random>

using namespace GnuPlotScripting;

template <typename T>
struct type_identity
{
  using type = T;
};
template <typename T>
using type_identity_t = typename type_identity<T>::type;

// Example from:
// https://stackoverflow.com/a/7454274/2001017
//
template <typename T>
void
gnuplot_histogram(Script& script,
                  const std::vector<T>& data,
                  const size_t n_bin,
                  type_identity_t<T> min,
                  type_identity_t<T> max)
{
  assert(max > min);

  Data_Vector gnuplot_data(data);

  const double width = (max - min) / (n_bin + 1.);
  script.free_form("width={}", width);
  script.free_form("hist(x,width)=width*floor(x/width)+width/2.0");
  script.free_form("set boxwidth width*0.9");
  script.free_form("set style fill solid 0.5");
  script.free_form("plot {} u (hist($1,width)):(1.0) smooth freq w boxes notitle", gnuplot_data);
}

int
main()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  const double a = 2, b = 1;
  std::gamma_distribution<> distribution(a, b);

  std::vector<double> data(10000);
  for (auto& data_i : data) data_i = distribution(gen);

  Script_File script("histogram.gp", Script_File_Mode_Enum::Persistent);

  script.free_form("set title \"Gamma({},{}) distributed sample", a, b);

  gnuplot_histogram(script, data, 100, 0, 3);

  script.export_as(PNG(), "histogram");
}
