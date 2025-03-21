
#ifndef INTERFACE_H_CPP2
#define INTERFACE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/interface.h2"

#line 4 "../src/interface.h2"
class Interface;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/interface.h2"
#include "goban.h"
#include "move.h"

#line 4 "../src/interface.h2"
class Interface {
    public: virtual auto print(cpp2::impl::in<std::string> message) -> void = 0;

    public: virtual auto printLater(cpp2::impl::in<std::string> message) -> void = 0;

    public: virtual auto clear() -> void = 0;

    public: virtual auto refreshGoban(cpp2::impl::in<Goban<9>> goban) -> void = 0;

    public: virtual auto refreshGoban(cpp2::impl::in<Goban<19>> goban) -> void = 0;

    public: virtual auto wait() -> void = 0;

    public: [[nodiscard]] virtual auto waitForAMove(cpp2::impl::in<Color> c) -> Move = 0;
    public: Interface() = default;
    public: Interface(Interface const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Interface const&) -> void = delete;

#line 18 "../src/interface.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/interface.h2"

#endif
