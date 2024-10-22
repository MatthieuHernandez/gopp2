
#ifndef GOBAN_H_CPP2
#define GOBAN_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/goban.h2"

#line 3 "../src/goban.h2"
class Goban;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/goban.h2"
#include "stone.h"

#line 3 "../src/goban.h2"
class Goban {
    public: std::array<std::array<Stone,19>,19> state {}; 

    public: Stone lockedPosition {}; 

    public: explicit Goban();

#line 22 "../src/goban.h2"
    public: [[nodiscard]] auto getAdjacentStone(cpp2::impl::in<Stone> s) const& -> std::vector<Stone>;

#line 48 "../src/goban.h2"
    public: [[nodiscard]] auto stonehasBeenProcessed(cpp2::impl::in<Stone> s) & -> bool;

#line 52 "../src/goban.h2"
    public: auto processStone(cpp2::impl::in<Stone> s) & -> void;

#line 56 "../src/goban.h2"
    public: auto clearProcessedStone() & -> void;

#line 70 "../src/goban.h2"
    public: auto removeStone(cpp2::impl::in<Stone> s) & -> void;

#line 75 "../src/goban.h2"
    public: auto lockPosition(cpp2::impl::in<Stone> s, cpp2::impl::in<Color> c) & -> void;

#line 80 "../src/goban.h2"
    public: auto unlockPosition() & -> void;
    public: Goban(Goban const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Goban const&) -> void = delete;


#line 85 "../src/goban.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/goban.h2"

#line 8 "../src/goban.h2"
    Goban::Goban(){
{
cpp2::i8 col{0};

#line 10 "../src/goban.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 14 "../src/goban.h2"
            for( ; cpp2::impl::cmp_less(row,CPP2_UFCS(ssize)(CPP2_ASSERT_IN_BOUNDS(state, col))); 
            ++row ) 
            {
                CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, col), row) = Stone(Color::None, col, row);
            }
}
#line 19 "../src/goban.h2"
        }
}
#line 20 "../src/goban.h2"
    }

#line 22 "../src/goban.h2"
    [[nodiscard]] auto Goban::getAdjacentStone(cpp2::impl::in<Stone> s) const& -> std::vector<Stone>{
        // vérifier les bounds.
        std::vector<Stone> adjacent_stones {}; 
        if (cpp2::impl::cmp_greater(s.col,0)) {
            if (!(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row).hasBeenProcessed)) {
                CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row));
            }
        }
        if (cpp2::impl::cmp_less(s.col,18)) {
            if (!(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row).hasBeenProcessed)) {
                CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row));
            }
        }
        if (cpp2::impl::cmp_greater(s.row,0)) {
            if (!(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row - 1).hasBeenProcessed)) {
                CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row - 1));
            }
        }
        if (cpp2::impl::cmp_less(s.row,18)) {
            if (!(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row + 1).hasBeenProcessed)) {
                CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row + 1));
            }
        }
        return adjacent_stones; 
    }

#line 48 "../src/goban.h2"
    [[nodiscard]] auto Goban::stonehasBeenProcessed(cpp2::impl::in<Stone> s) & -> bool{
        return CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row).hasBeenProcessed; 
    }

#line 52 "../src/goban.h2"
    auto Goban::processStone(cpp2::impl::in<Stone> s) & -> void{
        CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row).hasBeenProcessed = true;
    }

#line 56 "../src/goban.h2"
    auto Goban::clearProcessedStone() & -> void{
{
cpp2::i8 col{0};

#line 58 "../src/goban.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 62 "../src/goban.h2"
            for( ; cpp2::impl::cmp_less(row,CPP2_UFCS(ssize)(CPP2_ASSERT_IN_BOUNDS(state, col))); 
            ++row ) 
            {
                CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, col), row).hasBeenProcessed = false;
            }
}
#line 67 "../src/goban.h2"
        }
}
#line 68 "../src/goban.h2"
    }

#line 70 "../src/goban.h2"
    auto Goban::removeStone(cpp2::impl::in<Stone> s) & -> void{
        CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row).color = Color::None;
        CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row).hasBeenProcessed = true;
    }

#line 75 "../src/goban.h2"
    auto Goban::lockPosition(cpp2::impl::in<Stone> s, cpp2::impl::in<Color> c) & -> void{
        lockedPosition = s;
        lockedPosition.color = c;
    }

#line 80 "../src/goban.h2"
    auto Goban::unlockPosition() & -> void{
        lockedPosition.color = Color::None;
        lockedPosition.row = -1;
        lockedPosition.col = -1;
    }
#endif

