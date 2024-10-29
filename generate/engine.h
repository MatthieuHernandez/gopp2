
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

    public: cpp2::i16 blackPoint {0}; 
    public: cpp2::i16 whitePoint {0}; 

    public: auto playMove(cpp2::impl::in<Move> m) & -> void;

#line 24 "../src/engine.h2"
    private: auto countLiberties(Stone& stone, cpp2::i16& count, State<bool>& processedStones) & -> void;

#line 40 "../src/engine.h2"
    public: [[nodiscard]] auto numberOfLiberties(Stone& stone) & -> cpp2::i16;

#line 48 "../src/engine.h2"
    private: auto removeGroup(Stone& stone, cpp2::i16& count, State<bool>& processedStones) & -> void;

#line 61 "../src/engine.h2"
    public: [[nodiscard]] auto captureStones(Stone& stone) & -> cpp2::i16;

#line 86 "../src/engine.h2"
    public: [[nodiscard]] auto isValidMove(Move& m) & -> bool;

#line 104 "../src/engine.h2"
    public: [[nodiscard]] auto isFinish() const& -> bool;

#line 114 "../src/engine.h2"
    private: auto countTerritory(Stone& stone, cpp2::i16& count, Color& color, 
        State<bool>& processedStones1, State<bool>& processedStones2) & -> void;

#line 143 "../src/engine.h2"
    public: auto countScore() & -> void;

#line 181 "../src/engine.h2"
    private: auto findValidMove(Move& m, State<bool>& processedStones, cpp2::i32& count) & -> void;

#line 199 "../src/engine.h2"
    public: auto closerValidMove(Move& m) & -> void;
    public: Engine() = default;
    public: Engine(Engine const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Engine const&) -> void = delete;


#line 209 "../src/engine.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/engine.h2"

#line 12 "../src/engine.h2"
    auto Engine::playMove(cpp2::impl::in<Move> m) & -> void{
        CPP2_UFCS(push_back)(moves, m);
        if (!(m.pass)) {
            auto col {m.stone.col}; 
            auto row {m.stone.row}; 
            CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, cpp2::move(col)), row) = m.stone;
            if (goban.lockedPosition.color == m.stone.color) {
                CPP2_UFCS(unlockPosition)(goban);
            }
        }
    }

#line 24 "../src/engine.h2"
    auto Engine::countLiberties(Stone& stone, cpp2::i16& count, State<bool>& processedStones) & -> void{
        CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, stone.col), stone.row) = true;
        auto nextStones {CPP2_UFCS(getAdjacentStone)(goban, stone, processedStones)}; 
        for ( 
        auto& nextStone : cpp2::move(nextStones) ) {
            if (!(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, nextStone.col), nextStone.row))) {
                if (nextStone.color == Color::None) {
                    CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, nextStone.col), nextStone.row) = true;
                    ++count;
                }else {if (nextStone.color == stone.color) {
                    countLiberties(nextStone, count, processedStones);
                }}
            }
        }
    }

#line 40 "../src/engine.h2"
    [[nodiscard]] auto Engine::numberOfLiberties(Stone& stone) & -> cpp2::i16{
        State<bool> processedStones {}; 
        cpp2::i16 count {0}; 
        countLiberties(stone, count, processedStones);
        processedStones = processedStones;
        return count; 
    }

#line 48 "../src/engine.h2"
    auto Engine::removeGroup(Stone& stone, cpp2::i16& count, State<bool>& processedStones) & -> void{
        auto nextStones {CPP2_UFCS(getAdjacentStone)(goban, stone, processedStones)}; 
        for ( 
        auto& nextStone : cpp2::move(nextStones) ) {
            if (nextStone.color == stone.color) {
                CPP2_UFCS(removeStone)(goban, nextStone);
                CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, nextStone.col), nextStone.row) = true;
                ++count;
                removeGroup(nextStone, count, processedStones);
            }
        }
    }

#line 61 "../src/engine.h2"
    [[nodiscard]] auto Engine::captureStones(Stone& stone) & -> cpp2::i16{
        State<bool> processedStones {}; 
        cpp2::i16 count {0}; 
        auto color {otherColor(stone.color)}; 
        auto nextStones {CPP2_UFCS(getAdjacentStone)(goban, stone, processedStones)}; 
        for ( 
        auto& nextStone : cpp2::move(nextStones) ) {
            if (nextStone.color == color) {
                auto l {numberOfLiberties(nextStone)}; 
                if (cpp2::move(l) == 1) {
                    removeGroup(nextStone, count, processedStones);
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

#line 86 "../src/engine.h2"
    [[nodiscard]] auto Engine::isValidMove(Move& m) & -> bool{
        if (m.pass) {
            return true; 
        }
        auto col {m.stone.col}; 
        auto row {m.stone.row}; 
        if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, cpp2::move(col)), cpp2::move(row)).color == Color::None && 
            !(CPP2_UFCS(isLockedPosition)(goban, m.stone)) && 
            !(CPP2_UFCS(isTrueEye)(goban, m.stone))) {
            auto numberOfcapturedStones {captureStones(m.stone)}; 
            if (cpp2::impl::cmp_greater(numberOfLiberties(m.stone),0) || 
                cpp2::impl::cmp_greater(cpp2::move(numberOfcapturedStones),0)) {
                return true; 
            }
        }
        return false; 
    }

#line 104 "../src/engine.h2"
    [[nodiscard]] auto Engine::isFinish() const& -> bool{
        if (cpp2::impl::cmp_greater(CPP2_UFCS(ssize)(moves),1)) {
            if (CPP2_ASSERT_IN_BOUNDS(moves, CPP2_UFCS(size)(moves) - 1).pass == true 
            && CPP2_ASSERT_IN_BOUNDS(moves, CPP2_UFCS(size)(moves) - 2).pass == true) {
                return true; 
            }
        }
        return false; 
    }

#line 114 "../src/engine.h2"
    auto Engine::countTerritory(Stone& stone, cpp2::i16& count, Color& color, 
        State<bool>& processedStones1, State<bool>& processedStones2) & -> void{
        if (count == 0) {
            return ; 
        }
        CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones2, stone.col), stone.row) = true;
        auto nextStones {CPP2_UFCS(getAdjacentStone)(goban, stone, processedStones2)}; 
        for ( 
        auto& nextStone : cpp2::move(nextStones) ) {
            if (nextStone.color == Color::None) {
                if (!(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones2, nextStone.col), nextStone.row))) {
                    CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones1, nextStone.col), nextStone.row) = true;
                    ++count;
                    countTerritory(nextStone, count, color, processedStones1, processedStones2);
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
            CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones2, nextStone.col), nextStone.row) = true;
        }
    }

#line 143 "../src/engine.h2"
    auto Engine::countScore() & -> void{
        State<bool> processedStones1 {}; 
        blackPoint = 0;
        whitePoint = 7;
{
cpp2::i8 col{0};

#line 148 "../src/engine.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(goban.state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 152 "../src/engine.h2"
            for( ; cpp2::impl::cmp_less(row,CPP2_UFCS(ssize)(CPP2_ASSERT_IN_BOUNDS(goban.state, col))); 
            ++row ) 
            {
                if (!(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones1, col), row))) {
                    CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones1, col), row) = true;
                    if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row).color == Color::Black) {
                        ++blackPoint;
                    }
                    else {if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row).color == Color::White) {
                        ++whitePoint;
                    }
                    else {
                        cpp2::i16 count {1}; 
                        auto color {Color::None}; 
                        State<bool> processedStones2 {}; 
                        countTerritory(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row), count, color, processedStones1, processedStones2);
                        processedStones2 = processedStones2; // CPP2 workaround: Fix inout recursion.
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
#line 178 "../src/engine.h2"
        }
}
#line 179 "../src/engine.h2"
    }

#line 181 "../src/engine.h2"
    auto Engine::findValidMove(Move& m, State<bool>& processedStones, cpp2::i32& count) & -> void{
        ++count;
        if (cpp2::cpp2_default.is_active() && !(cpp2::impl::cmp_less_eq(count,361)) ) { cpp2::cpp2_default.report_violation(""); }
        if (isValidMove(m)) {
            return ; 
        }
        auto nextStones {CPP2_UFCS(getAdjacentStone)(goban, m.stone, processedStones)}; 
        CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, m.stone.col), m.stone.row) = true;
        for ( 
        auto& nextStone : cpp2::move(nextStones) ) {
            m.stone.col = nextStone.col;
            m.stone.row = nextStone.row;
            if (!(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, m.stone.col), m.stone.row))) {
                findValidMove(m, processedStones, count);
            }
        }
    }

#line 199 "../src/engine.h2"
    auto Engine::closerValidMove(Move& m) & -> void{
        State<bool> processedStones {false}; 
        cpp2::i32 count {0}; 
        findValidMove(m, processedStones, count);
        processedStones = processedStones; // CPP2 workaround: Fix inout recursion.
        if (!(isValidMove(m))) {
            m = Move(m.stone.color, -1, -1, true);
        }
        count = count;
    }
#endif

