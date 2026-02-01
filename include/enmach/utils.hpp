#ifndef ENMACH_UTILS_HPP_
#define ENMACH_UTILS_HPP_

#include <tuple>
#include <type_traits>
#include <utility>

namespace enmach
{
  template<class...>
  inline constexpr auto is_unique = std::true_type{};

  template<class T, class... Args>
  inline constexpr auto is_unique<T, Args...> = std::bool_constant<(!std::is_same_v<T, Args> && ...) && is_unique<Args...>>{};

  template<class... Tags>
  struct Set
  {
    template<class Needle>
    constexpr static bool is_in_set()
    {
      return (std::is_same_v<Needle, Tags> || ...);
    }
  };

} // namespace enmach

#endif // ENMACH_UTILS_HPP_