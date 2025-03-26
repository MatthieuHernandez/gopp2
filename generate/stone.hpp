
#ifndef STONE_H_CPP2
#error This file is part of a '.h2' header compiled to be consumed from another -pure-cpp2 file. To use this file, write '#include "stone.h2"' in a '.h2' or '.cpp2' file compiled with -pure-cpp2.
#endif

#ifndef STONE_HPP_CPP2
#define STONE_HPP_CPP2

#include "color.hpp"


//=== Cpp2 function definitions =================================================

#line 1 "../src/stone.h2"

#line 10 "../src/stone.h2"
    Stone::Stone()
        : color{ Color::None }
        , col{ -1 }
        , row{ -1 }
        , estimation{ 0.0f }{

#line 15 "../src/stone.h2"
    }

#line 17 "../src/stone.h2"
    Stone::Stone(cpp2::impl::in<Color> p, cpp2::impl::in<cpp2::i8> c, cpp2::impl::in<cpp2::i8> r, cpp2::impl::in<float> e)
        : color{ p }
        , col{ c }
        , row{ r }
        , estimation{ e }{

#line 22 "../src/stone.h2"
    }

#line 24 "../src/stone.h2"
    Stone::Stone(Stone const& that)
        : color{ that.color }
        , col{ that.col }
        , row{ that.row }
        , estimation{ that.estimation }{

#line 28 "../src/stone.h2"
    }
#line 24 "../src/stone.h2"
    auto Stone::operator=(Stone const& that) -> Stone& {
        color = that.color;
        col = that.col;
        row = that.row;
        estimation = that.estimation;
        return *this;

#line 28 "../src/stone.h2"
    }
#line 24 "../src/stone.h2"
    Stone::Stone(Stone&& that) noexcept
        : color{ cpp2::move(that).color }
        , col{ cpp2::move(that).col }
        , row{ cpp2::move(that).row }
        , estimation{ std::move(that).estimation }{

#line 28 "../src/stone.h2"
    }
#line 24 "../src/stone.h2"
    auto Stone::operator=(Stone&& that) noexcept -> Stone& {
        color = cpp2::move(that).color;
        col = cpp2::move(that).col;
        row = cpp2::move(that).row;
        estimation = std::move(that).estimation;
        return *this;

#line 28 "../src/stone.h2"
    }

#line 30 "../src/stone.h2"
    template<cpp2::i8 Size> [[nodiscard]] auto Stone::getIndex() const& -> cpp2::i16{
        return (cpp2::impl::as_<cpp2::i16>(col)) * (Size) + (cpp2::impl::as_<cpp2::i16>(row)); 
    }
#endif

