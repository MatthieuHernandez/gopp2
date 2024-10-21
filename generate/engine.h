
#ifndef ENGINE_H_CPP2
#define ENGINE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/engine.h2"

#line 4 "../src/engine.h2"
class Engine;


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/engine.h2"
#include "goban.h"
#include "move.h"

#line 4 "../src/engine.h2"
class Engine {

    public: Goban goban {}; 
    public: std::vector<Move> moves {}; 
    public: Color nextMovePlayer; 

   public: explicit Engine();

#line 14 "../src/engine.h2"
    public: auto playMove(cpp2::impl::in<Move> m) & -> void;

#line 26 "../src/engine.h2"
    public: auto countLiberties(Stone& stone, auto& count) & -> void;

#line 42 "../src/engine.h2"
    public: [[nodiscard]] auto numberOfLiberties(Stone& stone) & -> cpp2::i16;

#line 49 "../src/engine.h2"
    public: [[nodiscard]] auto isValidMove(Move& m) & -> bool;

#line 62 "../src/engine.h2"
    public: [[nodiscard]] static auto captureStone() -> bool;

#line 66 "../src/engine.h2"
    public: [[nodiscard]] auto isFinish() const& -> bool;
    public: Engine(Engine const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Engine const&) -> void = delete;


#line 75 "../src/engine.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/engine.h2"

#line 10 "../src/engine.h2"
   Engine::Engine()
        : nextMovePlayer{ Color::Black }{

#line 12 "../src/engine.h2"
    }

#line 14 "../src/engine.h2"
    auto Engine::playMove(cpp2::impl::in<Move> m) & -> void{
        CPP2_UFCS(push_back)(moves, m);
        if (!(m.pass)) {
            auto col {m.stone.col}; 
            auto row {m.stone.row}; 
            CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row) = m.stone;
            std::cout << "The stone is " << cpp2::impl::as_<cpp2::i32>(m.stone.color) << std::endl;
            std::cout << "The stone is " <<  cpp2::impl::as_<cpp2::i32>(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, cpp2::move(col)), cpp2::move(row)).color) << std::endl;
            //switchPlayer(nextMovePlayer);
        }
    }

#line 26 "../src/engine.h2"
    auto Engine::countLiberties(Stone& stone, auto& count) & -> void{
        auto nextStones {CPP2_UFCS(getAdjacentStone)(goban, stone)}; 
        for ( 
        auto& nextStone : cpp2::move(nextStones) ) 
        {
            if (nextStone.color == Color::None && !(nextStone.hasBeenProcessed)) {
                nextStone.hasBeenProcessed = true;
                ++count;
            }else {if (nextStone.color == stone.color && !(nextStone.hasBeenProcessed)) {
                nextStone.hasBeenProcessed = true;
                countLiberties(nextStone, count);
            }}
        }
        stone.hasBeenProcessed = true;
    }

#line 42 "../src/engine.h2"
    [[nodiscard]] auto Engine::numberOfLiberties(Stone& stone) & -> cpp2::i16{
        auto count {0}; 
        countLiberties(stone, count);
        CPP2_UFCS(clearProcessedStone)(goban);
        return count; 
    }

#line 49 "../src/engine.h2"
    [[nodiscard]] auto Engine::isValidMove(Move& m) & -> bool{
        if (m.pass) {
            return true; 
        }
        auto col {m.stone.col}; 
        auto row {m.stone.row}; 
        if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, cpp2::move(col)), cpp2::move(row)).color == Color::None && 
            (cpp2::impl::cmp_greater(numberOfLiberties(m.stone),0) || captureStone() == true)) {
            return true; 
        }
        return false; 
    }

#line 62 "../src/engine.h2"
    [[nodiscard]] auto Engine::captureStone() -> bool{
        return false; 
    }

#line 66 "../src/engine.h2"
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

