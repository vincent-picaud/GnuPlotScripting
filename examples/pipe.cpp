#include "GnuPlotScripting/GnuPlotScripting.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <utility>  // std::pair
#include <vector>

using namespace GnuPlotScripting;

int
main()
{
  // AFAIK one has to replot all data at each iteration
  //
  std::vector<std::pair<size_t, double>> data;

  Script_Pipe pipe(Script_Pipe_Mode_Enum::Not_Persistent);

  pipe.free_form("set xlabel 'iterations'");

  for (size_t i = 0; i < 100; i++)
  {
    data.push_back({i, 1 / (i + 1.)});

    pipe.free_form("plot '-' using 1:2 with lines t \"residue\" ");
    for (const auto& data_i : data)
    {
      pipe.free_form("{} {}", data_i.first, data_i.second);
    }
    pipe.free_form("e");
    pipe.flush();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}
