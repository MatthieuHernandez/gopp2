
#ifndef HUMAN_H_CPP2
#define HUMAN_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/human.h2"

#line 3 "../src/human.h2"
class Human;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/human.h2"
#include "player.h"

#line 3 "../src/human.h2"
class Human: public Player {

#line 6 "../src/human.h2"
    public: Human(cpp2::impl::in<Color> c);

#line 10 "../src/human.h2"
    public: Human(Human const& that);

#line 14 "../src/human.h2"
    public: [[nodiscard]] auto getMove([[maybe_unused]] Engine<9>& unnamed_param_2) -> Move override;

#line 18 "../src/human.h2"
    public: [[nodiscard]] auto getMove([[maybe_unused]] Engine<19>& unnamed_param_2) -> Move override;

#line 21 "../src/human.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/human.h2"

#line 6 "../src/human.h2"
    Human::Human(cpp2::impl::in<Color> c)
        : Player{ c }{

#line 8 "../src/human.h2"
    }

#line 10 "../src/human.h2"
    Human::Human(Human const& that)
        : Player{ that }{

#line 12 "../src/human.h2"
    }

#line 14 "../src/human.h2"
    [[nodiscard]] auto Human::getMove([[maybe_unused]] Engine<9>& unnamed_param_2) -> Move{
        return getInputMove<9>(color); 
    }

#line 18 "../src/human.h2"
    [[nodiscard]] auto Human::getMove([[maybe_unused]] Engine<19>& unnamed_param_2) -> Move{
        return getInputMove<19>(color); 
    }
#endif

