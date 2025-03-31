
#ifndef CLI_INTERFACE_H_CPP2
#define CLI_INTERFACE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/cli_interface.h2"

#line 5 "../src/cli_interface.h2"
class CliInterface;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/cli_interface.h2"
#include "cli.h"
#include "interface.h"
#include "io.h"

#line 5 "../src/cli_interface.h2"
class CliInterface: public Interface {

#line 8 "../src/cli_interface.h2"
    public: auto print(cpp2::impl::in<std::string> message) -> void override;

#line 12 "../src/cli_interface.h2"
    public: auto printLater(cpp2::impl::in<std::string> message) -> void override;

#line 16 "../src/cli_interface.h2"
    public: auto clear() -> void override;

#line 20 "../src/cli_interface.h2"
    public: auto refreshGoban(cpp2::impl::in<Goban<9>> goban) -> void override;

#line 24 "../src/cli_interface.h2"
    public: auto refreshGoban(cpp2::impl::in<Goban<13>> goban) -> void override;

#line 28 "../src/cli_interface.h2"
    public: auto refreshGoban(cpp2::impl::in<Goban<19>> goban) -> void override;

#line 32 "../src/cli_interface.h2"
    public: auto wait() -> void override;

#line 36 "../src/cli_interface.h2"
    public: [[nodiscard]] auto waitForAMove(cpp2::impl::in<Color> c) -> Move override;
    public: CliInterface() = default;
    public: CliInterface(CliInterface const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(CliInterface const&) -> void = delete;


#line 39 "../src/cli_interface.h2"
};

#endif
