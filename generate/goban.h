
#ifndef GOBAN_H_CPP2
#define GOBAN_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/goban.h2"

#line 6 "../src/goban.h2"
class Goban;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/goban.h2"
#include "stone.h"

template<class T>
using State = std::array<std::array<T, 19>, 19>;

#line 6 "../src/goban.h2"
class Goban {
    public: State<Stone> state {}; 

    public: Stone lockedPosition {}; 

    public: explicit Goban();

#line 25 "../src/goban.h2"
           public: [[nodiscard]] auto getAdjacentStone(cpp2::impl::in<Stone> s, cpp2::impl::in<State<bool>> processedStones) const& -> std::vector<Stone>;

#line 43 "../src/goban.h2"
    public: [[nodiscard]] auto isTrueEye(cpp2::impl::in<Stone> s) const& -> bool;

#line 88 "../src/goban.h2"
    public: auto removeStone(cpp2::impl::in<Stone> s) & -> void;

#line 92 "../src/goban.h2"
    public: [[nodiscard]] auto isLockedPosition(cpp2::impl::in<Stone> s) const& -> bool;

#line 97 "../src/goban.h2"
    public: auto lockPosition(cpp2::impl::in<Stone> s, cpp2::impl::in<Color> c) & -> void;

#line 102 "../src/goban.h2"
    public: auto unlockPosition() & -> void;
    public: Goban(Goban const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Goban const&) -> void = delete;


#line 107 "../src/goban.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/goban.h2"

#line 11 "../src/goban.h2"
    Goban::Goban(){
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
           [[nodiscard]] auto Goban::getAdjacentStone(cpp2::impl::in<Stone> s, cpp2::impl::in<State<bool>> processedStones) const& -> std::vector<Stone>{
        // vérifier les bounds.
        std::vector<Stone> adjacent_stones {}; 
        if (cpp2::impl::cmp_greater(s.col,0) && !(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, s.col - 1), s.row))) {
            CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row));
        }
        if (cpp2::impl::cmp_less(s.col,18) && !(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, s.col + 1), s.row))) {
            CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row));
        }
        if (cpp2::impl::cmp_greater(s.row,0) && !(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, s.col), s.row - 1))) {
            CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row - 1));
        }
        if (cpp2::impl::cmp_less(s.row,18) && !(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, s.col), s.row + 1))) {
                CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row + 1));
        }
        return adjacent_stones; 
    }

#line 43 "../src/goban.h2"
    [[nodiscard]] auto Goban::isTrueEye(cpp2::impl::in<Stone> s) const& -> bool{
        cpp2::i8 count {0}; 
        if (cpp2::impl::cmp_greater(s.col,0)) {
            if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row).color == s.color) {
                ++count;
            }
        }
        if (cpp2::impl::cmp_less(s.col,18)) {
            if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row).color == s.color) {
                ++count;
            }
        }
        if (cpp2::impl::cmp_greater(s.row,0)) {
            if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row - 1).color == s.color) {
                ++count;
            }
        }
        if (cpp2::impl::cmp_less(s.row,18)) {
            if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row + 1).color == s.color) {
                ++count;
            }
        }
        if (cpp2::impl::cmp_greater(s.col,0) && cpp2::impl::cmp_greater(s.row,0)) {
            if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row - 1).color == s.color) {
                ++count;
            }
        }
        if (cpp2::impl::cmp_greater(s.col,0) && cpp2::impl::cmp_less(s.row,18)) {
            if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row + 1).color == s.color) {
                ++count;
            }
        }
        if (cpp2::impl::cmp_less(s.col,18) && cpp2::impl::cmp_greater(s.row,0)) {
            if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row - 1).color == s.color) {
                ++count;
            }
        }
        if (cpp2::impl::cmp_less(s.col,18) && cpp2::impl::cmp_less(s.row,18)) {
            if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row + 1).color == s.color) {
                ++count;
            }
        }
        return cpp2::impl::cmp_greater_eq(cpp2::move(count),7); 
    }

#line 88 "../src/goban.h2"
    auto Goban::removeStone(cpp2::impl::in<Stone> s) & -> void{
        CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row).color = Color::None;
    }

#line 92 "../src/goban.h2"
    [[nodiscard]] auto Goban::isLockedPosition(cpp2::impl::in<Stone> s) const& -> bool{
        return lockedPosition.col == s.col && 
            lockedPosition.row == s.row; 
    }

#line 97 "../src/goban.h2"
    auto Goban::lockPosition(cpp2::impl::in<Stone> s, cpp2::impl::in<Color> c) & -> void{
        lockedPosition = s;
        lockedPosition.color = c;
    }

#line 102 "../src/goban.h2"
    auto Goban::unlockPosition() & -> void{
        lockedPosition.color = Color::None;
        lockedPosition.row = -1;
        lockedPosition.col = -1;
    }
#endif

