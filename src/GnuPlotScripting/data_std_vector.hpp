#pragma once

#include "GnuPlotScripting/data.hpp"

#include <cassert>
#include <sstream>
#include <valarray>
#include <vector>

namespace GnuPlotScripting
{
  class Data_Std_Vector final : public Data
  {
    template <typename T, typename... Ts>
    static std::string
    create_embedded_data(const std::vector<T>& vector, const std::vector<Ts>&... vectors)
    {
      const size_t n = vector.size();
      assert(((n == vectors.size()) && ...));

      std::stringstream buffer;
      for (size_t i = 0; i < n; ++i)
      {
        buffer << vector[i] << " ";
        ((buffer << vectors[i] << " "), ...);
        buffer << "\n";
      }

      return buffer.str();
    }

   public:
    template <typename T, typename... Ts>
    Data_Std_Vector(const std::vector<T>& vector, const std::vector<Ts>&... vectors)
        : Data(create_embedded_data(vector, vectors...))
    {
    }
  };

#define RETURNS(...) \
  noexcept(noexcept(__VA_ARGS__))->decltype(__VA_ARGS__) { return __VA_ARGS__; }

#define METHOD(NAME) \
  [](auto&& self, auto&&... args) RETURNS(decltype(self)(self).NAME(decltype(args)(args)...))

  auto call_size = METHOD(size);

  class Data_Vector final : public Data
  {
    template <typename VECTOR, typename... VECTORs>
    std::string
    create_embedded_data(const VECTOR& vector, const VECTORs&... vectors)
    {
      const size_t n = vector.size();
      assert(((n == vectors.size()) && ...));

      std::stringstream buffer;
      for (size_t i = 0; i < n; ++i)
      {
        buffer << vector[i] << " ";
        ((buffer << vectors[i] << " "), ...);
        buffer << "\n";
      }

      return buffer.str();
    }

   public:
    template <typename VECTOR, typename... VECTORs>
    Data_Vector(const VECTOR& vector, const VECTORs&... vectors)
        : Data(create_embedded_data(vector, vectors...))
    {
      // static_assert(std::is_invocable_r<std::size_t, decltype(call_size), VECTOR&, double>{});

      static_assert(std::is_invocable_r_v<size_t, decltype(&VECTOR::size), VECTOR&>);

      // static_assert(std::is_invocable_r_v<size_t, decltype(&VECTOR::size), VECTOR> &&
      //               std::is_invocable_v<decltype(&std::decay_t<VECTOR>::operator[]),
      //                                   std::decay_t<VECTOR>,
      //                                   size_t>);
      //  static_assert(
      // static_assert(
      //     (std::is_invocable_r_v<size_t, decltype(&VECTOR::size), VECTOR> &&
      //      std::is_invocable_v<
      //          decltype(&std::decay_t<VECTOR>::operator[]),
      //          std::decay_t<VECTOR>,
      //          size_t>)&&((std::is_invocable_r_v<size_t, decltype(&VECTORs::size), VECTORs> &&
      //                      std::is_invocable_v<decltype(&VECTORs::operator[]), VECTORs>)&&...),
      //     "Must have size() and operator[] methods");
    }
  };
}
