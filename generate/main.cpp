
#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/main.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/main.cpp2"
#include "windows.h"

#include "io.h"
#include "game.h"
#include "human.h"
#include "random.h"
#include "ai.h"

#line 9 "../src/main.cpp2"
[[nodiscard]] auto cpp2_main() -> int;
#line 91 "../src/main.cpp2"


int main() {
    try { // CPP2 workaround: Try catch not yet supported.
        return cpp2_main();
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}


//=== Cpp2 function definitions =================================================

#line 1 "../src/main.cpp2"

#line 9 "../src/main.cpp2"
[[nodiscard]] auto cpp2_main() -> int{
    SetConsoleOutputCP(CP_UTF8);
    bool exit {false}; 
    std::string modelName {""}; 
    do {
        printMenu();
        int selection {getInputMenu()}; 
        if (selection == 0) {
            clear("Bye.");
            exit = true;
        }else {if (selection == 1) {
            clear();
            setNextMessage("Start a new game.");
            auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; 
            auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::White)}; 
            auto game {Game(cpp2::move(player1), cpp2::move(player2))}; 
            CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));
            waitInput();
        }else {if (selection == 2) {
            clear();
            setNextMessage("Start a new game.");
            auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; 
            auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::White)}; 
            auto game {Game(cpp2::move(player1), cpp2::move(player2))}; 
            CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));
            waitInput();
        }else {if (selection == 3) {
            clear();
            setNextMessage("Start a new game.");
            auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; 
            auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, Color::White)}; 
            auto game {Game(cpp2::move(player1), cpp2::move(player2))}; 
            CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));
            waitInput();
        }else {if (selection == 4) {
            clear();
            setNextMessage("Start a new game.");
            auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::Black, 500)}; 
            auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::White, 500)}; 
            auto game {Game(cpp2::move(player1), cpp2::move(player2))}; 
            CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));
            waitInput();
        }else {if (selection == 5) {
                clear();
                auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::Black)}; 
                auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::White)}; 
                auto game {Game(cpp2::move(player1), cpp2::move(player2))}; 
                CPP2_UFCS_TEMPLATE(play<false>)(cpp2::move(game));
                waitInput();
        }else {if (selection == 6) {
            clear();
            if (modelName == "") {
                setNextMessage("No model selected.");
                continue;
            }
            auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, Color::Black)}; 
            auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, Color::White)}; 
            auto game {Game(player1, player2)}; 
            cpp2::i32 i {0}; 
            while( true ) 
            {
                CPP2_UFCS_TEMPLATE(play<false>)(game);
                CPP2_UFCS(train)((*cpp2::impl::assert_not_null(player1)));
                CPP2_UFCS(train)((*cpp2::impl::assert_not_null(player2)));
                if (i % 20 == 19) {
                    CPP2_UFCS(save)((*cpp2::impl::assert_not_null(player1)));
                }
                ++i;
            }
        }else {if (selection == 7) {
            clear();
            modelName = SelectSnnModel();
            setNextMessage(modelName + " selected.");
        }else {if (cpp2::move(selection) == 9) {
                createAi();
                setNextMessage("AI created.");
        }else {
            setNextMessage("Invalid selection.");
        }}}}}}}}}
    } while ( !(exit));
  return 0; 
}

