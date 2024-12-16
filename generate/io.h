
#ifndef IO_H_CPP2
#define IO_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/io.h2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/io.h2"
#include "goban.h"
#include "move.h"

#line 4 "../src/io.h2"
extern std::string nextMessage;

auto setNextMessage(cpp2::impl::in<std::string> message) -> void;

#line 10 "../src/io.h2"
[[nodiscard]] auto getNextMessage() -> std::string;

#line 16 "../src/io.h2"
auto clear(cpp2::impl::in<std::string> message = "") -> void;

auto clearInput() -> void;

#line 23 "../src/io.h2"
[[nodiscard]] auto printMenuAndSelect() -> cpp2::i32;

#line 40 "../src/io.h2"
[[nodiscard]] auto getInputMenu() -> cpp2::i32;

#line 48 "../src/io.h2"
auto waitInput() -> void;

#line 54 "../src/io.h2"
[[nodiscard]] auto getInputMove(cpp2::impl::in<Color> color) -> Move;

#line 86 "../src/io.h2"
// Make it a coroutine without row and col parameter
auto printIntersection(cpp2::impl::in<cpp2::i16> row, cpp2::impl::in<cpp2::i16> col) -> void;

#line 122 "../src/io.h2"
auto printGoban(cpp2::impl::in<Goban> goban) -> void;

#line 153 "../src/io.h2"
[[nodiscard]] auto getSnnModels() -> std::vector<std::string>;

#line 163 "../src/io.h2"
[[nodiscard]] auto printPlayersAndSelect(cpp2::impl::in<Color> color) -> std::string;

//=== Cpp2 function definitions =================================================

#line 1 "../src/io.h2"

#line 4 "../src/io.h2"
std::string nextMessage {"\n"}; 

#line 6 "../src/io.h2"
auto setNextMessage(cpp2::impl::in<std::string> message) -> void{
    nextMessage = nextMessage + "\n" + message;
}

#line 10 "../src/io.h2"
[[nodiscard]] auto getNextMessage() -> std::string{
    auto m {nextMessage}; 
    nextMessage = "";
    return m; 
}

#line 16 "../src/io.h2"
auto clear(cpp2::impl::in<std::string> message) -> void{std::cout << "\x1B[2J\x1B[H" << message << std::endl; }

#line 18 "../src/io.h2"
auto clearInput() -> void{
    CPP2_UFCS(clear)(std::cin);
    CPP2_UFCS(ignore)(std::cin, INT_MAX, '\n');
}

#line 23 "../src/io.h2"
[[nodiscard]] auto printMenuAndSelect() -> cpp2::i32{
    clear();
    std::cout << "**************************************************" << std::endl;
    std::cout << "*                   GOPP2 Menu                   *" << std::endl;
    std::cout << "**************************************************" << std::endl;
    std::cout << "* Please select one of the following:            *" << std::endl;
    std::cout << "*                                                *" << std::endl;
    std::cout << "*     1. Select Players                          *" << std::endl;
    std::cout << "*     2. Play one game                           *" << std::endl;
    std::cout << "*     3. Train Black player                      *" << std::endl;
    std::cout << "*     4. Evaluated players against each other    *" << std::endl;
    std::cout << "*     0. Exit                                    *" << std::endl;
    std::cout << "**************************************************" << std::endl;
    std::cout << getNextMessage() << std::endl;
    return getInputMenu(); 
}

#line 40 "../src/io.h2"
[[nodiscard]] auto getInputMenu() -> cpp2::i32{
    cpp2::i32 input {0}; 
    std::cout << "> ";
    std::cin >> input;
    clearInput();
    return input; 
}

#line 48 "../src/io.h2"
auto waitInput() -> void{
    std::string input {""}; 
    std::cout << "> ";
    CPP2_UFCS(get)(std::cin);
}

#line 54 "../src/io.h2"
[[nodiscard]] auto getInputMove(cpp2::impl::in<Color> color) -> Move{
    std::string input {""}; 
    std::cout << std::endl << colorName(color) << " to play:" << std::endl << "> ";
    std::cin >> input;
    clearInput();
    if ((input == "pass")) {
        setNextMessage("Player pass.");
        return pass(color); 
    }
    CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 0) = std::toupper(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 0));
    if ((cpp2::impl::cmp_less(CPP2_UFCS(ssize)(input),2) || cpp2::impl::cmp_greater(CPP2_UFCS(ssize)(input),3) || 
       cpp2::impl::cmp_less(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 0),'A') || cpp2::impl::cmp_greater(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 0),'T') || CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 0) == 'I' || 
       (CPP2_UFCS(ssize)(input) == 2 && (cpp2::impl::cmp_less(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 1),'1') || cpp2::impl::cmp_greater(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 1),'9'))) || 
       (CPP2_UFCS(ssize)(input) == 3 && (CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 1) != '1' || cpp2::impl::cmp_less(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 2),'0') || cpp2::impl::cmp_greater(CPP2_ASSERT_IN_BOUNDS_LITERAL(input, 2),'9'))))) {
        std::cout << "\033[A\033[A\033[A\033[A\033[K" << "Invalid Move." << std::endl;
        return getInputMove(color); 
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

#line 87 "../src/io.h2"
auto printIntersection(cpp2::impl::in<cpp2::i16> row, cpp2::impl::in<cpp2::i16> col) -> void{
    if ((row == 15 && (col == 3 || col == 9 || col == 15)) || 
       (row == 9 && (col == 3 || col == 9 || col == 15)) || 
       (row ==  3 && (col == 3 || col == 9 || col == 15))) {
        std::cout << "─●";
    }else {
        if (row == 18) {
            if (col == 0) {
                std::cout << " ┌";
            }
            else {if (col == 18) {
                std::cout << "─┐";
            }else {
                std::cout << "─┬";
            }}
        }else {if (row == 0) {
            if (col == 0) {
                std::cout << " └";
            }else {if (col == 18) {
                std::cout << "─┘";
            }else {
                std::cout << "─┴";
            }}
        }else {
            if (col == 0) {
                std::cout << " ├";
            }else {if (col == 18) {
                std::cout << "─┤";
            }else {
                std::cout << "─┼";
            }}
        }}
    }
}

#line 122 "../src/io.h2"
auto printGoban(cpp2::impl::in<Goban> goban) -> void{
    // First line
    std::cout << "     A B C D E F G H J K L M N O P Q R S T " << std::endl;
    cpp2::i8 row {18}; 
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
        for( ; cpp2::impl::cmp_less_eq(col,18); 
        ++col ) 
        {
            if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row).color == 1) {
                std::cout << "⚫";
            }else {if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row).color == 2) {
                std::cout << "⚪";
            }
            else {if (CPP2_ASSERT_IN_BOUNDS(CPP2_ASSERT_IN_BOUNDS(goban.state, col), row).color == 0) {
                printIntersection(row, col);
            }}}
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << getNextMessage() << std::endl;
}

#line 153 "../src/io.h2"
[[nodiscard]] auto getSnnModels() -> std::vector<std::string>{
    std::vector<std::string> modelNames {}; 
    auto files {std::filesystem::directory_iterator("./snn_models")}; 
    for ( 
    auto const& file : cpp2::move(files) ) {
         CPP2_UFCS(push_back)(modelNames, CPP2_UFCS(string)(CPP2_UFCS(path)(file)));
    }
    return modelNames; 
}

#line 163 "../src/io.h2"
[[nodiscard]] auto printPlayersAndSelect(cpp2::impl::in<Color> color) -> std::string{
    clear();
    std::cout << "**************************************************" << std::endl;
    std::cout << "*                    Players                     *" << std::endl;
    std::cout << "**************************************************" << std::endl;
    std::cout << "* Please select " << colorName(color) << " player:" << std::endl;
    std::cout << "*                                                *" << std::endl;
    std::cout << "*     0. Human Player                            *" << std::endl;
    std::cout << "*     1. Random Player                           *" << std::endl;
    auto modelNames {getSnnModels()}; 
{
cpp2::i8 i{0};

#line 174 "../src/io.h2"
    for( ; cpp2::impl::cmp_less(i,CPP2_UFCS(ssize)(modelNames)); 
    ++i ) 
    {
        std::cout << "*     " << cpp2::impl::as_<std::string>((i + 2)) << ". " << CPP2_ASSERT_IN_BOUNDS(modelNames, i) << std::endl;
    }
}
#line 179 "../src/io.h2"
    std::cout << "**************************************************" << std::endl;
    std::cout << std::endl << getNextMessage() << std::endl;
    cpp2::i32 input {0}; 
    std::cout << "> ";
    std::cin >> input;
    clearInput();
    if ((input == 0 || input == 1)) {
        return cpp2::impl::as_<std::string>(input); 
    }
    input -= 2;
    if ((cpp2::impl::cmp_greater_eq(input,0) && cpp2::impl::cmp_less(input,CPP2_UFCS(ssize)(modelNames)))) {
        return CPP2_ASSERT_IN_BOUNDS(cpp2::move(modelNames), cpp2::move(input)); 
    }
    return ""; 
}
#endif

