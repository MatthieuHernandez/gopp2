
#ifndef ITSELF_H_CPP2
#error This file is part of a '.h2' header compiled to be consumed from another -pure-cpp2 file. To use this file, write '#include "itself.h2"' in a '.h2' or '.cpp2' file compiled with -pure-cpp2.
#endif

#ifndef ITSELF_HPP_CPP2
#define ITSELF_HPP_CPP2

#include "player.hpp"
#include "ai.hpp"


//=== Cpp2 function definitions =================================================

#line 1 "../src/itself.h2"

#line 8 "../src/itself.h2"
    Itself::Itself(Interface* i, cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> r, cpp2::impl::in<Ai> aiToCopy)
         : Player{ i, c }
         , ai{ Ai(i, c, r, aiToCopy) }{

#line 11 "../src/itself.h2"
    }

#line 13 "../src/itself.h2"
    auto Itself::setColor(cpp2::impl::in<Color> c) -> void{
        color = c;
        CPP2_UFCS(setColor)(ai, c);
    }

#line 18 "../src/itself.h2"
    [[nodiscard]] auto Itself::getMove(Engine<9>& engine) -> Move{
        return CPP2_UFCS(getMove)(ai, engine); 
    }

#line 22 "../src/itself.h2"
    [[nodiscard]] auto Itself::getMove(Engine<19>& engine) -> Move{
        return CPP2_UFCS(getMove)(ai, engine); 
    }
#endif

