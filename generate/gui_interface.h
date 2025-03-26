
#ifndef GUI_INTERFACE_H_CPP2
#define GUI_INTERFACE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/gui_interface.h2"

#line 4 "../src/gui_interface.h2"
class GuiInterface;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/gui_interface.h2"
#include "interface.h"
#include "../src/window.h"

#line 4 "../src/gui_interface.h2"
class GuiInterface: public Interface {

    public: Window* window; 

    public: auto print(cpp2::impl::in<std::string> message) -> void override;

    public: auto printLater(cpp2::impl::in<std::string> message) -> void override;

    public: auto clear() -> void override;

    public: auto refreshGoban(cpp2::impl::in<Goban<9>> goban) -> void override;

#line 18 "../src/gui_interface.h2"
    public: auto refreshGoban(cpp2::impl::in<Goban<19>> goban) -> void override;

#line 22 "../src/gui_interface.h2"
    public: auto wait() -> void override;

#line 25 "../src/gui_interface.h2"
    public: [[nodiscard]] auto waitForAMove(cpp2::impl::in<Color> c) -> Move override;
    public: GuiInterface() = default;
    public: GuiInterface(GuiInterface const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(GuiInterface const&) -> void = delete;


#line 28 "../src/gui_interface.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/gui_interface.h2"

#line 8 "../src/gui_interface.h2"
    auto GuiInterface::print(cpp2::impl::in<std::string> message) -> void{}

#line 10 "../src/gui_interface.h2"
    auto GuiInterface::printLater(cpp2::impl::in<std::string> message) -> void{}

#line 12 "../src/gui_interface.h2"
    auto GuiInterface::clear() -> void{}

#line 14 "../src/gui_interface.h2"
    auto GuiInterface::refreshGoban(cpp2::impl::in<Goban<9>> goban) -> void{
        CPP2_UFCS(refreshGoban)((*cpp2::impl::assert_not_null(window)));
    }

#line 18 "../src/gui_interface.h2"
    auto GuiInterface::refreshGoban(cpp2::impl::in<Goban<19>> goban) -> void{
        CPP2_UFCS(refreshGoban)((*cpp2::impl::assert_not_null(window)));
    }

#line 22 "../src/gui_interface.h2"
    auto GuiInterface::wait() -> void{
    }

#line 25 "../src/gui_interface.h2"
    [[nodiscard]] auto GuiInterface::waitForAMove(cpp2::impl::in<Color> c) -> Move{
        return pass(c); 
    }
#endif

