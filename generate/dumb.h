
#ifndef DUMB_H_CPP2
#define DUMB_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/dumb.h2"

#line 3 "../src/dumb.h2"
class Dumb;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/dumb.h2"
#include "player.h"

#line 3 "../src/dumb.h2"
class Dumb: public Player {

#line 6 "../src/dumb.h2"
    public: Dumb(Interface* i, cpp2::impl::in<Color> c);

#line 10 "../src/dumb.h2"
    public: Dumb(Dumb const& that);

#line 14 "../src/dumb.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto getMove(Engine<Size>& engine) & -> Move;

#line 20 "../src/dumb.h2"
    public: [[nodiscard]] auto getMove(Engine<9>& engine) -> Move override;

#line 24 "../src/dumb.h2"
    public: [[nodiscard]] auto getMove(Engine<19>& engine) -> Move override;

#line 27 "../src/dumb.h2"
};

#endif
