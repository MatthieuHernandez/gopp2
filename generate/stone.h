
#ifndef STONE_H_CPP2
#define STONE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/stone.h2"

#line 3 "../src/stone.h2"
class Stone;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/stone.h2"
#include "color.h"

#line 3 "../src/stone.h2"
class Stone {
    public: Color color; 
    public: cpp2::i8 col; 
    public: cpp2::i8 row; 
    public: bool has_been_processed; 

    public: explicit Stone(cpp2::impl::in<Color> p, cpp2::impl::in<cpp2::i8> c, cpp2::impl::in<cpp2::i8> r);

#line 16 "../src/stone.h2"
    public: Stone(Stone const& that);
#line 16 "../src/stone.h2"
    public: auto operator=(Stone const& that) -> Stone& ;
#line 16 "../src/stone.h2"
    public: Stone(Stone&& that) noexcept;
#line 16 "../src/stone.h2"
    public: auto operator=(Stone&& that) noexcept -> Stone& ;

#line 21 "../src/stone.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/stone.h2"

#line 9 "../src/stone.h2"
    Stone::Stone(cpp2::impl::in<Color> p, cpp2::impl::in<cpp2::i8> c, cpp2::impl::in<cpp2::i8> r)
        : color{ p }
        , col{ c }
        , row{ r }
        , has_been_processed{ false }{

#line 14 "../src/stone.h2"
    }

#line 16 "../src/stone.h2"
    Stone::Stone(Stone const& that)
        : color{ that.color }
        , col{ that.col }
        , row{ that.row }
        , has_been_processed{ that.has_been_processed }{

#line 20 "../src/stone.h2"
    }
#line 16 "../src/stone.h2"
    auto Stone::operator=(Stone const& that) -> Stone& {
        color = that.color;
        col = that.col;
        row = that.row;
        has_been_processed = that.has_been_processed;
        return *this;

#line 20 "../src/stone.h2"
    }
#line 16 "../src/stone.h2"
    Stone::Stone(Stone&& that) noexcept
        : color{ cpp2::move(that).color }
        , col{ cpp2::move(that).col }
        , row{ cpp2::move(that).row }
        , has_been_processed{ std::move(that).has_been_processed }{

#line 20 "../src/stone.h2"
    }
#line 16 "../src/stone.h2"
    auto Stone::operator=(Stone&& that) noexcept -> Stone& {
        color = cpp2::move(that).color;
        col = cpp2::move(that).col;
        row = cpp2::move(that).row;
        has_been_processed = std::move(that).has_been_processed;
        return *this;

#line 20 "../src/stone.h2"
    }
#endif

