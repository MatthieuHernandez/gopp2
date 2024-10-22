
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

#line 28 "../src/engine.h2"
    private: auto countLiberties(Stone& stone, cpp2::i16& count) & -> void;

#line 44 "../src/engine.h2"
    public: [[nodiscard]] auto numberOfLiberties(Stone& stone) & -> cpp2::i16;

#line 52 "../src/engine.h2"
    public: auto capture(Stone& stone, cpp2::impl::in<Color> color, cpp2::i16& count) & -> void;

#line 73 "../src/engine.h2"
    public: [[nodiscard]] auto captureStones(Stone& stone) & -> cpp2::i16;

#line 84 "../src/engine.h2"
    public: [[nodiscard]] auto isValidMove(Move& m) & -> bool;

#line 102 "../src/engine.h2"
    public: [[nodiscard]] auto isFinish() const& -> bool;
    public: Engine(Engine const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Engine const&) -> void = delete;


#line 112 "../src/engine.h2"
    /*countPoints(): int16 = {

    }*/
#line 115 "../src/engine.h2"
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
            CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, cpp2::move(col)), row) = m.stone;
            if (goban.lockedPosition.color == m.stone.color) {
                CPP2_UFCS(unlockPosition)(goban);
                std::cout << "Stone unlockled." << std::endl;
            }
            nextMovePlayer = otherColor(nextMovePlayer);
        }
    }

#line 28 "../src/engine.h2"
    auto Engine::countLiberties(Stone& stone, cpp2::i16& count) & -> void{
        CPP2_UFCS(processStone)(goban, stone);
        auto nextStones {CPP2_UFCS(getAdjacentStone)(goban, stone)}; 
        for ( 
        auto& nextStone : cpp2::move(nextStones) ) {
            if (!(CPP2_UFCS(stonehasBeenProcessed)(goban, nextStone))) {
                if (nextStone.color == Color::None) {
                    CPP2_UFCS(processStone)(goban, nextStone);
                    ++count;
                }else {if (nextStone.color == stone.color) {
                    countLiberties(nextStone, count);
                }}
            }
        }
    }

#line 44 "../src/engine.h2"
    [[nodiscard]] auto Engine::numberOfLiberties(Stone& stone) & -> cpp2::i16{
        cpp2::i16 count {0}; 
        CPP2_UFCS(clearProcessedStone)(goban);
        countLiberties(stone, count);
        CPP2_UFCS(clearProcessedStone)(goban);
        return count; 
    }

#line 52 "../src/engine.h2"
    auto Engine::capture(Stone& stone, cpp2::impl::in<Color> color, cpp2::i16& count) & -> void{
        auto nextStones {CPP2_UFCS(getAdjacentStone)(goban, stone)}; 
        for ( 
        auto& nextStone : cpp2::move(nextStones) ) {
            if (nextStone.color == color) {
                auto l {numberOfLiberties(nextStone)}; 
                if (cpp2::move(l) == 1) {
                    count = count + 0;
                    CPP2_UFCS(removeStone)(goban, nextStone);
                    ++count;
                    if (count == 1) {
                        //o:= otherColor(color);
                        CPP2_UFCS(lockPosition)(goban, nextStone, color);
                        std::cout << "Stone " << cpp2::impl::as_<std::string>(nextStone.col) << ", " << cpp2::impl::as_<std::string>(nextStone.row) << "    " << cpp2::impl::as_<cpp2::i32>(goban.lockedPosition.color) << " locked." << std::endl;
                    }
                    capture(nextStone, color, count);
                }
            }
        }
    }

#line 73 "../src/engine.h2"
    [[nodiscard]] auto Engine::captureStones(Stone& stone) & -> cpp2::i16{
        cpp2::i16 count {0}; 
        auto color {otherColor(stone.color)}; 
        capture(stone, cpp2::move(color), count);
        if (cpp2::impl::cmp_greater(count,1)) {
            CPP2_UFCS(unlockPosition)(goban);
            std::cout << "Stone unlockled." << std::endl;
        }
        return count; 
    }

#line 84 "../src/engine.h2"
    [[nodiscard]] auto Engine::isValidMove(Move& m) & -> bool{
        if (m.pass) {
            return true; 
        }
        auto col {m.stone.col}; 
        auto row {m.stone.row}; 
        std::cout << "Check stone " << cpp2::impl::as_<std::string>(m.stone.col) << ", " << cpp2::impl::as_<std::string>(m.stone.row) << "    " << cpp2::impl::as_<cpp2::i32>(goban.lockedPosition.color) << " locked." << std::endl;
        if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row).color == Color::None && 
            (goban.lockedPosition.col != col || goban.lockedPosition.row != row)) {
            auto numberOfcapturedStones {captureStones(m.stone)}; 
            if (cpp2::impl::cmp_greater(numberOfLiberties(m.stone),0) || 
                cpp2::impl::cmp_greater(cpp2::move(numberOfcapturedStones),0)) {
                return true; 
            }
        }
        return false; 
    }

#line 102 "../src/engine.h2"
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

