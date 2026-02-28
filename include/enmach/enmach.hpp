#ifndef ENMACH_ENMACH_HPP_
#define ENMACH_ENMACH_HPP_

#include "enmach/EnigmaMachine.hpp"
#include "enmach/Reflector.hpp"
#include "enmach/Rotor.hpp"
#include "enmach/utils.hpp"

namespace enmach
{
  using namespace enmach::rotor_tags;

  template<class... Args>
  using EnigmaM1 = EnigmaMachine<
      EnigmaMachineConfiguration<
          Set<I, II, III, IV, V>,
          Set<ukw::A, ukw::B, ukw::C>,
          3>,
      Args...>;

  template<class... Args>
  using EnigmaM3 = EnigmaMachine<
      EnigmaMachineConfiguration<
          Set<I, II, III, IV, V, VI, VII, VIII>,
          Set<ukw::A, ukw::B, ukw::C>,
          3>,
      Args...>;

  template<class Plugboard, class Reflector, class Zusatzwalze, class... Rotors>
  struct EnigmaM4_t
  {
    static_assert(std::is_same_v<Zusatzwalze, BETA> || std::is_same_v<Zusatzwalze, GAMMA>, "[ERROR] Zusatzwalze (4th rotor) must be either rotor_tags::BETA or rotor_tags::GAMMA.");
    static_assert(!(Set<BETA, GAMMA>::template is_in_set<Rotors>() || ...), "the three standard rotors must not be BETA or GAMMA. Those are reserved for the Zusatzwalze position.");
    using type = EnigmaMachine<
        EnigmaMachineConfiguration<
            Set<I, II, III, IV, V, VI, VII, VIII, BETA, GAMMA>,
            Set<ukw::ThinB, ukw::ThinC>,
            4>,
        Plugboard, Reflector, Zusatzwalze, Rotors...>;
  };

  template<class Plugboard, class Reflector, class Zusatzwalze, class... Rotors>
  using EnigmaM4 = typename EnigmaM4_t<Plugboard, Reflector, Zusatzwalze, Rotors...>::type;
} // namespace enmach

#endif // ENMACH_ENMACH_HPP_