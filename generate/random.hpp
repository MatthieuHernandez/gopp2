
#ifndef RANDOM_H_CPP2
#error This file is part of a '.h2' header compiled to be consumed from another -pure-cpp2 file. To use this file, write '#include "random.h2"' in a '.h2' or '.cpp2' file compiled with -pure-cpp2.
#endif

#ifndef RANDOM_HPP_CPP2
#define RANDOM_HPP_CPP2

#include "player.hpp"


//=== Cpp2 function definitions =================================================

#line 1 "../src/random.h2"

#line 6 "../src/random.h2"
           Random::Random(Interface* i, cpp2::impl::in<Color> c)
        : Player{ i, c }{

#line 8 "../src/random.h2"
    }

#line 10 "../src/random.h2"
    Random::Random(Random const& that)
        : Player{ that }{

#line 12 "../src/random.h2"
    }

#line 14 "../src/random.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Random::getMove(Engine<Size>& engine) & -> Move{
        cpp2::i8 maxIndex {Size - 1}; 
        std::uniform_int_distribution<cpp2::i32> dist {0, cpp2::move(maxIndex)}; 
        cpp2::i32 col {dist(rng)}; 
        cpp2::i32 row {cpp2::move(dist)(rng)}; 
        auto m {Move(color, cpp2::move(col), cpp2::move(row))}; 
        CPP2_UFCS(closerValidMove)(engine, m);
        return m; 
    }

#line 24 "../src/random.h2"
    [[nodiscard]] auto Random::getMove(Engine<9>& engine) -> Move{
        return getMove<9>(engine); 
    }

#line 28 "../src/random.h2"
    [[nodiscard]] auto Random::getMove(Engine<19>& engine) -> Move{
        return getMove<19>(engine); 
    }
#endif

