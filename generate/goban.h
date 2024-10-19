
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

    // BUG: Using vector because we cannot initialize std::array in cpp2.
    public: std::vector<std::vector<Stone>> state; 

    public: explicit Goban();
    public: Goban(Goban const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Goban const&) -> void = delete;


#line 27 "../src/goban.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/goban.h2"

#line 8 "../src/goban.h2"
    Goban::Goban()
        : state{  }{

#line 10 "../src/goban.h2"
        cpp2::i32 size {19}; 
        CPP2_UFCS(reserve)(state, size);
{
cpp2::i8 col{0};

#line 13 "../src/goban.h2"
        for( ; cpp2::impl::cmp_less(col,size); 
        ++col ) 
        {
            std::vector<Stone> v {}; 
            CPP2_UFCS(push_back)(state, cpp2::move(v));
            CPP2_UFCS(reserve)(CPP2_ASSERT_IN_BOUNDS(state, col), size);
{
cpp2::i8 row{0};

#line 20 "../src/goban.h2"
            for( ; cpp2::impl::cmp_less(row,size); 
            ++row ) 
            {
                CPP2_UFCS(emplace_back)(CPP2_ASSERT_IN_BOUNDS(state, col), Color::None, col, row);
            }
}
#line 25 "../src/goban.h2"
        }
}
#line 26 "../src/goban.h2"
    }
#endif

