
#ifndef HUMAN_H_CPP2
#error This file is part of a '.h2' header compiled to be consumed from another -pure-cpp2 file. To use this file, write '#include "human.h2"' in a '.h2' or '.cpp2' file compiled with -pure-cpp2.
#endif

#ifndef HUMAN_HPP_CPP2
#define HUMAN_HPP_CPP2

#include "player.hpp"


//=== Cpp2 function definitions =================================================

#line 1 "../src/human.h2"

#line 6 "../src/human.h2"
    Human::Human(Interface* i, cpp2::impl::in<Color> c)
        : Player{ i, c }{

#line 8 "../src/human.h2"
    }

#line 10 "../src/human.h2"
    Human::Human(Human const& that)
        : Player{ that }{

#line 12 "../src/human.h2"
    }

#line 14 "../src/human.h2"
    [[nodiscard]] auto Human::getMove([[maybe_unused]] Engine<9>& unnamed_param_2) -> Move{
        return CPP2_UFCS(waitForAMove)((*cpp2::impl::assert_not_null(interface)), color); 
    }

#line 18 "../src/human.h2"
    [[nodiscard]] auto Human::getMove([[maybe_unused]] Engine<13>& unnamed_param_2) -> Move{
        return CPP2_UFCS(waitForAMove)((*cpp2::impl::assert_not_null(interface)), color); 
    }

#line 22 "../src/human.h2"
    [[nodiscard]] auto Human::getMove([[maybe_unused]] Engine<19>& unnamed_param_2) -> Move{
        return CPP2_UFCS(waitForAMove)((*cpp2::impl::assert_not_null(interface)), color); 
    }
#endif

