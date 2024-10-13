
#ifndef GAME_H_CPP2
#define GAME_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/game.h2"

#line 5 "../src/game.h2"
class Game;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/game.h2"
#include "engine.h"
#include "move.h"
#include "io.h"

#line 5 "../src/game.h2"
class Game {
    public: static auto play() -> void;
    public: Game() = default;
    public: Game(Game const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Game const&) -> void = delete;


#line 19 "../src/game.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/game.h2"

#line 6 "../src/game.h2"
    auto Game::play() -> void{
        Engine engine {}; 
        auto state {engine.goban_state}; 
        auto current_player {Color::Black}; 
        do {
            printGoban(state);
            auto m {getInputMove(current_player)}; 
            clear();
            CPP2_UFCS(playMove)(engine, cpp2::move(m));
            state = engine.goban_state;
            switchPlayer(current_player);
        } while ( !(CPP2_UFCS(isFinish)(engine)));
}
#endif

