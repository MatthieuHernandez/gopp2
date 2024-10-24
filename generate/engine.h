
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

    public: cpp2::i16 blackPoint {0}; 
    public: cpp2::i16 whitePoint {0}; 

   public: explicit Engine();

#line 17 "../src/engine.h2"
    public: auto playMove(cpp2::impl::in<Move> m) & -> void;

#line 31 "../src/engine.h2"
    private: auto countLiberties(Stone& stone, cpp2::i16& count) & -> void;

#line 47 "../src/engine.h2"
    public: [[nodiscard]] auto numberOfLiberties(Stone& stone) & -> cpp2::i16;

#line 55 "../src/engine.h2"
    public: auto removeGroup(Stone& stone, cpp2::i16& count) & -> void;

#line 70 "../src/engine.h2"
    public: [[nodiscard]] auto captureStones(Stone& stone) & -> cpp2::i16;

#line 96 "../src/engine.h2"
    public: [[nodiscard]] auto isValidMove(Move& m) & -> bool;

#line 113 "../src/engine.h2"
    public: [[nodiscard]] auto isFinish() const& -> bool;

#line 123 "../src/engine.h2"
    public: auto countTerritory(Stone& stone, cpp2::i16& count, Color& color) & -> void;

#line 149 "../src/engine.h2"
    public: auto countScore() & -> void;
    public: Engine(Engine const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Engine const&) -> void = delete;


#line 184 "../src/engine.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/engine.h2"

#line 13 "../src/engine.h2"
   Engine::Engine()
        : nextMovePlayer{ Color::Black }{

#line 15 "../src/engine.h2"
    }

#line 17 "../src/engine.h2"
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
        }
        nextMovePlayer = otherColor(nextMovePlayer);
    }

#line 31 "../src/engine.h2"
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

#line 47 "../src/engine.h2"
    [[nodiscard]] auto Engine::numberOfLiberties(Stone& stone) & -> cpp2::i16{
        CPP2_UFCS(clearProcessedStone)(goban);
        cpp2::i16 count {0}; 
        countLiberties(stone, count);
        CPP2_UFCS(clearProcessedStone)(goban);
        return count; 
    }

#line 55 "../src/engine.h2"
    auto Engine::removeGroup(Stone& stone, cpp2::i16& count) & -> void{
        auto nextStones {CPP2_UFCS(getAdjacentStone)(goban, stone)}; 
        for ( 
        auto& nextStone : cpp2::move(nextStones) ) {
            std::cout << "stone.color " << cpp2::impl::as_<cpp2::i32>(stone.color) << std::endl;
            std::cout << "nextStone.color " << cpp2::impl::as_<cpp2::i32>(nextStone.color) << std::endl;
            if (nextStone.color == stone.color) {
                CPP2_UFCS(removeStone)(goban, nextStone);
                std::cout << "nextStone removed" << std::endl;
                ++count;
                removeGroup(nextStone, count);
            }
        }
    }

#line 70 "../src/engine.h2"
    [[nodiscard]] auto Engine::captureStones(Stone& stone) & -> cpp2::i16{
        CPP2_UFCS(clearProcessedStone)(goban);
        cpp2::i16 count {0}; 
        auto color {otherColor(stone.color)}; 
        auto nextStones {CPP2_UFCS(getAdjacentStone)(goban, stone)}; 
        for ( 
        auto& nextStone : cpp2::move(nextStones) ) {
            if (nextStone.color == color) {
                auto l {numberOfLiberties(nextStone)}; 
                if (cpp2::move(l) == 1) {
                    std::cout << "Remove group." << std::endl;
                    removeGroup(nextStone, count);
                    CPP2_UFCS(removeStone)(goban, nextStone);
                    ++count;
                    if (count == 1) {
                        CPP2_UFCS(lockPosition)(goban, nextStone, color);
                    }
                }
            }
        }
        if (cpp2::impl::cmp_greater(count,1)) {
            CPP2_UFCS(unlockPosition)(goban);
        }
        return count; 
    }

#line 96 "../src/engine.h2"
    [[nodiscard]] auto Engine::isValidMove(Move& m) & -> bool{
        if (m.pass) {
            return true; 
        }
        auto col {m.stone.col}; 
        auto row {m.stone.row}; 
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

#line 113 "../src/engine.h2"
    [[nodiscard]] auto Engine::isFinish() const& -> bool{
        if (cpp2::impl::cmp_greater(CPP2_UFCS(ssize)(moves),1)) {
            if (CPP2_ASSERT_IN_BOUNDS(moves, CPP2_UFCS(size)(moves) - 1).pass == true 
            && CPP2_ASSERT_IN_BOUNDS(moves, CPP2_UFCS(size)(moves) - 2).pass == true) {
                return true; 
            }
        }
        return false; 
    }

#line 123 "../src/engine.h2"
    auto Engine::countTerritory(Stone& stone, cpp2::i16& count, Color& color) & -> void{
        if (count == 0) {
            return ; 
        }
        auto nextStones {CPP2_UFCS(getAdjacentStone)(goban, stone)}; 
        for ( 
        auto& nextStone : cpp2::move(nextStones) ) {
            if (nextStone.color == Color::None) {
                if (CPP2_UFCS(stonehasBeenProcessed)(goban, nextStone) == false) {
                    CPP2_UFCS(processStone)(goban, nextStone);
                    ++count;
                    countTerritory(nextStone, count, color);
                }
            }
            else {if (nextStone.color == Color::Black && color != Color::White) {
                color = Color::Black;
            }
            else {if (nextStone.color == Color::White && color != Color::Black) {
                color = Color::White;
            }else {
                count = 0;
                return ; 
            }}}
        }
    }

#line 149 "../src/engine.h2"
    auto Engine::countScore() & -> void{
        CPP2_UFCS(clearProcessedStone)(goban);
        blackPoint = 0;
        whitePoint = 7;
{
cpp2::i8 col{0};

#line 154 "../src/engine.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(goban.state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 158 "../src/engine.h2"
            for( ; cpp2::impl::cmp_less(row,CPP2_UFCS(ssize)(CPP2_ASSERT_IN_BOUNDS(goban.state, col))); 
            ++row ) 
            {
                if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row).hasBeenProcessed == false) {
                    CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row).hasBeenProcessed = true;
                    if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row).color == Color::Black) {
                        ++blackPoint;
                    }
                    else {if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row).color == Color::White) {
                        ++whitePoint;
                    }
                    else {
                        cpp2::i16 count {1}; 
                        auto color {Color::None}; 
                        countTerritory(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row), count, color);
                        if (color == Color::Black) {
                            blackPoint += count;
                        }
                        if (cpp2::move(color) == Color::White) {
                            whitePoint += cpp2::move(count);
                        }
                    }}
                }
            }
}
#line 182 "../src/engine.h2"
        }
}
#line 183 "../src/engine.h2"
    }
#endif

