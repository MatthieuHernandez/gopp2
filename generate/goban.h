
#ifndef GOBAN_H_CPP2
#define GOBAN_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/goban.h2"

#line 7 "../src/goban.h2"
template<cpp2::i8 Size> class Goban;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/goban.h2"
#include "stone.h"

// CPP1 workaround: Do not know how to do this in CPP2.
template<class T, int8_t Size>
using State = std::array<std::array<T, Size>, Size>;

#line 7 "../src/goban.h2"
template<cpp2::i8 Size> class Goban {
    public: State<Stone,Size> state {}; 
    public: Stone lockedPosition {}; 
    public: cpp2::i32 iterations {0}; 
    private: cpp2::i8 maxIndex {Size - 1}; 

    public: explicit Goban();

#line 27 "../src/goban.h2"
           public: [[nodiscard]] auto getAdjacentStone(cpp2::impl::in<Stone> s, cpp2::impl::in<State<bool,Size>> processedStones, cpp2::impl::in<bool> count = true) & -> std::vector<Stone>;

#line 47 "../src/goban.h2"
    public: [[nodiscard]] auto isTrueEye(cpp2::impl::in<Stone> s) const& -> bool;

#line 78 "../src/goban.h2"
    public: auto removeStone(cpp2::impl::in<Stone> s) & -> void;

#line 82 "../src/goban.h2"
    public: [[nodiscard]] auto isLockedPosition(cpp2::impl::in<Stone> s) const& -> bool;

#line 87 "../src/goban.h2"
    public: auto lockPosition(cpp2::impl::in<Stone> s, cpp2::impl::in<Color> c) & -> void;

#line 92 "../src/goban.h2"
    public: auto unlockPosition() & -> void;
    public: Goban(Goban const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Goban const&) -> void = delete;


#line 97 "../src/goban.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/goban.h2"

#line 13 "../src/goban.h2"
    template <cpp2::i8 Size> Goban<Size>::Goban(){
{
cpp2::i8 col{0};

#line 15 "../src/goban.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 19 "../src/goban.h2"
            for( ; cpp2::impl::cmp_less(row,CPP2_UFCS(ssize)(CPP2_ASSERT_IN_BOUNDS(state, col))); 
            ++row ) 
            {
                CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, col), row) = Stone(Color::None, col, row);
            }
}
#line 24 "../src/goban.h2"
        }
}
#line 25 "../src/goban.h2"
    }

#line 27 "../src/goban.h2"
           template <cpp2::i8 Size> [[nodiscard]] auto Goban<Size>::getAdjacentStone(cpp2::impl::in<Stone> s, cpp2::impl::in<State<bool,Size>> processedStones, cpp2::impl::in<bool> count) & -> std::vector<Stone>{
        std::vector<Stone> adjacent_stones {}; 
        if (cpp2::impl::cmp_greater(s.col,0) && !(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, s.col - 1), s.row))) {
            CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row));
        }
        if (cpp2::impl::cmp_less(s.col,maxIndex) && !(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, s.col + 1), s.row))) {
            CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row));
        }
        if (cpp2::impl::cmp_greater(s.row,0) && !(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, s.col), s.row - 1))) {
            CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row - 1));
        }
        if (cpp2::impl::cmp_less(s.row,maxIndex) && !(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(processedStones, s.col), s.row + 1))) {
                CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row + 1));
        }
        if (count) {
            iterations += CPP2_UFCS(ssize)(adjacent_stones);
        }
        return adjacent_stones; 
    }

#line 47 "../src/goban.h2"
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

#line 78 "../src/goban.h2"
    template <cpp2::i8 Size> auto Goban<Size>::removeStone(cpp2::impl::in<Stone> s) & -> void{
        CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row).color = Color::None;
    }

#line 82 "../src/goban.h2"
    template <cpp2::i8 Size> [[nodiscard]] auto Goban<Size>::isLockedPosition(cpp2::impl::in<Stone> s) const& -> bool{
        return lockedPosition.col == s.col && 
            lockedPosition.row == s.row; 
    }

#line 87 "../src/goban.h2"
    template <cpp2::i8 Size> auto Goban<Size>::lockPosition(cpp2::impl::in<Stone> s, cpp2::impl::in<Color> c) & -> void{
        lockedPosition = s;
        lockedPosition.color = c;
    }

#line 92 "../src/goban.h2"
    template <cpp2::i8 Size> auto Goban<Size>::unlockPosition() & -> void{
        lockedPosition.color = Color::None;
        lockedPosition.row = -1;
        lockedPosition.col = -1;
    }
#endif

