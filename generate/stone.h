
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
    public: bool isLocked; 

    public: Stone();

#line 16 "../src/stone.h2"
    public: explicit Stone(cpp2::impl::in<Color> p, cpp2::impl::in<cpp2::i8> c, cpp2::impl::in<cpp2::i8> r);

#line 23 "../src/stone.h2"
    public: Stone(Stone const& that);
#line 23 "../src/stone.h2"
    public: auto operator=(Stone const& that) -> Stone& ;
#line 23 "../src/stone.h2"
    public: Stone(Stone&& that) noexcept;
#line 23 "../src/stone.h2"
    public: auto operator=(Stone&& that) noexcept -> Stone& ;

#line 29 "../src/stone.h2"
    public: [[nodiscard]] auto operator<=>(Stone const& that) const& -> std::strong_ordering = default;
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/stone.h2"

#line 9 "../src/stone.h2"
    Stone::Stone()
        : color{ Color::None }
        , col{ -1 }
        , row{ -1 }
        , isLocked{ false }{

#line 14 "../src/stone.h2"
    }

#line 16 "../src/stone.h2"
    Stone::Stone(cpp2::impl::in<Color> p, cpp2::impl::in<cpp2::i8> c, cpp2::impl::in<cpp2::i8> r)
        : color{ p }
        , col{ c }
        , row{ r }
        , isLocked{ false }{

#line 21 "../src/stone.h2"
    }

#line 23 "../src/stone.h2"
    Stone::Stone(Stone const& that)
        : color{ that.color }
        , col{ that.col }
        , row{ that.row }
        , isLocked{ that.isLocked }{

#line 27 "../src/stone.h2"
    }
#line 23 "../src/stone.h2"
    auto Stone::operator=(Stone const& that) -> Stone& {
        color = that.color;
        col = that.col;
        row = that.row;
        isLocked = that.isLocked;
        return *this;

#line 27 "../src/stone.h2"
    }
#line 23 "../src/stone.h2"
    Stone::Stone(Stone&& that) noexcept
        : color{ cpp2::move(that).color }
        , col{ cpp2::move(that).col }
        , row{ cpp2::move(that).row }
        , isLocked{ std::move(that).isLocked }{

#line 27 "../src/stone.h2"
    }
#line 23 "../src/stone.h2"
    auto Stone::operator=(Stone&& that) noexcept -> Stone& {
        color = cpp2::move(that).color;
        col = cpp2::move(that).col;
        row = cpp2::move(that).row;
        isLocked = std::move(that).isLocked;
        return *this;

#line 27 "../src/stone.h2"
    }
#endif

