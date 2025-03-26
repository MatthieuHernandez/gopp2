
#ifndef CLI_H_CPP2
#define CLI_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/cli.h2"

#line 4 "../src/cli.h2"
namespace cli {

#line 234 "../src/cli.h2"
}


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/cli.h2"
#include "goban.h"
#include "move.h"

#line 4 "../src/cli.h2"
namespace cli {

extern std::string nextMessage;

auto setNextMessage(cpp2::impl::in<std::string> message) -> void;

#line 12 "../src/cli.h2"
[[nodiscard]] auto getNextMessage() -> std::string;

#line 18 "../src/cli.h2"
auto clearConsole(cpp2::impl::in<std::string> message = "") -> void;

auto clearInput() -> void;

#line 25 "../src/cli.h2"
[[nodiscard]] auto printMenuAndSelect(cpp2::impl::in<cpp2::i8> size, cpp2::impl::in<std::string> players) -> cpp2::i32;

#line 44 "../src/cli.h2"
[[nodiscard]] auto getInputMenu() -> cpp2::i32;

#line 52 "../src/cli.h2"
auto waitInput() -> void;

#line 58 "../src/cli.h2"
template<cpp2::i8 Size> [[nodiscard]] auto getInputMove(cpp2::impl::in<Color> color) -> Move;

#line 97 "../src/cli.h2"
// Make it a coroutine without row and col parameter
template<cpp2::i8 Size> auto printIntersection(cpp2::impl::in<cpp2::i16> row, cpp2::impl::in<cpp2::i16> col) -> void;

#line 138 "../src/cli.h2"
template<cpp2::i8 Size> auto printGoban(cpp2::impl::in<Goban<Size>> goban) -> void;

#line 175 "../src/cli.h2"
[[nodiscard]] auto getSnnModels(cpp2::impl::in<cpp2::i8> size) -> std::vector<std::array<std::string,2>>;

#line 195 "../src/cli.h2"
[[nodiscard]] auto printPlayersAndSelect(cpp2::impl::in<cpp2::i8> size, cpp2::impl::in<Color> color) -> std::string;

#line 234 "../src/cli.h2"
}

#endif
