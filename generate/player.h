
#ifndef PLAYER_H_CPP2
#define PLAYER_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/player.h2"

#line 7 "../src/player.h2"
class Player;
    

#line 26 "../src/player.h2"
class Human;
    

#line 45 "../src/player.h2"
class Random;
    

#line 66 "../src/player.h2"
class RandomSlow;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/player.h2"
#include "move.h"
#include "engine.h"
#include "io.h"

using namespace std::chrono_literals;

#line 7 "../src/player.h2"
class Player {
    public: Color color; 

    public: [[nodiscard]] virtual auto getMove(Engine& engine) const -> Move = 0;

    public: explicit Player(cpp2::impl::in<Color> c);

#line 16 "../src/player.h2"
    // CPP2 workaround: Default operator seems not working.
    public: Player(Player const& that);

#line 21 "../src/player.h2"
    // CPP2 workaround: Default operator seems not working.
    public: virtual ~Player() noexcept;

};

class Human: public Player {

#line 29 "../src/player.h2"
    public: explicit Human(cpp2::impl::in<Color> c);

#line 33 "../src/player.h2"
    public: Human(Human const& that);

#line 37 "../src/player.h2"
    public: [[nodiscard]] auto getMove([[maybe_unused]] Engine& unnamed_param_2) const -> Move override;

#line 40 "../src/player.h2"
};

static std::random_device rd;
static std::mt19937 rng(rd());

class Random: public Player {

#line 48 "../src/player.h2"
    public: explicit Random(cpp2::impl::in<Color> c);

#line 52 "../src/player.h2"
    public: Random(Random const& that);

#line 56 "../src/player.h2"
    public: [[nodiscard]] auto getMove(Engine& engine) const -> Move override;

#line 64 "../src/player.h2"
};

class RandomSlow: public Random {

    private: cpp2::i16 duration; 

    public: explicit RandomSlow(cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> sleep_duration);

#line 75 "../src/player.h2"
    public: RandomSlow(RandomSlow const& that);

#line 80 "../src/player.h2"
    public: [[nodiscard]] auto getMove(Engine& engine) const -> Move override;

#line 84 "../src/player.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/player.h2"

#line 12 "../src/player.h2"
    Player::Player(cpp2::impl::in<Color> c)
        : color{ c }{

#line 14 "../src/player.h2"
    }

#line 17 "../src/player.h2"
    Player::Player(Player const& that)
        : color{ that.color }{

#line 19 "../src/player.h2"
    }

#line 22 "../src/player.h2"
    Player::~Player() noexcept{
    }

#line 29 "../src/player.h2"
    Human::Human(cpp2::impl::in<Color> c)
        : Player{ c }{

#line 31 "../src/player.h2"
    }

#line 33 "../src/player.h2"
    Human::Human(Human const& that)
        : Player{ that }{

#line 35 "../src/player.h2"
    }

#line 37 "../src/player.h2"
    [[nodiscard]] auto Human::getMove([[maybe_unused]] Engine& unnamed_param_2) const -> Move{
        return getInputMove(color); 
    }

#line 48 "../src/player.h2"
    Random::Random(cpp2::impl::in<Color> c)
        : Player{ c }{

#line 50 "../src/player.h2"
    }

#line 52 "../src/player.h2"
    Random::Random(Random const& that)
        : Player{ that }{

#line 54 "../src/player.h2"
    }

#line 56 "../src/player.h2"
    [[nodiscard]] auto Random::getMove(Engine& engine) const -> Move{
        std::uniform_int_distribution<cpp2::i32> dist {0, 18}; 
        cpp2::i32 col {dist(rng)}; 
        cpp2::i32 row {cpp2::move(dist)(rng)}; 
        auto m {Move(color, cpp2::move(col), cpp2::move(row))}; 
        CPP2_UFCS(closerValidMove)(engine, m);
        return m; 
    }

#line 70 "../src/player.h2"
    RandomSlow::RandomSlow(cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> sleep_duration)
        : Random{ c }
        , duration{ sleep_duration }{

#line 73 "../src/player.h2"
    }

#line 75 "../src/player.h2"
    RandomSlow::RandomSlow(RandomSlow const& that)
        : Random{ that }
        , duration{ that.duration }{

#line 78 "../src/player.h2"
    }

#line 80 "../src/player.h2"
    [[nodiscard]] auto RandomSlow::getMove(Engine& engine) const -> Move{
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
        return Random::getMove(engine); 
    }
#endif

