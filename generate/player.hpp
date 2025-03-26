
#ifndef PLAYER_H_CPP2
#error This file is part of a '.h2' header compiled to be consumed from another -pure-cpp2 file. To use this file, write '#include "player.h2"' in a '.h2' or '.cpp2' file compiled with -pure-cpp2.
#endif

#ifndef PLAYER_HPP_CPP2
#define PLAYER_HPP_CPP2

#include "interface.hpp"
#include "move.hpp"
#include "engine.hpp"


//=== Cpp2 function definitions =================================================

#line 1 "../src/player.h2"

#line 7 "../src/player.h2"
std::random_device rd {}; 
std::mt19937 rng {rd()}; 

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

