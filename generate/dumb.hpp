
#ifndef DUMB_H_CPP2
#error This file is part of a '.h2' header compiled to be consumed from another -pure-cpp2 file. To use this file, write '#include "dumb.h2"' in a '.h2' or '.cpp2' file compiled with -pure-cpp2.
#endif

#ifndef DUMB_HPP_CPP2
#define DUMB_HPP_CPP2

#include "player.hpp"


//=== Cpp2 function definitions =================================================

#line 1 "../src/dumb.h2"

#line 6 "../src/dumb.h2"
    Dumb::Dumb(Interface* i, cpp2::impl::in<Color> c)
        : Player{ i, c }{

#line 8 "../src/dumb.h2"
    }

#line 10 "../src/dumb.h2"
    Dumb::Dumb(Dumb const& that)
        : Player{ that }{

#line 12 "../src/dumb.h2"
    }

#line 14 "../src/dumb.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Dumb::getMove(Engine<Size>& engine) & -> Move{
        auto m {Move(color, 0, 0)}; 
        CPP2_UFCS(closerValidMove)(engine, m);
        return m; 
    }

#line 20 "../src/dumb.h2"
    [[nodiscard]] auto Dumb::getMove(Engine<9>& engine) -> Move{
        return getMove<9>(engine); 
    }

#line 24 "../src/dumb.h2"
    [[nodiscard]] auto Dumb::getMove(Engine<19>& engine) -> Move{
        return getMove<19>(engine); 
    }
#endif

