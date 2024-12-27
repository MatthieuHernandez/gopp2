
#ifndef GAME_H_CPP2
#define GAME_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/game.h2"

#line 11 "../src/game.h2"
class Game;


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/game.h2"
#include "engine.h"
#include "move.h"
#include "io.h"
#include "player.h"
#include "human.h"
#include "random.h"
#include "ai.h"

#line 9 "../src/game.h2"
extern bool isSaving;

class Game {

    private: std::shared_ptr<Player> blackPlayer {nullptr}; // CPP2 workaround: Not able to make unique_prtr work.
    private: std::shared_ptr<Player> whitePlayer {nullptr}; 

    private: [[nodiscard]] static auto selectPlayer(cpp2::impl::in<Color> color) -> std::shared_ptr<Player>;

#line 35 "../src/game.h2"
    public: auto selectPlayers() & -> void;

#line 41 "../src/game.h2"
    private: [[nodiscard]] auto hasValidPlayer() const& -> bool;

#line 49 "../src/game.h2"
    private: template<bool verbose> auto play() & -> void;

#line 100 "../src/game.h2"
    public: auto playOne() & -> void;

#line 109 "../src/game.h2"
    private: auto switchPlayerColor() & -> void;

#line 115 "../src/game.h2"
    public: auto trainBlack() & -> void;

#line 140 "../src/game.h2"
    public: auto evaluate() & -> void;
    public: Game() = default;
    public: Game(Game const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Game const&) -> void = delete;


#line 169 "../src/game.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/game.h2"

#line 9 "../src/game.h2"
bool isSaving {false}; 

#line 16 "../src/game.h2"
    [[nodiscard]] auto Game::selectPlayer(cpp2::impl::in<Color> color) -> std::shared_ptr<Player>{
        auto selection {printPlayersAndSelect(color)}; 
        if ((selection == "")) {
            return nullptr; 
        }
        if ((selection == "0")) {
            return CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, color); 
        }
        if ((selection == "1")) {
            return CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, color); 
        }
        auto ai {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, color, cpp2::move(selection))}; 
        clear();
        std::cout << CPP2_UFCS(summary)((*cpp2::impl::assert_not_null(ai))) << std::endl;
        waitInput();
        clear();
        return ai; 
    }

#line 35 "../src/game.h2"
    auto Game::selectPlayers() & -> void{
        blackPlayer = selectPlayer(Color::Black);
        whitePlayer = selectPlayer(Color::White);
        setNextMessage("Players selected.");
    }

#line 41 "../src/game.h2"
    [[nodiscard]] auto Game::hasValidPlayer() const& -> bool{
        if (blackPlayer == nullptr || whitePlayer == nullptr) {
            setNextMessage("No player selected.");
            return false; 
        }
        return true; 
    }

#line 49 "../src/game.h2"
    template<bool verbose> auto Game::play() & -> void{
        auto start {std::chrono::high_resolution_clock::now()}; 
        Engine engine {}; 
        cpp2::i16 moveNumber {1}; 
        do {
            if constexpr (verbose) {
                clear();
                printGoban(engine.goban);
            }
            Move m {};    // CPP2 workaround: Not able to make unique_prtr work.
            if (moveNumber % 2 == 1) {
                m = CPP2_UFCS(getMove)((*cpp2::impl::assert_not_null(blackPlayer)), engine);
            }else {
                m = CPP2_UFCS(getMove)((*cpp2::impl::assert_not_null(whitePlayer)), engine);
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
            (*cpp2::impl::assert_not_null(blackPlayer)).hasWon = true;
            (*cpp2::impl::assert_not_null(whitePlayer)).hasWon = false;
            setNextMessage("Black win " + cpp2::impl::as_<std::string>(engine.blackPoint) + " to " + cpp2::impl::as_<std::string>(engine.whitePoint) + ".5.");
        }else {
            (*cpp2::impl::assert_not_null(whitePlayer)).hasWon = true;
            (*cpp2::impl::assert_not_null(blackPlayer)).hasWon = false;
            setNextMessage("White win " + cpp2::impl::as_<std::string>(engine.whitePoint) + ".5 to " + cpp2::impl::as_<std::string>(engine.blackPoint) + ".");
        }
        auto stop {std::chrono::high_resolution_clock::now()}; 
        auto duration {CPP2_UFCS(count)(std::chrono::duration_cast<std::chrono::milliseconds>(cpp2::move(stop) - cpp2::move(start)))}; 
        setNextMessage("The game lasted " + cpp2::impl::as_<std::string>(cpp2::move(duration)) + " ms.");
        setNextMessage("After " + cpp2::impl::as_<std::string>(engine.goban.iterations) + " iterations.");
        CPP2_UFCS(processEndGame)((*cpp2::impl::assert_not_null(blackPlayer)));
        CPP2_UFCS(processEndGame)((*cpp2::impl::assert_not_null(whitePlayer)));
        clear();
        printGoban(cpp2::move(engine).goban);
    }

#line 100 "../src/game.h2"
    auto Game::playOne() & -> void{
        if (!(hasValidPlayer())) {
            return ; 
        }
        play<true>();
        waitInput();
        setNextMessage("Game was played.");
    }

#line 109 "../src/game.h2"
    auto Game::switchPlayerColor() & -> void{
        (*cpp2::impl::assert_not_null(blackPlayer)).color = Color::White;
        (*cpp2::impl::assert_not_null(whitePlayer)).color = Color::Black;
        std::swap(blackPlayer, whitePlayer);
    }

#line 115 "../src/game.h2"
    auto Game::trainBlack() & -> void{
        if (!(hasValidPlayer())) {
            return ; 
        }
        auto player1 {std::dynamic_pointer_cast<Ai>(blackPlayer)}; // CPP2 workaround: keyword "as" not working.
        if (player1 == nullptr) {
            setNextMessage("Black player should be an AI.");
            return ; 
        }
        cpp2::i32 i {0}; 
        while( true ) 
        {
            play<false>();
            CPP2_UFCS(train)((*cpp2::impl::assert_not_null(player1)));
            switchPlayerColor();
            if (i % 20 == 0) {
                isSaving = true;
                CPP2_UFCS(save)((*cpp2::impl::assert_not_null(player1)));
                isSaving = false;
            }
            ++i;
        }
        setNextMessage("AI trained.");
    }

#line 140 "../src/game.h2"
    auto Game::evaluate() & -> void{
        if (!(hasValidPlayer())) {
            return ; 
        }
        auto blackHuman {std::dynamic_pointer_cast<Human>(blackPlayer)}; // CPP2 workaround: keyword "as" not working.
        auto whiteHuman {std::dynamic_pointer_cast<Human>(blackPlayer)}; 
        if (cpp2::move(blackHuman) != nullptr || cpp2::move(whiteHuman) != nullptr) {
            setNextMessage("Cannot evaluated with human players.");
            return ; 
        }
        auto player1 {blackPlayer}; 
        cpp2::i16 numberOfGame {100}; 
        cpp2::i16 numberOfGameWon {0}; 
        clear();
{
cpp2::i32 i{0};

#line 155 "../src/game.h2"
        for( ; cpp2::impl::cmp_less(i,numberOfGame); 
        ++i ) 
        {
            if (i == (numberOfGame / CPP2_ASSERT_NOT_ZERO_LITERAL(CPP2_TYPEOF(numberOfGame),2))) {
                switchPlayerColor();
            }
            play<false>();
            if ((*cpp2::impl::assert_not_null(player1)).hasWon) {
                ++numberOfGameWon;
            }
        }
}
#line 166 "../src/game.h2"
        setNextMessage("The first player won " + cpp2::impl::as_<std::string>(cpp2::move(numberOfGameWon)) + 
                    "/" + cpp2::impl::as_<std::string>(cpp2::move(numberOfGame)) + " games againt the 2nd player.");
    }
#endif

