// tutorial: https://blog.tartanllama.xyz/detection-idiom/
#pragma once

#include <type_traits>

namespace GnuPlotScripting
{
  ////////////////////////////////
  // has_random_access_operator //
  ////////////////////////////////

  template <class, class = std::void_t<>>
  struct has_random_access_operator : std::false_type
  {
  };

  template <class T>
  struct has_random_access_operator<
      T,
      std::void_t<decltype(std::declval<T>()[std::declval<size_t>()])>> : std::true_type
  {
  };

  template <class T>
  static constexpr auto has_random_access_operator_v = has_random_access_operator<T>::value;

  /////////////////////
  // has_size_method //
  /////////////////////

  template <class, class = std::void_t<>>
  struct has_size_method : std::false_type
  {
  };

  template <class T>
  struct has_size_method<T, std::void_t<decltype(std::declval<T>().size())>> : std::true_type
  {
  };

  template <class T>
  static constexpr auto has_size_method_v = has_size_method<T>::value;

}
