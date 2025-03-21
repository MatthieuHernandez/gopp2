
#ifndef GUI_INTERFACE_H_CPP2
#define GUI_INTERFACE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/gui_interface.h2"

#line 3 "../src/gui_interface.h2"
class GuiInterface;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/gui_interface.h2"
#include "interface.h"

#line 3 "../src/gui_interface.h2"
class GuiInterface: public Interface {

#line 6 "../src/gui_interface.h2"
    public: auto print(cpp2::impl::in<std::string> message) -> void override;

    public: auto printLater(cpp2::impl::in<std::string> message) -> void override;

    public: auto clear() -> void override;

    public: auto refreshGoban(cpp2::impl::in<Goban<9>> goban) -> void override;

    public: auto refreshGoban(cpp2::impl::in<Goban<19>> goban) -> void override;

    public: [[nodiscard]] auto wait() -> Move override;

    public: [[nodiscard]] auto waitForAMove(cpp2::impl::in<Color> c) -> Move override;
    public: GuiInterface() = default;
    public: GuiInterface(GuiInterface const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(GuiInterface const&) -> void = delete;


#line 21 "../src/gui_interface.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/gui_interface.h2"

#line 6 "../src/gui_interface.h2"
    auto GuiInterface::print(cpp2::impl::in<std::string> message) -> void{}

#line 8 "../src/gui_interface.h2"
    auto GuiInterface::printLater(cpp2::impl::in<std::string> message) -> void{}

#line 10 "../src/gui_interface.h2"
    auto GuiInterface::clear() -> void{}

#line 12 "../src/gui_interface.h2"
    auto GuiInterface::refreshGoban(cpp2::impl::in<Goban<9>> goban) -> void{}

#line 14 "../src/gui_interface.h2"
    auto GuiInterface::refreshGoban(cpp2::impl::in<Goban<19>> goban) -> void{}

#line 16 "../src/gui_interface.h2"
    [[nodiscard]] auto GuiInterface::wait() -> Move{}

#line 18 "../src/gui_interface.h2"
    [[nodiscard]] auto GuiInterface::waitForAMove(cpp2::impl::in<Color> c) -> Move{
        return pass(C); 
    }
#endif

