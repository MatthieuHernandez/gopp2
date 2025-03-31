
#ifndef CLI_INTERFACE_H_CPP2
#error This file is part of a '.h2' header compiled to be consumed from another -pure-cpp2 file. To use this file, write '#include "cli_interface.h2"' in a '.h2' or '.cpp2' file compiled with -pure-cpp2.
#endif

#ifndef CLI_INTERFACE_HPP_CPP2
#define CLI_INTERFACE_HPP_CPP2

#include "cli.hpp"
#include "interface.hpp"
#include "io.hpp"


//=== Cpp2 function definitions =================================================

#line 1 "../src/cli_interface.h2"

#line 8 "../src/cli_interface.h2"
    auto CliInterface::print(cpp2::impl::in<std::string> message) -> void{
        std::cout << message << std::endl;
    }

#line 12 "../src/cli_interface.h2"
    auto CliInterface::printLater(cpp2::impl::in<std::string> message) -> void{
        cli::setNextMessage(message);
    }

#line 16 "../src/cli_interface.h2"
    auto CliInterface::clear() -> void{
        cli::clearConsole();
    }

#line 20 "../src/cli_interface.h2"
    auto CliInterface::refreshGoban(cpp2::impl::in<Goban<9>> goban) -> void{
        cli::printGoban<9>(goban);
    }

#line 24 "../src/cli_interface.h2"
    auto CliInterface::refreshGoban(cpp2::impl::in<Goban<13>> goban) -> void{
        cli::printGoban<13>(goban);
    }

#line 28 "../src/cli_interface.h2"
    auto CliInterface::refreshGoban(cpp2::impl::in<Goban<19>> goban) -> void{
        cli::printGoban<19>(goban);
    }

#line 32 "../src/cli_interface.h2"
    auto CliInterface::wait() -> void{
        cli::waitInput();
    }

#line 36 "../src/cli_interface.h2"
    [[nodiscard]] auto CliInterface::waitForAMove(cpp2::impl::in<Color> c) -> Move{
        return cli::getInputMove<9>(c); 
    }
#endif

