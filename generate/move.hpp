
#ifndef MOVE_H_CPP2
#error This file is part of a '.h2' header compiled to be consumed from another -pure-cpp2 file. To use this file, write '#include "move.h2"' in a '.h2' or '.cpp2' file compiled with -pure-cpp2.
#endif

#ifndef MOVE_HPP_CPP2
#define MOVE_HPP_CPP2

#include "stone.hpp"


//=== Cpp2 function definitions =================================================

#line 1 "../src/move.h2"

#line 3 "../src/move.h2"
[[nodiscard]] auto pass(cpp2::impl::in<Color> color) -> Move{
    return Move(color, -1, -1, true); 
}

#line 12 "../src/move.h2"
    Move::Move()
        : stone{  }
        , isPass{ false }
        , isValid{ false }{

#line 16 "../src/move.h2"
    }

#line 18 "../src/move.h2"
    Move::Move(cpp2::impl::in<Color> color, cpp2::impl::in<cpp2::i8> col, cpp2::impl::in<cpp2::i8> row, cpp2::impl::in<bool> pas)
        : stone{ color, col, row }
        , isPass{ pas }
        , isValid{ false }{

#line 22 "../src/move.h2"
    }

#line 24 "../src/move.h2"
    Move::Move(cpp2::impl::in<Stone> s)
        : stone{ s }
        , isPass{ false }
        , isValid{ false }{

#line 28 "../src/move.h2"
    }
#line 24 "../src/move.h2"
    auto Move::operator=(cpp2::impl::in<Stone> s) -> Move& {
        stone = s;
        isPass = false;
        isValid = false;
        return *this;

#line 28 "../src/move.h2"
    }

#line 30 "../src/move.h2"
    [[nodiscard]] auto Move::name() const& -> std::string{
        if (!(pass)) {
            char colName {stone.col}; 
            colName +=  65;
            if (cpp2::impl::cmp_greater(stone.col,7)) {// No I column
                ++colName;
            }
            auto n {cpp2::move(colName) + cpp2::impl::as_<std::string>((stone.row + 1))}; 
            return n; 
        }
        return "pass"; 
    }

#line 43 "../src/move.h2"
    Move::Move(Move const& that)
        : stone{ that.stone }
        , isPass{ that.isPass }
        , isValid{ that.isValid }{

#line 47 "../src/move.h2"
    }
#line 43 "../src/move.h2"
    auto Move::operator=(Move const& that) -> Move& {
        stone = that.stone;
        isPass = that.isPass;
        isValid = that.isValid;
        return *this;

#line 47 "../src/move.h2"
    }
#line 43 "../src/move.h2"
    Move::Move(Move&& that) noexcept
        : stone{ cpp2::move(that).stone }
        , isPass{ cpp2::move(that).isPass }
        , isValid{ cpp2::move(that).isValid }{

#line 47 "../src/move.h2"
    }
#line 43 "../src/move.h2"
    auto Move::operator=(Move&& that) noexcept -> Move& {
        stone = cpp2::move(that).stone;
        isPass = cpp2::move(that).isPass;
        isValid = cpp2::move(that).isValid;
        return *this;

#line 47 "../src/move.h2"
    }
#endif

