
#ifndef IO_H_CPP2
#define IO_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/io.h2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/io.h2"
#include "windows.h"

#line 3 "../src/io.h2"
auto clear(cpp2::impl::in<std::string> message = "") -> void;

auto resetCursor() -> void;

auto moveCursor(cpp2::impl::in<uint8_t> x, cpp2::impl::in<uint8_t> y) -> void;

auto print(cpp2::impl::in<std::string> message) -> void;

#line 17 "../src/io.h2"
auto printMenu() -> void;

#line 31 "../src/io.h2"
[[nodiscard]] auto getInputMenu() -> int;

#line 42 "../src/io.h2"
auto printGoban() -> void;

//=== Cpp2 function definitions =================================================

#line 1 "../src/io.h2"

#line 3 "../src/io.h2"
auto clear(cpp2::impl::in<std::string> message) -> void{std::cout << "\x1B[2J\x1B[H" << message << std::endl; }

#line 5 "../src/io.h2"
auto resetCursor() -> void{std::cout << "\033[0J"; }

#line 7 "../src/io.h2"
auto moveCursor(cpp2::impl::in<uint8_t> x, cpp2::impl::in<uint8_t> y) -> void{std::cout << "\033[" << x << ";" << y << "H"; }

#line 9 "../src/io.h2"
auto print(cpp2::impl::in<std::string> message) -> void{
    std::cout << "\033[A\033[K" 
         << "\033[A\033[K" 
         << "\033[A\033[K" 
         << "\033[A\033[K" << message << std::endl;
    std::cout << std::endl;
}

#line 17 "../src/io.h2"
auto printMenu() -> void{
    SetConsoleOutputCP(CP_UTF8);
    clear();
    std::cout << "**************************************************" << std::endl;
    std::cout << "*                   GOPP2 Menu                   *" << std::endl;
    std::cout << "**************************************************" << std::endl;
    std::cout << "* Please select one of the following:            *" << std::endl;
    std::cout << "*                                                *" << std::endl;
    std::cout << "*     1. Start a game                            *" << std::endl;
    std::cout << "*     2. Exit                                    *" << std::endl;
    std::cout << "**************************************************" << std::endl;
    std::cout << std::endl << std::endl;
}

#line 31 "../src/io.h2"
[[nodiscard]] auto getInputMenu() -> int{
    int input {0}; 
    std::cout << "> ";
    std::cin >> input;
    if ((CPP2_UFCS(fail)(std::cin))) {
        return 0; 
    }
    std::cout << "in = " << input << std::endl;
    return input; 
}

#line 42 "../src/io.h2"
auto printGoban() -> void{
    std::cout << "    A B C D E F G H J K L M N O P Q R S T " << std::endl;
    std::cout << " 19 ┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐ " << std::endl;
    std::cout << " 18 ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤ " << std::endl;
    std::cout << " 17 ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤ " << std::endl;
    std::cout << " 16 ├─┼─┼─●─┼─┼─┼─┼─┼─●─┼─┼─┼─┼─┼─●─┼─┼─┤ " << std::endl;
    std::cout << " 15 ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤ " << std::endl;
    std::cout << " 14 ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤ " << std::endl;
    std::cout << " 13 ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤ " << std::endl;
    std::cout << " 12 ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤ " << std::endl;
    std::cout << " 11 ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤ " << std::endl;
    std::cout << " 10 ├─┼─┼─●─┼─┼─┼─┼─┼─●─┼─┼─┼─┼─┼─●─┼─┼─┤ " << std::endl;
    std::cout << "  9 ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤ " << std::endl;
    std::cout << "  8 ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤ " << std::endl;
    std::cout << "  7 ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤ " << std::endl;
    std::cout << "  6 ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤ " << std::endl;
    std::cout << "  5 ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤ " << std::endl;
    std::cout << "  4 ├─┼─┼─●─┼─┼─┼─┼─┼─●─┼─┼─┼─┼─┼─●─┼─┼─┤ " << std::endl;
    std::cout << "  3 ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤ " << std::endl;
    std::cout << "  2 ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤ " << std::endl;
    std::cout << "  1 └─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘ " << std::endl;
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;

    // moveCursor(3, 4);
    // std::cout << "\033[" << 5 << ";" << 6 << "H";
    // std::cout << "⚫ ⚪";
    // std::cout << "\033[23;0H";
    // resetCursor();

    //char wait;
    //cin >> wait;
}
#endif

