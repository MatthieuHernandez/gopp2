
#ifndef PLAYER_H_CPP2
#define PLAYER_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/player.h2"

#line 7 "../src/player.h2"
class Player;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/player.h2"
#include "move.h"
#include "engine.h"
#include "io.h"

using namespace std::chrono_literals;

#line 7 "../src/player.h2"
class Player {
    public: Color color; 
    public: bool hasWon; 

    public: [[nodiscard]] virtual auto getMove(Engine& engine) -> Move = 0;

    public: explicit Player(cpp2::impl::in<Color> c);

#line 18 "../src/player.h2"
    // CPP2 workaround: Default operator seems not working.
    public: Player(Player const& that);

#line 24 "../src/player.h2"
    // CPP2 workaround: Default operator seems not working.
    public: virtual ~Player() noexcept;

};


//=== Cpp2 function definitions =================================================

#line 1 "../src/player.h2"

#line 13 "../src/player.h2"
    Player::Player(cpp2::impl::in<Color> c)
        : color{ c }
        , hasWon{ false }{

#line 16 "../src/player.h2"
    }

#line 19 "../src/player.h2"
    Player::Player(Player const& that)
        : color{ that.color }
        , hasWon{ that.hasWon }{

#line 22 "../src/player.h2"
    }

#line 25 "../src/player.h2"
    Player::~Player() noexcept{
    }
#endif

