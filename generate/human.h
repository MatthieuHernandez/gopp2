
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
    public: Human(Interface* i, cpp2::impl::in<Color> c);

#line 10 "../src/human.h2"
    public: Human(Human const& that);

#line 14 "../src/human.h2"
    public: [[nodiscard]] auto getMove([[maybe_unused]] Engine<9>& unnamed_param_2) -> Move override;

#line 18 "../src/human.h2"
    public: [[nodiscard]] auto getMove([[maybe_unused]] Engine<13>& unnamed_param_2) -> Move override;

#line 22 "../src/human.h2"
    public: [[nodiscard]] auto getMove([[maybe_unused]] Engine<19>& unnamed_param_2) -> Move override;

#line 25 "../src/human.h2"
};

#endif
