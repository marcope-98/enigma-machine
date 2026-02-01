#ifndef ENMACH_UTILS_HPP_
#define ENMACH_UTILS_HPP_

#include <cctype>
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

  // clang-format off
  constexpr auto is_lowercase   = [](char character) noexcept { return character >= 'a' && character <= 'z'; };
  // clang-format on

  [[nodiscard]] constexpr auto to_lowercase_or_die(char letter) -> char
  {
    letter = static_cast<char>(std::tolower(letter));
    if (!is_lowercase(letter)) 
      throw std::invalid_argument("Character must be a lowercase letter (a-z) or uppercase letter (A-Z)");
    return letter;
  }

} // namespace enmach

#endif // ENMACH_UTILS_HPP_