
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

#line 7 "../src/player.h2"
extern std::random_device rd;
extern std::mt19937 rng;

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

    public: [[nodiscard]] virtual auto getMove(Engine<13>& engine) -> Move = 0;

    public: [[nodiscard]] virtual auto getMove(Engine<19>& engine) -> Move = 0;

    // CPP2 workaround: Default operator seems not working.
    public: Player(Player const& that);

#line 41 "../src/player.h2"
    // CPP2 workaround: Default operator seems not working.
    public: virtual ~Player() noexcept;

#line 45 "../src/player.h2"
    public: virtual auto processStartGame() -> void;

    public: virtual auto processEndGame() -> void;
};

#endif
