
#ifndef MOVE_H_CPP2
#define MOVE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/move.h2"

#line 3 "../src/move.h2"
class Move;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/move.h2"
#include "stone.h"

#line 3 "../src/move.h2"
class Move {
    public: Stone stone; 
    public: std::string name; 
    public: bool pass; 

    public: explicit Move();

#line 14 "../src/move.h2"
    public: explicit Move(cpp2::impl::in<Color> color, cpp2::impl::in<cpp2::i8> col, cpp2::impl::in<cpp2::i8> row, cpp2::impl::in<std::string> nam, cpp2::impl::in<bool> pas = false);

#line 20 "../src/move.h2"
    public: Move(Move const& that);
#line 20 "../src/move.h2"
    public: auto operator=(Move const& that) -> Move& ;
#line 20 "../src/move.h2"
    public: Move(Move&& that) noexcept;
#line 20 "../src/move.h2"
    public: auto operator=(Move&& that) noexcept -> Move& ;

#line 25 "../src/move.h2"
};

#line 1 "../src/move.h2"

//=== Cpp2 function definitions =================================================

#line 1 "../src/move.h2"

#line 8 "../src/move.h2"
    Move::Move()
        : stone{  }
        , name{ "" }
        , pass{ false }{

#line 12 "../src/move.h2"
    }

#line 14 "../src/move.h2"
    Move::Move(cpp2::impl::in<Color> color, cpp2::impl::in<cpp2::i8> col, cpp2::impl::in<cpp2::i8> row, cpp2::impl::in<std::string> nam, cpp2::impl::in<bool> pas)
        : stone{ color, col, row }
        , name{ nam }
        , pass{ pas }{

#line 18 "../src/move.h2"
    }

#line 20 "../src/move.h2"
    Move::Move(Move const& that)
        : stone{ that.stone }
        , name{ that.name }
        , pass{ that.pass }{

#line 24 "../src/move.h2"
    }
#line 20 "../src/move.h2"
    auto Move::operator=(Move const& that) -> Move& {
        stone = that.stone;
        name = that.name;
        pass = that.pass;
        return *this;

#line 24 "../src/move.h2"
    }
#line 20 "../src/move.h2"
    Move::Move(Move&& that) noexcept
        : stone{ cpp2::move(that).stone }
        , name{ cpp2::move(that).name }
        , pass{ cpp2::move(that).pass }{

#line 24 "../src/move.h2"
    }
#line 20 "../src/move.h2"
    auto Move::operator=(Move&& that) noexcept -> Move& {
        stone = cpp2::move(that).stone;
        name = cpp2::move(that).name;
        pass = cpp2::move(that).pass;
        return *this;

#line 24 "../src/move.h2"
    }
#endif

