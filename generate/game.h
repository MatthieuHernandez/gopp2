
#ifndef GAME_H_CPP2
#define GAME_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/game.h2"

#line 10 "../src/game.h2"
class Game;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/game.h2"
#include "engine.h"
#include "move.h"
#include "player.h"
#include "human.h"
#include "dumb.h"
#include "random.h"
#include "ai.h"
#include "itself.h"

#line 10 "../src/game.h2"
class Game {
    private: bool isSaving {false}; 
    private: Interface* interface; 
    private: std::shared_ptr<Player> blackPlayer {nullptr}; // CPP2 workaround: Not able to make unique_ptr work.
    private: std::shared_ptr<Player> whitePlayer {nullptr}; 
    private: cpp2::i8 gobanSize {9}; 

    public: Game(Interface* i);
#line 17 "../src/game.h2"
    public: auto operator=(Interface* i) -> Game& ;

#line 21 "../src/game.h2"
    public: [[nodiscard]] auto canBeStopped() const& -> bool;

#line 25 "../src/game.h2"
    public: [[nodiscard]] auto getGobanSize() const& -> cpp2::i8;

#line 29 "../src/game.h2"
    public: auto setGobanSize(cpp2::impl::in<cpp2::i8> size) & -> void;

#line 33 "../src/game.h2"
    private: [[nodiscard]] static auto getPlayerName(cpp2::impl::in<std::shared_ptr<Player>> player) -> std::string;

#line 57 "../src/game.h2"
    public: [[nodiscard]] auto getPlayerNames() const& -> std::string;

#line 63 "../src/game.h2"
    public: auto selectPlayer(cpp2::impl::in<Color> color, cpp2::impl::in<std::string> selection) & -> void;

#line 92 "../src/game.h2"
    private: [[nodiscard]] auto hasValidPlayer() const& -> bool;

#line 100 "../src/game.h2"
    private: auto setAiRandomness(cpp2::impl::in<cpp2::i16> r) & -> void;

#line 111 "../src/game.h2"
    private: template<bool verbose, cpp2::i8 Size> auto play(Engine<Size>& engine) & -> void;

#line 167 "../src/game.h2"
    public: auto playOne() & -> void;

#line 186 "../src/game.h2"
    private: auto switchPlayerColor() & -> void;

#line 192 "../src/game.h2"
    public: auto trainBlack() & -> void;

#line 229 "../src/game.h2"
    public: auto evaluate() & -> void;
    public: Game(Game const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Game const&) -> void = delete;


#line 270 "../src/game.h2"
};

                CPP2_UFCS(save)((*cpp2::impl::assert_not_null(player1)));
#endif
