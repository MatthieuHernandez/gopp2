
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

    public: Game(cpp2::impl::in<std::shared_ptr<Player>> p1, cpp2::impl::in<std::shared_ptr<Player>> p2);

#line 16 "../src/game.h2"
    public: template<bool verbose> auto play() const& -> void;
    public: Game(Game const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Game const&) -> void = delete;


#line 62 "../src/game.h2"
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
    template<bool verbose> auto Game::play() const& -> void{
        auto start {std::chrono::high_resolution_clock::now()}; 
        Engine engine {}; 
        cpp2::i16 moveNumber {1}; 
        do {
            if constexpr (verbose) {
                printGoban(engine.goban);
            }
            Move m {};    // CPP2 workaround: Not able to make unique_prtr work.
            if (moveNumber % 2 == 1) {
                m = CPP2_UFCS(getMove)((*cpp2::impl::assert_not_null(player1)), engine);
            }else {
                m = CPP2_UFCS(getMove)((*cpp2::impl::assert_not_null(player2)), engine);
            }
            if (CPP2_UFCS(isValidMove)(engine, m)) {
                CPP2_UFCS(playMove)(engine, m);
                ++moveNumber;
                if constexpr (verbose) {
                    setNextMessage(colorName(m.stone.color) + " played " + m.name + ".");
                }
            }else {
                if constexpr (verbose) {
                    setNextMessage(colorName(m.stone.color) + " cannot play " + m.name + ".");
                }
            }
            if ((cpp2::impl::cmp_greater_eq(moveNumber,1000))) {// Only to prevent an eventual triple ko.
                break;
            }
        } while ( !(CPP2_UFCS(isFinish)(engine)));
        CPP2_UFCS(countScore)(engine);
        setNextMessage("The game ends after " + cpp2::impl::as_<std::string>(cpp2::move(moveNumber)) + " moves.");
        if ((cpp2::impl::cmp_greater(engine.blackPoint,engine.whitePoint))) {
            (*cpp2::impl::assert_not_null(player1)).hasWon = true;
            setNextMessage("Black win " + cpp2::impl::as_<std::string>(engine.blackPoint) + " to " + cpp2::impl::as_<std::string>(engine.whitePoint) + ".5.");
        }
        else {
            (*cpp2::impl::assert_not_null(player2)).hasWon = true;
            setNextMessage("White win " + cpp2::impl::as_<std::string>(engine.whitePoint) + ".5 to " + cpp2::impl::as_<std::string>(engine.blackPoint) + ".");
        }
        auto stop {std::chrono::high_resolution_clock::now()}; 
        auto duration {CPP2_UFCS(count)(std::chrono::duration_cast<std::chrono::milliseconds>(cpp2::move(stop) - cpp2::move(start)))}; 
        setNextMessage("The game lasted " + cpp2::impl::as_<std::string>(cpp2::move(duration)) + " ms.");
        setNextMessage("After " + cpp2::impl::as_<std::string>(engine.goban.iterations) + " iterations.");
        clear();
        printGoban(cpp2::move(engine).goban);
    }
#endif

