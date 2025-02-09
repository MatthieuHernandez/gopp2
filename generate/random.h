
#ifndef RANDOM_H_CPP2
#define RANDOM_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/random.h2"

#line 3 "../src/random.h2"
class Random;
    

#line 24 "../src/random.h2"
class RandomSlow;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/random.h2"
#include "player.h"

#line 3 "../src/random.h2"
class Random: public Player {

#line 6 "../src/random.h2"
    public: Random(cpp2::impl::in<Color> c);

#line 10 "../src/random.h2"
    public: Random(Random const& that);

#line 14 "../src/random.h2"
    public: [[nodiscard]] auto getMove(Engine& engine) -> Move override;

#line 22 "../src/random.h2"
};

class RandomSlow: public Random {

    private: cpp2::i16 duration; 

    public: RandomSlow(cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> sleep_duration);

#line 33 "../src/random.h2"
    public: RandomSlow(RandomSlow const& that);

#line 38 "../src/random.h2"
    public: [[nodiscard]] auto getMove(Engine& engine) -> Move override;

#line 42 "../src/random.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/random.h2"

#line 6 "../src/random.h2"
    Random::Random(cpp2::impl::in<Color> c)
        : Player{ c }{

#line 8 "../src/random.h2"
    }

#line 10 "../src/random.h2"
    Random::Random(Random const& that)
        : Player{ that }{

#line 12 "../src/random.h2"
    }

#line 14 "../src/random.h2"
    [[nodiscard]] auto Random::getMove(Engine& engine) -> Move{
        std::uniform_int_distribution<cpp2::i32> dist {0, 18}; 
        cpp2::i32 col {dist(rng)}; 
        cpp2::i32 row {cpp2::move(dist)(rng)}; 
        auto m {Move(color, cpp2::move(col), cpp2::move(row))}; 
        CPP2_UFCS(closerValidMove)(engine, m);
        return m; 
    }

#line 28 "../src/random.h2"
    RandomSlow::RandomSlow(cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> sleep_duration)
        : Random{ c }
        , duration{ sleep_duration }{

#line 31 "../src/random.h2"
    }

#line 33 "../src/random.h2"
    RandomSlow::RandomSlow(RandomSlow const& that)
        : Random{ that }
        , duration{ that.duration }{

#line 36 "../src/random.h2"
    }

#line 38 "../src/random.h2"
    [[nodiscard]] auto RandomSlow::getMove(Engine& engine) -> Move{
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
        return Random::getMove(engine); 
    }
#endif

