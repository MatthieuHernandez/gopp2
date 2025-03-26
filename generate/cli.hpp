
#ifndef CLI_H_CPP2
#error This file is part of a '.h2' header compiled to be consumed from another -pure-cpp2 file. To use this file, write '#include "cli.h2"' in a '.h2' or '.cpp2' file compiled with -pure-cpp2.
#endif

#ifndef CLI_HPP_CPP2
#define CLI_HPP_CPP2

#include "goban.hpp"
#include "move.hpp"


//=== Cpp2 function definitions =================================================

#line 1 "../src/cli.h2"

#line 4 "../src/cli.h2"
namespace cli {

std::string nextMessage {"\n"}; 

#line 8 "../src/cli.h2"
auto setNextMessage(cpp2::impl::in<std::string> message) -> void{
    nextMessage = nextMessage + "\n" + message;
}

#line 12 "../src/cli.h2"
[[nodiscard]] auto getNextMessage() -> std::string{
    auto m {nextMessage}; 
    nextMessage = "";
    return m; 
}

#line 18 "../src/cli.h2"
auto clearConsole(cpp2::impl::in<std::string> message) -> void{std::cout << "\x1B[2J\x1B[H" << message << std::endl; }

#line 20 "../src/cli.h2"
auto clearInput() -> void{
    CPP2_UFCS(clear)(std::cin);
    CPP2_UFCS(ignore)(std::cin, INT_MAX, '\n');
}

#line 25 "../src/cli.h2"
[[nodiscard]] auto printMenuAndSelect(cpp2::impl::in<cpp2::i8> size, cpp2::impl::in<std::string> players) -> cpp2::i32{
    clearConsole();
    auto goban {cpp2::impl::as_<std::string>(size) + "x" + cpp2::impl::as_<std::string>(size)}; 
    std::cout << "**************************************************" << std::endl;
    std::cout << "*                   GOPP2 Menu                   *" << std::endl;
    std::cout << "**************************************************" << std::endl;
    std::cout << "* Please select one of the following:            *" << std::endl;
    std::cout << "*                                                *" << std::endl;
    std::cout << "*     1. Select Goban: " << std::left << std::setw(26) << std::setfill(' ') << cpp2::move(goban) << "*" << std::endl;
    std::cout << "*     2. Select Players: " << std::left << std::setw(24) << std::setfill(' ') << players  << "*" << std::endl;
    std::cout << "*     3. Play one game                           *" << std::endl;
    std::cout << "*     4. Train Black player                      *" << std::endl;
    std::cout << "*     5. Evaluate players against each other     *" << std::endl;
    std::cout << "*     0. Exit                                    *" << std::endl;
    std::cout << "**************************************************" << std::endl;
    std::cout << getNextMessage() << std::endl;
    return getInputMenu(); 
}

#line 44 "../src/cli.h2"
[[nodiscard]] auto getInputMenu() -> cpp2::i32{
    cpp2::i32 input {0}; 
    std::cout << "> ";
    std::cin >> input;
    clearInput();
    return input; 
}

#line 52 "../src/cli.h2"
auto waitInput() -> void{
    std::string input {""}; 
    std::cout << "> ";
    CPP2_UFCS(get)(std::cin);
}

#line 58 "../src/cli.h2"
template<cpp2::i8 Size> [[nodiscard]] auto getInputMove(cpp2::impl::in<Color> color) -> Move{
    std::string input {""}; 
    std::cout << std::endl << colorName(color) << " to play:" << std::endl << "> ";
    std::cin >> input;
    clearInput();
    if ((input == "pass")) {
        setNextMessage("Player pass.");
        return pass(color); 
    }
    CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 0) = std::toupper(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 0));
    if (((Size == 9 && 
       (CPP2_UFCS(ssize)(input) != 2 || 
       cpp2::impl::cmp_less(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 0),'A') || cpp2::impl::cmp_greater(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 0),'J') || CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 0) == 'I' || 
       (cpp2::impl::cmp_less(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 1),'1') || cpp2::impl::cmp_greater(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 1),'9')))) || 
       (Size == 19 && 
       (cpp2::impl::cmp_less(CPP2_UFCS(ssize)(input),2) || cpp2::impl::cmp_greater(CPP2_UFCS(ssize)(input),3) || 
       cpp2::impl::cmp_less(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 0),'A') || cpp2::impl::cmp_greater(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 0),'T') || CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 0) == 'I' || 
       (CPP2_UFCS(ssize)(input) == 2 && (cpp2::impl::cmp_less(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 1),'1') || cpp2::impl::cmp_greater(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 1),'9'))) || 
       (CPP2_UFCS(ssize)(input) == 3 && (CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 1) != '1' || cpp2::impl::cmp_less(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 2),'0') || cpp2::impl::cmp_greater(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 2),'9'))))))) 

       {
        std::cout << "\033[A\033[A\033[A\033[A\033[K" << "Invalid Move." << std::endl;
        return getInputMove<Size>(color); 
    }
    cpp2::i8 col {0}; 
    col = CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 0) - 65;
    if (cpp2::impl::cmp_greater(col,8)) {// No I column
        --col;
    }
    cpp2::i8 row {0}; 
    if (CPP2_UFCS(ssize)(input) == 2) {
        row = CPP2_ASSERT_IN_BOUNDS_LITERAL(cpp2::move(input), 1) - 49;
    }else {
        row = ((CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 1) - 48) * 10) + (CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 2) - 49);
    }
    Move m {color, cpp2::move(col), cpp2::move(row), false}; 
    return m; 
}

#line 98 "../src/cli.h2"
template<cpp2::i8 Size> auto printIntersection(cpp2::impl::in<cpp2::i16> row, cpp2::impl::in<cpp2::i16> col) -> void{
    cpp2::i8 maxIndex {Size - 1}; 
    if (((Size == 9 && 
        ((row == 2 && (col == 2 || col == 6)) || 
        (row ==  6 && (col == 2 || col == 6)))) || 
        (Size == 19 && 
        ((row == 15 && (col == 3 || col == 9 || col == 15)) || 
        (row == 9 && (col == 3 || col == 9 || col == 15)) || 
        (row ==  3 && (col == 3 || col == 9 || col == 15))))))  {
        std::cout << "─●";
    }else {
        if (row == maxIndex) {
            if (col == 0) {
                std::cout << " ┌";
            }
            else {if (col == cpp2::move(maxIndex)) {
                std::cout << "─┐";
            }else {
                std::cout << "─┬";
            }}
        }else {if (row == 0) {
            if (col == 0) {
                std::cout << " └";
            }else {if (col == cpp2::move(maxIndex)) {
                std::cout << "─┘";
            }else {
                std::cout << "─┴";
            }}
        }else {
            if (col == 0) {
                std::cout << " ├";
            }else {if (col == cpp2::move(maxIndex)) {
                std::cout << "─┤";
            }else {
                std::cout << "─┼";
            }}
        }}
    }
}

#line 138 "../src/cli.h2"
template<cpp2::i8 Size> auto printGoban(cpp2::impl::in<Goban<Size>> goban) -> void{
    // First line
    if constexpr (Size == 19) {
        std::cout << "     A B C D E F G H J K L M N O P Q R S T" << std::endl;
    }
    if constexpr (Size == 9) {
        std::cout << "     A B C D E F G H J" << std::endl;
    }
    cpp2::i8 maxIndex {Size - 1}; 
    cpp2::i8 row {maxIndex}; 
    for( ; cpp2::impl::cmp_greater(row,-1); 
    --row ) 
    {
        //v: i8 = row + 1
        if (cpp2::impl::cmp_less(row,9)) {
            std::cout << "  " << cpp2::impl::as_<std::string>((row + 1)) << " ";
        }else {
             std::cout << " " << cpp2::impl::as_<std::string>((row + 1)) << " ";
        }
        cpp2::i8 col {0}; 
        for( ; cpp2::impl::cmp_less_eq(col,maxIndex); 
        ++col ) 
        {
            if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row).color == Color::Black) {
                std::cout << "⚫";
            }else {if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row).color == Color::White) {
                std::cout << "⚪";
            }
            else {if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row).color == Color::None) {
                printIntersection<Size>(row, col);
            }}}
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << getNextMessage() << std::endl;
}

#line 175 "../src/cli.h2"
[[nodiscard]] auto getSnnModels(cpp2::impl::in<cpp2::i8> size) -> std::vector<std::array<std::string,2>>{
    std::vector<std::array<std::string,2>> modelFiles {}; 
    std::string path {""}; 
    if (size == 9) {
        path = "./snn_models/9x9";
    }else {if (size == 19) {
        path = "./snn_models/19x19";
    }}

    auto files {std::filesystem::directory_iterator(path)}; 
    for ( 
    auto const& file : cpp2::move(files) ) {
        std::string modelName {CPP2_UFCS(string)(CPP2_UFCS(filename)(CPP2_UFCS(path)(file)))}; 
        std::string modelPath {CPP2_UFCS(string)(CPP2_UFCS(path)(file))}; 
        std::array<std::string,2> modelFile {cpp2::move(modelName), cpp2::move(modelPath)}; 
        CPP2_UFCS(push_back)(modelFiles, cpp2::move(modelFile));
    }
    return modelFiles; 
}

#line 195 "../src/cli.h2"
[[nodiscard]] auto printPlayersAndSelect(cpp2::impl::in<cpp2::i8> size, cpp2::impl::in<Color> color) -> std::string{
    auto add_itself {color == Color::White}; 
    clearConsole();
    auto title {"*                  " + cpp2::impl::as_<std::string>(size) + "x" + cpp2::impl::as_<std::string>(size) + " players"}; 
    auto select {"* Please select " + colorName(color) + " player:"}; 
    std::cout << "**************************************************" << std::endl;
    std::cout << std::left << std::setw(49) << std::setfill(' ') << cpp2::move(title) << "*" << std::endl;
    std::cout << "**************************************************" << std::endl;
    std::cout << std::left << std::setw(49) << std::setfill(' ') << cpp2::move(select) << "*" << std::endl;
    std::cout << "*                                                *" << std::endl;
    if ((color == Color::White)) {
        std::cout << "*    -1. Itself                                  *" << std::endl;
    }
    std::cout << "*     0. Human Player                            *" << std::endl;
    std::cout << "*     1. Dumb Player                             *" << std::endl;
    std::cout << "*     2. Random Player                           *" << std::endl;
    auto modelNames {getSnnModels(size)}; 
{
cpp2::i8 i{0};

#line 213 "../src/cli.h2"
    for( ; cpp2::impl::cmp_less(i,CPP2_UFCS(ssize)(modelNames)); 
    ++i ) 
    {
        auto model {"*     " + cpp2::impl::as_<std::string>((i + 3)) + ". " + CPP2_ASSERT_IN_BOUNDS_LITERAL(CPP2_ASSERT_IN_BOUNDS(modelNames, i), 0)}; 
        std::cout << std::left << std::setw(49) << std::setfill(' ') << cpp2::move(model) << "*" << std::endl;
    }
}
#line 219 "../src/cli.h2"
    std::cout << "**************************************************" << std::endl;
    std::cout << std::endl << getNextMessage() << std::endl;
    cpp2::i32 input {0}; 
    std::cout << "> ";
    std::cin >> input;
    clearInput();
    if ((cpp2::impl::cmp_greater_eq(input,-1) && cpp2::impl::cmp_less_eq(input,2))) {
        return cpp2::impl::as_<std::string>(input); 
    }
    input -= 3;
    if ((cpp2::impl::cmp_greater_eq(input,0) && cpp2::impl::cmp_less(input,CPP2_UFCS(ssize)(modelNames)))) {
        return CPP2_ASSERT_IN_BOUNDS_LITERAL(CPP2_ASSERT_IN_BOUNDS(cpp2::move(modelNames), cpp2::move(input)), 1); 
    }
    return ""; 
}
}

#endif
