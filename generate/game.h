
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


#line 23 "../src/game.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/game.h2"

#line 6 "../src/game.h2"
    auto Game::play() -> void{
        Engine engine {}; 
        do {
            printGoban(engine.goban);
            auto m {getInputMove(engine.nextMovePlayer)}; 
            //clear();
            if (CPP2_UFCS(isValidMove)(engine, m)) {
                CPP2_UFCS(playMove)(engine, m);
                setNextMessage(colorName(m.stone.color) + " played " + m.name + "." 
                + " The stone has " + cpp2::impl::as_<std::string>(CPP2_UFCS(numberOfLiberties)(engine, m.stone)) + " liberties.");
            }
            else {
                setNextMessage(colorName(m.stone.color) + " cannot play " + m.name + ".");
            }

        } while ( !(CPP2_UFCS(isFinish)(engine)));
}
#endif

