
#ifndef MOVE_H_CPP2
#define MOVE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/move.h2"

#line 7 "../src/move.h2"
class Move;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/move.h2"
#include "stone.h"

#line 3 "../src/move.h2"
[[nodiscard]] auto pass(cpp2::impl::in<Color> color) -> Move;

#line 7 "../src/move.h2"
class Move {
    public: Stone stone; 
    public: bool pass; 
    public: bool isValid; 

    public: explicit Move();

#line 18 "../src/move.h2"
    public: Move(cpp2::impl::in<Color> color, cpp2::impl::in<cpp2::i8> col, cpp2::impl::in<cpp2::i8> row, cpp2::impl::in<bool> pas = false);

#line 24 "../src/move.h2"
    public: Move(cpp2::impl::in<Stone> s);
#line 24 "../src/move.h2"
    public: auto operator=(cpp2::impl::in<Stone> s) -> Move& ;

#line 30 "../src/move.h2"
    public: [[nodiscard]] auto name() const& -> std::string;

#line 43 "../src/move.h2"
    public: Move(Move const& that);
#line 43 "../src/move.h2"
    public: auto operator=(Move const& that) -> Move& ;
#line 43 "../src/move.h2"
    public: Move(Move&& that) noexcept;
#line 43 "../src/move.h2"
    public: auto operator=(Move&& that) noexcept -> Move& ;

#line 48 "../src/move.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/move.h2"

#line 3 "../src/move.h2"
[[nodiscard]] auto pass(cpp2::impl::in<Color> color) -> Move{
    return Move(color, -1, -1, true); 
}

#line 12 "../src/move.h2"
    Move::Move()
        : stone{  }
        , pass{ false }
        , isValid{ false }{

#line 16 "../src/move.h2"
    }

#line 18 "../src/move.h2"
    Move::Move(cpp2::impl::in<Color> color, cpp2::impl::in<cpp2::i8> col, cpp2::impl::in<cpp2::i8> row, cpp2::impl::in<bool> pas)
        : stone{ color, col, row }
        , pass{ pas }
        , isValid{ false }{

#line 22 "../src/move.h2"
    }

#line 24 "../src/move.h2"
    Move::Move(cpp2::impl::in<Stone> s)
        : stone{ s }
        , pass{ false }
        , isValid{ false }{

#line 28 "../src/move.h2"
    }
#line 24 "../src/move.h2"
    auto Move::operator=(cpp2::impl::in<Stone> s) -> Move& {
        stone = s;
        pass = false;
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
        , pass{ that.pass }
        , isValid{ that.isValid }{

#line 47 "../src/move.h2"
    }
#line 43 "../src/move.h2"
    auto Move::operator=(Move const& that) -> Move& {
        stone = that.stone;
        pass = that.pass;
        isValid = that.isValid;
        return *this;

#line 47 "../src/move.h2"
    }
#line 43 "../src/move.h2"
    Move::Move(Move&& that) noexcept
        : stone{ cpp2::move(that).stone }
        , pass{ cpp2::move(that).pass }
        , isValid{ cpp2::move(that).isValid }{

#line 47 "../src/move.h2"
    }
#line 43 "../src/move.h2"
    auto Move::operator=(Move&& that) noexcept -> Move& {
        stone = cpp2::move(that).stone;
        pass = cpp2::move(that).pass;
        isValid = cpp2::move(that).isValid;
        return *this;

#line 47 "../src/move.h2"
    }
#endif

