
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

    public: explicit Goban();

#line 20 "../src/goban.h2"
    public: [[nodiscard]] auto getAdjacentStone(cpp2::impl::in<Stone> s) const& -> std::vector<Stone>;

#line 58 "../src/goban.h2"
    public: auto clearProcessedStone() & -> void;
    public: Goban(Goban const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Goban const&) -> void = delete;


#line 71 "../src/goban.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/goban.h2"

#line 6 "../src/goban.h2"
    Goban::Goban(){
{
cpp2::i8 col{0};

#line 8 "../src/goban.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 12 "../src/goban.h2"
            for( ; cpp2::impl::cmp_less(row,CPP2_UFCS(ssize)(CPP2_ASSERT_IN_BOUNDS(state, col))); 
            ++row ) 
            {
                CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, col), row) = Stone(Color::None, col, row);
            }
}
#line 17 "../src/goban.h2"
        }
}
#line 18 "../src/goban.h2"
    }

#line 20 "../src/goban.h2"
    [[nodiscard]] auto Goban::getAdjacentStone(cpp2::impl::in<Stone> s) const& -> std::vector<Stone>{
        // vérifier les bounds.
        std::vector<Stone> adjacent_stones {}; 
        if (cpp2::impl::cmp_greater(s.col,0)) {
            if (!(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row).hasBeenProcessed)) {
                CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row));
                std::cout << "adjacent stone color is " << cpp2::impl::as_<cpp2::i32>(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row).color) << std::endl;
                std::cout << "adjacent stone row is " << cpp2::impl::as_<cpp2::i32>(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row).row) << std::endl;
                std::cout << "adjacent stone col is " << cpp2::impl::as_<cpp2::i32>(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col - 1), s.row).col) << std::endl;
            }
        }
        if (cpp2::impl::cmp_less(s.col,18)) {
            if (!(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row).hasBeenProcessed)) {
                CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row));
                std::cout << "adjacent stone color is " << cpp2::impl::as_<cpp2::i32>(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row).color) << std::endl;
                std::cout << "adjacent stone row is " << cpp2::impl::as_<cpp2::i32>(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row).row) << std::endl;
                std::cout << "adjacent stone col is " << cpp2::impl::as_<cpp2::i32>(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col + 1), s.row).col) << std::endl;
            }
        }
        if (cpp2::impl::cmp_greater(s.row,0)) {
            if (!(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row - 1).hasBeenProcessed)) {
                CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row - 1));
                std::cout << "adjacent stone color is " << cpp2::impl::as_<cpp2::i32>(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row - 1).color) << std::endl;
                std::cout << "adjacent stone row is " << cpp2::impl::as_<cpp2::i32>(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row - 1).row) << std::endl;
                std::cout << "adjacent stone col is " << cpp2::impl::as_<cpp2::i32>(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row - 1).col) << std::endl;
            }
        }
        if (cpp2::impl::cmp_less(s.row,18)) {
            if (!(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row + 1).hasBeenProcessed)) {
                CPP2_UFCS(push_back)(adjacent_stones, CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row + 1));
                std::cout << "adjacent stone color is " << cpp2::impl::as_<cpp2::i32>(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row + 1).color) << std::endl;
                std::cout << "adjacent stone row is " << cpp2::impl::as_<cpp2::i32>(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row + 1).row) << std::endl;
                std::cout << "adjacent stone col is " << cpp2::impl::as_<cpp2::i32>(CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, s.col), s.row + 1).col) << std::endl;
            }
        }
        return adjacent_stones; 
    }

#line 58 "../src/goban.h2"
    auto Goban::clearProcessedStone() & -> void{
{
cpp2::i8 col{0};

#line 60 "../src/goban.h2"
        for( ; cpp2::impl::cmp_less(col,CPP2_UFCS(ssize)(state)); 
        ++col ) 
        {
{
cpp2::i8 row{0};

#line 64 "../src/goban.h2"
            for( ; cpp2::impl::cmp_less(row,CPP2_UFCS(ssize)(CPP2_ASSERT_IN_BOUNDS(state, col))); 
            ++row ) 
            {
                CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(state, col), row).hasBeenProcessed = false;
            }
}
#line 69 "../src/goban.h2"
        }
}
#line 70 "../src/goban.h2"
    }
#endif

