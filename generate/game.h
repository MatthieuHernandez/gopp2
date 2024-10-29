
#ifndef GAME_H_CPP2
#define GAME_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/game.h2"

#line 6 "../src/game.h2"
class Game;


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/game.h2"
#include "engine.h"
#include "move.h"
#include "io.h"
#include "player.h"

#line 6 "../src/game.h2"
class Game {

    private: std::shared_ptr<Player> player1; // CPP2 workaround: Not able to make unique_prtr work.
    private: std::shared_ptr<Player> player2; 

    public: explicit Game(cpp2::impl::in<std::shared_ptr<Player>> p1, cpp2::impl::in<std::shared_ptr<Player>> p2);

#line 16 "../src/game.h2"
    public: auto play() const& -> void;
    public: Game(Game const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Game const&) -> void = delete;


#line 46 "../src/game.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/game.h2"

#line 11 "../src/game.h2"
    Game::Game(cpp2::impl::in<std::shared_ptr<Player>> p1, cpp2::impl::in<std::shared_ptr<Player>> p2)
        : player1{ p1 }
        , player2{ p2 }{

#line 14 "../src/game.h2"
    }

#line 16 "../src/game.h2"
    auto Game::play() const& -> void{
        Engine engine {}; 
{
auto moveNumber{1};

#line 19 "../src/game.h2"
        do {
            // clear();
            printGoban(engine.goban);
            Move m {};    // CPP2 workaround: Not able to make unique_prtr work.
            if (moveNumber % 2 == 1) {
                m = CPP2_UFCS(getMove)((*cpp2::impl::assert_not_null(player1)), engine);
            }else {
                m = CPP2_UFCS(getMove)((*cpp2::impl::assert_not_null(player2)), engine);
            }
            if (m.isValid) {
                CPP2_UFCS(playMove)(engine, m);
                setNextMessage(colorName(m.stone.color) + " played " + m.name + ".");
            }else {
                setNextMessage(colorName(m.stone.color) + " cannot play " + m.name + ".");
            }
        ++moveNumber;
        } while ( !(CPP2_UFCS(isFinish)(engine)));
}
#line 36 "../src/game.h2"
        CPP2_UFCS(countScore)(engine);
        if ((cpp2::impl::cmp_greater(engine.blackPoint,engine.whitePoint))) {
            setNextMessage("Black win " + cpp2::impl::as_<std::string>(engine.blackPoint) + " to " + cpp2::impl::as_<std::string>(engine.whitePoint) + ".5.");
        }
        else {
            setNextMessage("White win " + cpp2::impl::as_<std::string>(engine.whitePoint) + ".5 to " + cpp2::impl::as_<std::string>(engine.blackPoint) + ".");
        }
        printGoban(cpp2::move(engine).goban);
        waitInput();
    }
#endif

