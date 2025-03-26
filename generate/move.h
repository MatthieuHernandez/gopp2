
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
    public: bool isPass; 
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

#endif
