
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
    public: float estimation; 
    public: bool isLocked; 

#line 11 "../src/stone.h2"
    public: Stone();

#line 19 "../src/stone.h2"
    public: Stone(cpp2::impl::in<Color> p, cpp2::impl::in<cpp2::i8> c, cpp2::impl::in<cpp2::i8> r, cpp2::impl::in<float> e = 0.0f);

#line 27 "../src/stone.h2"
    public: Stone(Stone const& that);
#line 27 "../src/stone.h2"
    public: auto operator=(Stone const& that) -> Stone& ;
#line 27 "../src/stone.h2"
    public: Stone(Stone&& that) noexcept;
#line 27 "../src/stone.h2"
    public: auto operator=(Stone&& that) noexcept -> Stone& ;

#line 33 "../src/stone.h2"
    public: template<cpp2::i8 Size> [[nodiscard]] auto getIndex() const& -> cpp2::i16;

#line 37 "../src/stone.h2"
    public: [[nodiscard]] auto operator<=>(Stone const& that) const& -> std::strong_ordering = default;
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/stone.h2"

#line 11 "../src/stone.h2"
    Stone::Stone()
        : color{ Color::None }
        , col{ -1 }
        , row{ -1 }
        , estimation{ 0.0f }
        , isLocked{ false }{

#line 17 "../src/stone.h2"
    }

#line 19 "../src/stone.h2"
    Stone::Stone(cpp2::impl::in<Color> p, cpp2::impl::in<cpp2::i8> c, cpp2::impl::in<cpp2::i8> r, cpp2::impl::in<float> e)
        : color{ p }
        , col{ c }
        , row{ r }
        , estimation{ e }
        , isLocked{ false }{

#line 25 "../src/stone.h2"
    }

#line 27 "../src/stone.h2"
    Stone::Stone(Stone const& that)
        : color{ that.color }
        , col{ that.col }
        , row{ that.row }
        , estimation{ that.estimation }
        , isLocked{ that.isLocked }{

#line 31 "../src/stone.h2"
    }
#line 27 "../src/stone.h2"
    auto Stone::operator=(Stone const& that) -> Stone& {
        color = that.color;
        col = that.col;
        row = that.row;
        estimation = that.estimation;
        isLocked = that.isLocked;
        return *this;

#line 31 "../src/stone.h2"
    }
#line 27 "../src/stone.h2"
    Stone::Stone(Stone&& that) noexcept
        : color{ cpp2::move(that).color }
        , col{ cpp2::move(that).col }
        , row{ cpp2::move(that).row }
        , estimation{ std::move(that).estimation }
        , isLocked{ std::move(that).isLocked }{

#line 31 "../src/stone.h2"
    }
#line 27 "../src/stone.h2"
    auto Stone::operator=(Stone&& that) noexcept -> Stone& {
        color = cpp2::move(that).color;
        col = cpp2::move(that).col;
        row = cpp2::move(that).row;
        estimation = std::move(that).estimation;
        isLocked = std::move(that).isLocked;
        return *this;

#line 31 "../src/stone.h2"
    }

#line 33 "../src/stone.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Stone::getIndex() const& -> cpp2::i16{
        return (cpp2::impl::as_<cpp2::i16>(col)) * (Size - 1) + (cpp2::impl::as_<cpp2::i16>(row)); 
    }
#endif

