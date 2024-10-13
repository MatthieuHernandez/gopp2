
#ifndef ENGINE_H_CPP2
#define ENGINE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/engine.h2"

#line 3 "../src/engine.h2"
class Engine;


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/engine.h2"
#include "move.h"

#line 3 "../src/engine.h2"
class Engine {

    public: std::array<cpp2::i16,361> goban_state {0}; 
    public: std::vector<Move> moves; 

    public: auto start() & -> void;

#line 11 "../src/engine.h2"
    public: auto playMove(cpp2::impl::in<Move> m) & -> void;

#line 18 "../src/engine.h2"
    public: [[nodiscard]] auto isFinish() const& -> bool;
    public: Engine() = default;
    public: Engine(Engine const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Engine const&) -> void = delete;


#line 27 "../src/engine.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/engine.h2"

#line 8 "../src/engine.h2"
    auto Engine::start() & -> void{
    }

#line 11 "../src/engine.h2"
    auto Engine::playMove(cpp2::impl::in<Move> m) & -> void{
        CPP2_UFCS(push_back)(moves, m);
        cpp2::i16 i {0}; 
        i = (CPP2_ASSERT_IN_BOUNDS_LITERAL(m.position, 0) - 1) * 19 + CPP2_ASSERT_IN_BOUNDS_LITERAL(m.position, 1) - 1;
        CPP2_ASSERT_IN_BOUNDS(goban_state, i) = m.color;
    }

#line 18 "../src/engine.h2"
    [[nodiscard]] auto Engine::isFinish() const& -> bool{
        if (cpp2::impl::cmp_greater(CPP2_UFCS(ssize)(moves),1)) {
            if (CPP2_ASSERT_IN_BOUNDS(moves, CPP2_UFCS(size)(moves) - 1).pass == true 
            && CPP2_ASSERT_IN_BOUNDS(moves, CPP2_UFCS(size)(moves) - 2).pass == true) {
                return true; 
            }
        }
        return false; 
    }
#endif

