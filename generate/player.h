
#ifndef PLAYER_H_CPP2
#define PLAYER_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/player.h2"

#line 10 "../src/player.h2"
class Player;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/player.h2"
#include "interface.h"
#include "move.h"
#include "engine.h"

using namespace std::chrono_literals;

static std::random_device rd;
static std::mt19937 rng(rd());

#line 10 "../src/player.h2"
class Player {
    protected: Interface* interface; 
    protected: Color color; 
    public: bool hasWon; 

    public: Player(Interface* i, cpp2::impl::in<Color> c);

#line 21 "../src/player.h2"
    public: [[nodiscard]] auto getColor() const& -> Color;

#line 25 "../src/player.h2"
    public: virtual auto setColor(cpp2::impl::in<Color> c) -> void;

#line 29 "../src/player.h2"
    public: [[nodiscard]] virtual auto getMove(Engine<9>& engine) -> Move = 0;

    public: [[nodiscard]] virtual auto getMove(Engine<19>& engine) -> Move = 0;

    // CPP2 workaround: Default operator seems not working.
    public: Player(Player const& that);

#line 39 "../src/player.h2"
    // CPP2 workaround: Default operator seems not working.
    public: virtual ~Player() noexcept;

#line 43 "../src/player.h2"
    public: virtual auto processStartGame() -> void;

    public: virtual auto processEndGame() -> void;
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/player.h2"

#line 15 "../src/player.h2"
    Player::Player(Interface* i, cpp2::impl::in<Color> c)
        : interface{ i }
        , color{ c }
        , hasWon{ false }{

#line 19 "../src/player.h2"
    }

#line 21 "../src/player.h2"
    [[nodiscard]] auto Player::getColor() const& -> Color{
        return color; 
    }

#line 25 "../src/player.h2"
    auto Player::setColor(cpp2::impl::in<Color> c) -> void{
        color = c;
    }

#line 34 "../src/player.h2"
    Player::Player(Player const& that)
        : interface{ that.interface }
        , color{ that.color }
        , hasWon{ that.hasWon }{

#line 37 "../src/player.h2"
    }

#line 40 "../src/player.h2"
    Player::~Player() noexcept{
    }

#line 43 "../src/player.h2"
    auto Player::processStartGame() -> void{}

#line 45 "../src/player.h2"
    auto Player::processEndGame() -> void{}
#endif

