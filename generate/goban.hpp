
#ifndef GOBAN_H_CPP2
#error This file is part of a '.h2' header compiled to be consumed from another -pure-cpp2 file. To use this file, write '#include "goban.h2"' in a '.h2' or '.cpp2' file compiled with -pure-cpp2.
#endif

#ifndef GOBAN_HPP_CPP2
#define GOBAN_HPP_CPP2

#include "stone.hpp"


//=== Cpp2 function definitions =================================================

#line 1 "../src/goban.h2"

#line 11 "../src/goban.h2"
    template <cpp2::i8 Size> Goban<Size>::Goban(){
{
cpp2::i8 col{0};

#line 13 "../src/goban.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 17 "../src/goban.h2"
            for( ; cpp2::impl::cmp_less(row,CPP2_UFCS(ssize)(CPP2_ASSERT_IN_BOUNDS(state, col))); 
            ++row ) 
            {
                CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, col), row) = Stone(Color::None, col, row);
            }
}
#line 22 "../src/goban.h2"
        }
}
#line 23 "../src/goban.h2"
    }

#line 25 "../src/goban.h2"
           template <cpp2::i8 Size> [[nodiscard]] auto Goban<Size>::getAdjacentStone(cpp2::impl::in<Stone> s, cpp2::impl::in<State<bool,Size>> processedStones, cpp2::impl::in<bool> count) & -> std::vector<Stone>{
        std::vector<Stone> adjacentStones {}; 
        if (cpp2::impl::cmp_greater(s.col,0) && !(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, s.col - 1), s.row))) {
            CPP2_UFCS(push_back)(adjacentStones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row));
        }
        if (cpp2::impl::cmp_less(s.col,maxIndex) && !(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, s.col + 1), s.row))) {
            CPP2_UFCS(push_back)(adjacentStones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row));
        }
        if (cpp2::impl::cmp_greater(s.row,0) && !(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, s.col), s.row - 1))) {
            CPP2_UFCS(push_back)(adjacentStones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row - 1));
        }
        if (cpp2::impl::cmp_less(s.row,maxIndex) && !(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, s.col), s.row + 1))) {
                CPP2_UFCS(push_back)(adjacentStones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row + 1));
        }
        if (count) {
            iterations += CPP2_UFCS(ssize)(adjacentStones);
        }
        return adjacentStones; 
    }

#line 45 "../src/goban.h2"
    template <cpp2::i8 Size> [[nodiscard]] auto Goban<Size>::isTrueEye(cpp2::impl::in<Stone> s) const& -> bool{
        if ((cpp2::impl::cmp_greater(s.col,0) && CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row).color != s.color) || 
            (cpp2::impl::cmp_less(s.col,maxIndex) && CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row).color != s.color) || 
            (cpp2::impl::cmp_greater(s.row,0) && CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row - 1).color != s.color) || 
            (cpp2::impl::cmp_less(s.row,maxIndex) && CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row + 1).color != s.color)) {
                return false; 
        }
        cpp2::i8 count {0}; 
        if (cpp2::impl::cmp_greater(s.col,0) && cpp2::impl::cmp_greater(s.row,0)) {
            if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row - 1).color == s.color) {
                ++count;
            }
        }
        if (cpp2::impl::cmp_greater(s.col,0) && cpp2::impl::cmp_less(s.row,maxIndex)) {
            if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row + 1).color == s.color) {
                ++count;
            }
        }
        if (cpp2::impl::cmp_less(s.col,maxIndex) && cpp2::impl::cmp_greater(s.row,0)) {
            if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row - 1).color == s.color) {
                ++count;
            }
        }
        if (cpp2::impl::cmp_less(s.col,maxIndex) && cpp2::impl::cmp_less(s.row,maxIndex)) {
            if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row + 1).color == s.color) {
                ++count;
            }
        }
        return cpp2::impl::cmp_greater_eq(cpp2::move(count),3); 
    }

#line 76 "../src/goban.h2"
    template <cpp2::i8 Size> auto Goban<Size>::removeStone(cpp2::impl::in<Stone> s) & -> void{
        CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row).color = Color::None;
    }

#line 80 "../src/goban.h2"
    template <cpp2::i8 Size> [[nodiscard]] auto Goban<Size>::isLockedPosition(cpp2::impl::in<Stone> s) const& -> bool{
        return lockedPosition.col == s.col && 
            lockedPosition.row == s.row; 
    }

#line 85 "../src/goban.h2"
    template <cpp2::i8 Size> auto Goban<Size>::lockPosition(cpp2::impl::in<Stone> s, cpp2::impl::in<Color> c) & -> void{
        lockedPosition = s;
        lockedPosition.color = c;
    }

#line 90 "../src/goban.h2"
    template <cpp2::i8 Size> auto Goban<Size>::unlockPosition() & -> void{
        lockedPosition.color = Color::None;
        lockedPosition.row = -1;
        lockedPosition.col = -1;
    }
#endif

