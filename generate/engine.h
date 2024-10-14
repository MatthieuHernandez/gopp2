
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
    public: std::vector<Move> moves {}; 
    public: Color nextMovePlayer; 

   public: explicit Engine();

#line 13 "../src/engine.h2"
    public: auto playMove(cpp2::impl::in<Move> m) & -> void;

#line 22 "../src/engine.h2"
    public: [[nodiscard]] auto isValidMove(cpp2::impl::in<Move> m) & -> bool;

#line 32 "../src/engine.h2"
    public: [[nodiscard]] auto isFinish() const& -> bool;
    public: Engine(Engine const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Engine const&) -> void = delete;


#line 41 "../src/engine.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/engine.h2"

#line 9 "../src/engine.h2"
   Engine::Engine()
        : nextMovePlayer{ Color::Black }{

#line 11 "../src/engine.h2"
    }

#line 13 "../src/engine.h2"
    auto Engine::playMove(cpp2::impl::in<Move> m) & -> void{
        CPP2_UFCS(push_back)(moves, m);
        if (!(m.pass)) {
            cpp2::i16 i {CPP2_UFCS(getFlattenPosition)(m)}; 
            CPP2_ASSERT_IN_BOUNDS(goban_state, i) = m.color;
            switchPlayer(nextMovePlayer);
        }
    }

#line 22 "../src/engine.h2"
    [[nodiscard]] auto Engine::isValidMove(cpp2::impl::in<Move> m) & -> bool{
        if (!(m.pass)) {
            cpp2::i16 i {CPP2_UFCS(getFlattenPosition)(m)}; 
            if (CPP2_ASSERT_IN_BOUNDS(goban_state, cpp2::move(i)) != 0) {
                return false; 
            }
        }
        return true; 
    }

#line 32 "../src/engine.h2"
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

