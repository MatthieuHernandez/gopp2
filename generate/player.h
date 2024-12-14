
#ifndef PLAYER_H_CPP2
#define PLAYER_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/player.h2"

#line 9 "../src/player.h2"
class Player;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/player.h2"
#include "move.h"
#include "engine.h"

using namespace std::chrono_literals;

static std::random_device rd;
static std::mt19937 rng(rd());

#line 9 "../src/player.h2"
class Player {
    public: Color color; 
    public: bool hasWon; 

    public: [[nodiscard]] virtual auto getMove(Engine& engine) -> Move = 0;

    public: Player(cpp2::impl::in<Color> c);

#line 20 "../src/player.h2"
    // CPP2 workaround: Default operator seems not working.
    public: Player(Player const& that);

#line 26 "../src/player.h2"
    // CPP2 workaround: Default operator seems not working.
    public: virtual ~Player() noexcept;

#line 30 "../src/player.h2"
    public: virtual auto processEndGame() -> void;
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/player.h2"

#line 15 "../src/player.h2"
    Player::Player(cpp2::impl::in<Color> c)
        : color{ c }
        , hasWon{ false }{

#line 18 "../src/player.h2"
    }

#line 21 "../src/player.h2"
    Player::Player(Player const& that)
        : color{ that.color }
        , hasWon{ that.hasWon }{

#line 24 "../src/player.h2"
    }

#line 27 "../src/player.h2"
    Player::~Player() noexcept{
    }

#line 30 "../src/player.h2"
    auto Player::processEndGame() -> void{}
#endif

