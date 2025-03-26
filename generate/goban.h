
#ifndef GOBAN_H_CPP2
#define GOBAN_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/goban.h2"

#line 5 "../src/goban.h2"
template<cpp2::i8 Size> class Goban;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/goban.h2"
#include "stone.h"

#line 3 "../src/goban.h2"
template<typename T, cpp2::i8 Size> using State = std::array<std::array<T,Size>,Size>;

template<cpp2::i8 Size> class Goban {
    public: State<Stone,Size> state {}; 
    public: Stone lockedPosition {}; 
    public: cpp2::i32 iterations {0}; 
    private: cpp2::i8 maxIndex {Size - 1}; 

    public: explicit Goban();

#line 25 "../src/goban.h2"
           public: [[nodiscard]] auto getAdjacentStone(cpp2::impl::in<Stone> s, cpp2::impl::in<State<bool,Size>> processedStones, cpp2::impl::in<bool> count = true) & -> std::vector<Stone>;

#line 45 "../src/goban.h2"
    public: [[nodiscard]] auto isTrueEye(cpp2::impl::in<Stone> s) const& -> bool;

#line 76 "../src/goban.h2"
    public: auto removeStone(cpp2::impl::in<Stone> s) & -> void;

#line 80 "../src/goban.h2"
    public: [[nodiscard]] auto isLockedPosition(cpp2::impl::in<Stone> s) const& -> bool;

#line 85 "../src/goban.h2"
    public: auto lockPosition(cpp2::impl::in<Stone> s, cpp2::impl::in<Color> c) & -> void;

#line 90 "../src/goban.h2"
    public: auto unlockPosition() & -> void;
    public: Goban(Goban const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Goban const&) -> void = delete;


#line 95 "../src/goban.h2"
};

#endif
