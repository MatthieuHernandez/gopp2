
#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/main.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/main.cpp2"
#include "windows.h"

#include "io.h"
#include "game.h"

void signalHandler(int signal) {
    if (signal == SIGINT) {
        while(isSaving) {
            std::cout << "Cannot stop, saving in progress..." << std::endl;
        }
        std::exit(0);
    }
}

#line 15 "../src/main.cpp2"
[[nodiscard]] auto cpp2_main() -> int;
#line 42 "../src/main.cpp2"

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

#line 15 "../src/main.cpp2"
[[nodiscard]] auto cpp2_main() -> int{
    signal(SIGINT, signalHandler);
    SetConsoleOutputCP(CP_UTF8);
    bool exit {false}; 
    auto game {Game()}; 
    do {
        auto selection {printMenuAndSelect()}; 
        if (selection == 0) {
            clear("Bye.");
            exit = true;
        }else {if (selection == 1) {
            CPP2_UFCS(selectPlayers)(game);
        }else {if (selection == 2) {
            CPP2_UFCS(playOne)(game);
        }else {if (selection == 3) {
            CPP2_UFCS(trainBlack)(game);
        }else {if (selection == 4) {
            CPP2_UFCS(evaluate)(game);
        }else {if (cpp2::move(selection) == 9) {
            createAi();
            setNextMessage("AI created.");
        }else {
            setNextMessage("Invalid selection.");
        }}}}}}
    } while ( !(exit));
  return 0; 
}

