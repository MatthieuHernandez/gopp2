
#ifndef RANDOM_H_CPP2
#define RANDOM_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/random.h2"

#line 3 "../src/random.h2"
class Random;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/random.h2"
#include "player.h"

#line 3 "../src/random.h2"
class Random: public Player {

#line 6 "../src/random.h2"
           public: Random(Interface* i, cpp2::impl::in<Color> c);

#line 10 "../src/random.h2"
    public: Random(Random const& that);

#line 14 "../src/random.h2"
    private: template<cpp2::i8 Size> [[nodiscard]] auto getMove(Engine<Size>& engine) & -> Move;

#line 24 "../src/random.h2"
    public: [[nodiscard]] auto getMove(Engine<9>& engine) -> Move override;

#line 28 "../src/random.h2"
    public: [[nodiscard]] auto getMove(Engine<19>& engine) -> Move override;

#line 31 "../src/random.h2"
};

#endif
