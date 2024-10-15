
#ifndef MOVE_H_CPP2
#define MOVE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/move.h2"

#line 25 "../src/move.h2"
class Move;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/move.h2"
enum Color: uint8_t {
    None = 0,
    Black = 1,
    White = 2,
};

void switchPlayer(Color& c) {
    if (c == Color::Black) {
        c = Color::White;
    }
    else if (c == Color::White) {
        c =  Color::Black;
    }
}

std::string colorName(const Color& c) {
    if (c == Color::Black) {
        return "Black";
    }
    else if (c == Color::White) {
        return "White";
    }
}

#line 25 "../src/move.h2"
class Move {
    public: Color color; 
    public: std::array<cpp2::i8,2> position; 
    public: std::string name; 
    public: bool pass; 

    public: explicit Move(cpp2::impl::in<Color> col, cpp2::impl::in<std::array<cpp2::i8,2>> pos, cpp2::impl::in<std::string> nam, cpp2::impl::in<bool> pas = false);

#line 38 "../src/move.h2"
    public: Move(Move const& that);
#line 38 "../src/move.h2"
    public: auto operator=(Move const& that) -> Move& ;
#line 38 "../src/move.h2"
    public: Move(Move&& that) noexcept;
#line 38 "../src/move.h2"
    public: auto operator=(Move&& that) noexcept -> Move& ;

#line 44 "../src/move.h2"
};

#line 1 "../src/move.h2"

//=== Cpp2 function definitions =================================================

#line 1 "../src/move.h2"

#line 31 "../src/move.h2"
    Move::Move(cpp2::impl::in<Color> col, cpp2::impl::in<std::array<cpp2::i8,2>> pos, cpp2::impl::in<std::string> nam, cpp2::impl::in<bool> pas)
        : color{ col }
        , position{ pos }
        , name{ nam }
        , pass{ pas }{

#line 36 "../src/move.h2"
    }

#line 38 "../src/move.h2"
    Move::Move(Move const& that)
        : color{ that.color }
        , position{ that.position }
        , name{ that.name }
        , pass{ that.pass }{

#line 43 "../src/move.h2"
    }
#line 38 "../src/move.h2"
    auto Move::operator=(Move const& that) -> Move& {
        color = that.color;
        position = that.position;
        name = that.name;
        pass = that.pass;
        return *this;

#line 43 "../src/move.h2"
    }
#line 38 "../src/move.h2"
    Move::Move(Move&& that) noexcept
        : color{ cpp2::move(that).color }
        , position{ cpp2::move(that).position }
        , name{ cpp2::move(that).name }
        , pass{ cpp2::move(that).pass }{

#line 43 "../src/move.h2"
    }
#line 38 "../src/move.h2"
    auto Move::operator=(Move&& that) noexcept -> Move& {
        color = cpp2::move(that).color;
        position = cpp2::move(that).position;
        name = cpp2::move(that).name;
        pass = cpp2::move(that).pass;
        return *this;

#line 43 "../src/move.h2"
    }
#endif

