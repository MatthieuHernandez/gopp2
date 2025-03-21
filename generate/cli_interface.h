
#ifndef CLI_INTERFACE_H_CPP2
#define CLI_INTERFACE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/cli_interface.h2"

#line 4 "../src/cli_interface.h2"
class CliInterface;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/cli_interface.h2"
#include "interface.h"
#include "io.h"

#line 4 "../src/cli_interface.h2"
class CliInterface: public Interface {

#line 7 "../src/cli_interface.h2"
    public: auto print(cpp2::impl::in<std::string> message) -> void override;

#line 11 "../src/cli_interface.h2"
    public: auto printLater(cpp2::impl::in<std::string> message) -> void override;

#line 15 "../src/cli_interface.h2"
    public: auto clear() -> void override;

#line 19 "../src/cli_interface.h2"
    public: auto refreshGoban(cpp2::impl::in<Goban<9>> goban) -> void override;

#line 23 "../src/cli_interface.h2"
    public: auto refreshGoban(cpp2::impl::in<Goban<19>> goban) -> void override;

#line 27 "../src/cli_interface.h2"
    public: auto wait() -> void override;

#line 31 "../src/cli_interface.h2"
    public: [[nodiscard]] auto waitForAMove(cpp2::impl::in<Color> c) -> Move override;
    public: CliInterface() = default;
    public: CliInterface(CliInterface const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(CliInterface const&) -> void = delete;


#line 34 "../src/cli_interface.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/cli_interface.h2"

#line 7 "../src/cli_interface.h2"
    auto CliInterface::print(cpp2::impl::in<std::string> message) -> void{
        std::cout << message << std::endl;
    }

#line 11 "../src/cli_interface.h2"
    auto CliInterface::printLater(cpp2::impl::in<std::string> message) -> void{
        setNextMessage(message);
    }

#line 15 "../src/cli_interface.h2"
    auto CliInterface::clear() -> void{
        clearConsole();
    }

#line 19 "../src/cli_interface.h2"
    auto CliInterface::refreshGoban(cpp2::impl::in<Goban<9>> goban) -> void{
        printGoban<9>(goban);
    }

#line 23 "../src/cli_interface.h2"
    auto CliInterface::refreshGoban(cpp2::impl::in<Goban<19>> goban) -> void{
        printGoban<19>(goban);
    }

#line 27 "../src/cli_interface.h2"
    auto CliInterface::wait() -> void{
        waitInput();
    }

#line 31 "../src/cli_interface.h2"
    [[nodiscard]] auto CliInterface::waitForAMove(cpp2::impl::in<Color> c) -> Move{
        return getInputMove<9>(c); 
    }
#endif

