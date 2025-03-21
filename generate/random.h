
#ifndef RANDOM_H_CPP2
#define RANDOM_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/random.h2"

#line 3 "../src/random.h2"
class Random;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/random.h2"
#include "player.h"

#line 3 "../src/random.h2"
class Random: public Player {

#line 6 "../src/random.h2"
           public: Random(Interface* i, cpp2::impl::in<Color> c);

#line 10 "../src/random.h2"
    public: Random(Random const& that);

#line 14 "../src/random.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto getMove(Engine<Size>& engine) & -> Move;

#line 24 "../src/random.h2"
    public: [[nodiscard]] auto getMove(Engine<9>& engine) -> Move override;

#line 28 "../src/random.h2"
    public: [[nodiscard]] auto getMove(Engine<19>& engine) -> Move override;

#line 31 "../src/random.h2"
};


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

