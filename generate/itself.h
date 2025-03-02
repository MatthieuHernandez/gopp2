
#ifndef ITSELF_H_CPP2
#define ITSELF_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/itself.h2"

#line 4 "../src/itself.h2"
class Itself;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/itself.h2"
#include "player.h"
#include "ai.h"

#line 4 "../src/itself.h2"
class Itself: public Player {

    public: Ai ai; 

    public: Itself(cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> r, cpp2::impl::in<Ai> aiToCopy);

#line 13 "../src/itself.h2"
    public: virtual auto setColor(cpp2::impl::in<Color> c) -> void;

#line 18 "../src/itself.h2"
    public: [[nodiscard]] virtual auto getMove(Engine<9>& engine) -> Move;

#line 22 "../src/itself.h2"
    public: [[nodiscard]] virtual auto getMove(Engine<19>& engine) -> Move;
    public: Itself(Itself const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Itself const&) -> void = delete;


#line 25 "../src/itself.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/itself.h2"

#line 8 "../src/itself.h2"
    Itself::Itself(cpp2::impl::in<Color> c, cpp2::impl::in<cpp2::i16> r, cpp2::impl::in<Ai> aiToCopy)
         : Player{ c }
         , ai{ Ai(c, r, aiToCopy) }{

#line 11 "../src/itself.h2"
    }

#line 13 "../src/itself.h2"
    auto Itself::setColor(cpp2::impl::in<Color> c) -> void{
        color = c;
        CPP2_UFCS(setColor)(ai, c);
    }

#line 18 "../src/itself.h2"
    [[nodiscard]] auto Itself::getMove(Engine<9>& engine) -> Move{
        return CPP2_UFCS(getMove)(ai, engine); 
    }

#line 22 "../src/itself.h2"
    [[nodiscard]] auto Itself::getMove(Engine<19>& engine) -> Move{
        return CPP2_UFCS(getMove)(ai, engine); 
    }
#endif

