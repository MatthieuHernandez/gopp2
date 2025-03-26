
#ifndef ENGINE_H_CPP2
#error This file is part of a '.h2' header compiled to be consumed from another -pure-cpp2 file. To use this file, write '#include "engine.h2"' in a '.h2' or '.cpp2' file compiled with -pure-cpp2.
#endif

#ifndef ENGINE_HPP_CPP2
#define ENGINE_HPP_CPP2

#include "goban.hpp"
#include "move.hpp"


//=== Cpp2 function definitions =================================================

#line 1 "../src/engine.h2"

#line 13 "../src/engine.h2"
    template <cpp2::i8 Size> Engine<Size>::Engine(){
        State<Stone,Size> state {}; 
        CPP2_UFCS(push_back)(states, cpp2::move(state));
    }

#line 18 "../src/engine.h2"
    template <cpp2::i8 Size> auto Engine<Size>::playMove(Move& m) & -> void{
        if (isValidMove(m)) 
        {
            if (!(m.isPass)) {
                auto col {m.stone.col}; 
                auto row {m.stone.row}; 
                CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, cpp2::move(col)), row) = m.stone;
            }
            if (goban.lockedPosition.color == m.stone.color) {
                CPP2_UFCS(unlockPosition)(goban);
            }
            CPP2_UFCS(push_back)(moves, m);
            CPP2_UFCS(push_back)(states, goban.state);
        }
    }

#line 34 "../src/engine.h2"
    template <cpp2::i8 Size> auto Engine<Size>::countLiberties(cpp2::impl::in<Stone> stone, cpp2::i16& count, State<bool,Size>& processedStones) & -> void{
        if (cpp2::impl::cmp_greater(count,1)) {
            return ; 
        }
        CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, stone.col), stone.row) = true;
        auto nextStones {CPP2_UFCS(getAdjacentStone)(goban, stone, processedStones)}; 
        for ( 
        auto const& nextStone : nextStones ) {
            if (!(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, nextStone.col), nextStone.row))) {
                if (nextStone.color == Color::None) {
                    CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, nextStone.col), nextStone.row) = true;
                    ++count;
                    if (cpp2::impl::cmp_greater(count,1)) {
                        return ; 
                    }
                }
            }
        }
        for ( 
        auto const& nextStone : cpp2::move(nextStones) ) {
            if (!(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, nextStone.col), nextStone.row))) {
                if (nextStone.color == stone.color) {
                    countLiberties(nextStone, count, processedStones);
                }
            }
        }
    }

#line 62 "../src/engine.h2"
    template <cpp2::i8 Size> [[nodiscard]] auto Engine<Size>::numberOfLiberties(Stone& stone) & -> cpp2::i16{
        State<bool,Size> processedStones {}; 
        cpp2::i16 count {0}; 
        countLiberties(stone, count, processedStones);
        processedStones = processedStones;
        return count; 
    }

#line 70 "../src/engine.h2"
    template <cpp2::i8 Size> auto Engine<Size>::removeGroup(Stone& stone, cpp2::i16& count, State<bool,Size>& processedStones) & -> void{
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

#line 83 "../src/engine.h2"
    template <cpp2::i8 Size> [[nodiscard]] auto Engine<Size>::captureStones(Stone& stone) & -> cpp2::i16{
        State<bool,Size> processedStones {}; 
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
        return count; 
    }

#line 105 "../src/engine.h2"
    template <cpp2::i8 Size> [[nodiscard]] auto Engine<Size>::isValidMove(Move& m) & -> bool{
        if (m.isValid || m.isPass) {
            CPP2_UFCS(unlockPosition)(goban);
            m.isValid = true;
            return true; 
        }
        auto col {m.stone.col}; 
        auto row {m.stone.row}; 
        if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, cpp2::move(col)), cpp2::move(row)).color == Color::None && !(CPP2_UFCS(isTrueEye)(goban, m.stone))) {
            if (!(CPP2_UFCS(isLockedPosition)(goban, m.stone))) {
                auto captured {captureStones(m.stone)}; 
                if (cpp2::impl::cmp_greater(captured,0) || cpp2::impl::cmp_greater(numberOfLiberties(m.stone),0)) {
                    if (cpp2::move(captured) != 1) {
                        CPP2_UFCS(unlockPosition)(goban);
                    }
                    m.isValid = true;
                    return true; 
                }
            }
        }
        m.isValid = false;
        return false; 
    }

#line 129 "../src/engine.h2"
    template <cpp2::i8 Size> [[nodiscard]] auto Engine<Size>::isFinish() const& -> bool{
        if (cpp2::impl::cmp_greater(CPP2_UFCS(ssize)(moves),1)) {
            if (CPP2_ASSERT_IN_BOUNDS(moves, CPP2_UFCS(ssize)(moves) - 1).isPass == true 
            && CPP2_ASSERT_IN_BOUNDS(moves, CPP2_UFCS(ssize)(moves) - 2).isPass == true) {
                return true; 
            }
        }
        return false; 
    }

#line 139 "../src/engine.h2"
    template <cpp2::i8 Size> auto Engine<Size>::countTerritory(cpp2::impl::in<Stone> stone, cpp2::i16& count, Color& color, 
        State<bool,Size>& processedStones1, State<bool,Size>& processedStones2) & -> void{
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

#line 168 "../src/engine.h2"
    template <cpp2::i8 Size> auto Engine<Size>::countScore() & -> void{
        State<bool,Size> processedStones1 {}; 
        blackPoint = 0;
        whitePoint = 7;
{
cpp2::i8 col{0};

#line 173 "../src/engine.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(goban.state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 177 "../src/engine.h2"
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
                        State<bool,Size> processedStones2 {}; 
                        countTerritory(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row), count, color, processedStones1, processedStones2);
                        if (cpp2::cpp2_default.is_active() && !(&processedStones2) ) { cpp2::cpp2_default.report_violation(""); }// CPP2 workaround: Fix inout recursion.
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
#line 203 "../src/engine.h2"
        }
}
#line 204 "../src/engine.h2"
    }

#line 206 "../src/engine.h2"
    template <cpp2::i8 Size> auto Engine<Size>::findValidMove(Move& m, State<bool,Size>& processedStones, cpp2::i32& count) & -> void{
        CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, m.stone.col), m.stone.row) = true;
        ++count;
        if (isValidMove(m)) {
            return ; 
        }
        auto nextStones {CPP2_UFCS(getAdjacentStone)(goban, m.stone, processedStones)}; 
        for ( 
        auto const& nextStone : cpp2::move(nextStones) ) {
            if (!(m.isValid)) {
                m.stone.col = nextStone.col;
                m.stone.row = nextStone.row;
                if (!(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, m.stone.col), m.stone.row))) {
                    findValidMove(m, processedStones, count);
                }
            }
        }
    }

#line 225 "../src/engine.h2"
    template <cpp2::i8 Size> auto Engine<Size>::closerValidMove(Move& m) & -> void{
        if (m.isPass) {
            return ; 
        }
        State<bool,Size> processedStones {false}; 
        cpp2::i32 count {0}; 
        findValidMove(m, processedStones, count);
        if (cpp2::cpp2_default.is_active() && !(&processedStones) ) { cpp2::cpp2_default.report_violation(""); }// CPP2 workaround: Fix inout recursion.
        if (cpp2::cpp2_default.is_active() && !(&count) ) { cpp2::cpp2_default.report_violation(""); }// CPP2 workaround: Fix inout recursion.
        if (!(m.isValid)) {
            m = pass(m.stone.color);
        }
    }
#endif

