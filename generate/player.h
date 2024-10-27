
#ifndef PLAYER_H_CPP2
#define PLAYER_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/player.h2"

#line 4 "../src/player.h2"
class Player;
    

#line 19 "../src/player.h2"
class Human;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/player.h2"
#include "move.h"
#include "io.h"

#line 4 "../src/player.h2"
class Player {
    public: Color color; 

    public: [[nodiscard]] virtual auto getMove() const -> Move = 0;

    public: explicit Player(cpp2::impl::in<Color> c);

#line 13 "../src/player.h2"
    // CPP2 workaround: Default operator seems not working.
    public: Player(Player const& that);

#line 17 "../src/player.h2"
};

class Human: public Player {

#line 22 "../src/player.h2"
    public: explicit Human(cpp2::impl::in<Color> c);

#line 26 "../src/player.h2"
    public: Human(Human const& that);

#line 30 "../src/player.h2"
    public: [[nodiscard]] auto getMove() const -> Move override;

#line 33 "../src/player.h2"
};

#line 1 "../src/player.h2"

//=== Cpp2 function definitions =================================================

#line 1 "../src/player.h2"

#line 9 "../src/player.h2"
    Player::Player(cpp2::impl::in<Color> c)
        : color{ c }{

#line 11 "../src/player.h2"
    }

#line 14 "../src/player.h2"
    Player::Player(Player const& that)
        : color{ that.color }{

#line 16 "../src/player.h2"
    }

#line 22 "../src/player.h2"
    Human::Human(cpp2::impl::in<Color> c)
        : Player{ c }{

#line 24 "../src/player.h2"
    }

#line 26 "../src/player.h2"
    Human::Human(Human const& that)
        : Player{ that }{

#line 28 "../src/player.h2"
    }

#line 30 "../src/player.h2"
    [[nodiscard]] auto Human::getMove() const -> Move{
        return getInputMove(color); 
    }
#endif

