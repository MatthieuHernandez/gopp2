
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
    public: std::string name; 
    public: bool isValid; 

    public: explicit Move();

#line 20 "../src/move.h2"
    public: Move(cpp2::impl::in<Color> color, cpp2::impl::in<cpp2::i8> col, cpp2::impl::in<cpp2::i8> row, cpp2::impl::in<bool> pas = false);

#line 35 "../src/move.h2"
    public: Move(Move const& that);
#line 35 "../src/move.h2"
    public: auto operator=(Move const& that) -> Move& ;
#line 35 "../src/move.h2"
    public: Move(Move&& that) noexcept;
#line 35 "../src/move.h2"
    public: auto operator=(Move&& that) noexcept -> Move& ;

#line 41 "../src/move.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/move.h2"

#line 3 "../src/move.h2"
[[nodiscard]] auto pass(cpp2::impl::in<Color> color) -> Move{
    return Move(color, -1, -1, true); 
}

#line 13 "../src/move.h2"
    Move::Move()
        : stone{  }
        , pass{ false }
        , name{ "" }
        , isValid{ false }{

#line 18 "../src/move.h2"
    }

#line 20 "../src/move.h2"
    Move::Move(cpp2::impl::in<Color> color, cpp2::impl::in<cpp2::i8> col, cpp2::impl::in<cpp2::i8> row, cpp2::impl::in<bool> pas)
        : stone{ color, col, row }
        , pass{ pas }
        , name{ "pass" }
        , isValid{ false }{

#line 25 "../src/move.h2"
        if (!(pass)) {
            char colName {col}; 
            colName +=  65;
            if (cpp2::impl::cmp_greater(col,7)) {// No I column
                ++colName;
            }
            name = cpp2::move(colName) + cpp2::impl::as_<std::string>((row + 1));
        }
    }

#line 35 "../src/move.h2"
    Move::Move(Move const& that)
        : stone{ that.stone }
        , pass{ that.pass }
        , name{ that.name }
        , isValid{ that.isValid }{

#line 38 "../src/move.h2"
        pass = that.pass;
        isValid = that.isValid;
    }
#line 35 "../src/move.h2"
    auto Move::operator=(Move const& that) -> Move& {
        stone = that.stone;
        pass = that.pass;
        name = that.name;
        isValid = that.isValid;

#line 38 "../src/move.h2"
        pass = that.pass;
        isValid = that.isValid;
        return *this;
#line 40 "../src/move.h2"
    }
#line 35 "../src/move.h2"
    Move::Move(Move&& that) noexcept
        : stone{ cpp2::move(that).stone }
        , pass{ std::move(that).pass }
        , name{ cpp2::move(that).name }
        , isValid{ std::move(that).isValid }{

#line 38 "../src/move.h2"
        pass = cpp2::move(that).pass;
        isValid = cpp2::move(that).isValid;
    }
#line 35 "../src/move.h2"
    auto Move::operator=(Move&& that) noexcept -> Move& {
        stone = cpp2::move(that).stone;
        pass = std::move(that).pass;
        name = cpp2::move(that).name;
        isValid = std::move(that).isValid;

#line 38 "../src/move.h2"
        pass = cpp2::move(that).pass;
        isValid = cpp2::move(that).isValid;
        return *this;
#line 40 "../src/move.h2"
    }
#endif

