
#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/main.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/main.cpp2"
#include "cli_interface.h"
#include "game.h"
#include "interface.h"
#include "../src/window.h"

#ifdef _WIN32
#include "windows.h"
#endif

constexpr bool win32 =
#ifdef _WIN32
    true;
#else
    false;
#endif

void windowsConfig() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
}


void signalHandler(int signal) {
    if (signal == SIGINT) {
        while(isRunning) {
            std::cout << "Cannot stop, saving in progress..." << std::endl;
            std::this_thread::sleep_for(10ms);
        }
        std::exit(0);
    }
}

#line 34 "../src/main.cpp2"
[[nodiscard]] auto cliApp() -> int;
#line 76 "../src/main.cpp2"


#include <QApplication>

int main(int argc, char *argv[]) {

    if (argc > 1 && static_cast<std::string>(argv[1]) == "nogui") {
        try { // CPP2 workaround: Try catch not yet supported.
            return cliApp();
        } catch (const std::exception& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        }
    }
    else {
        QApplication guiApp(argc, argv);
        Window window;
        window.show();
        return guiApp.exec();
    }
    return 0;
}


//=== Cpp2 function definitions =================================================

#line 1 "../src/main.cpp2"

#line 34 "../src/main.cpp2"
[[nodiscard]] auto cliApp() -> int{
    windowsConfig();
    signal(SIGINT, signalHandler);
    bool exit {false}; 
    auto cliInterface {CliInterface()}; 
    auto game {Game(&cliInterface)}; 
    do {
        auto size {CPP2_UFCS(getGobanSize)(game)}; 
        auto players {CPP2_UFCS(getPlayerNames)(game)}; 
        auto selection {printMenuAndSelect(size, cpp2::move(players))}; 
        if (selection == 0) {
            CPP2_UFCS(clear)(cliInterface);
            CPP2_UFCS(print)(cliInterface, "Bye.");
            exit = true;
        }else {if (selection == 1) {
        if ((CPP2_UFCS(getGobanSize)(game) == 9)) {
            CPP2_UFCS(setGobanSize)(game, 13);
        }else {if ((CPP2_UFCS(getGobanSize)(game) == 13)) {
            CPP2_UFCS(setGobanSize)(game, 19);
        }else {if ((CPP2_UFCS(getGobanSize)(game) == 19)) {
            CPP2_UFCS(setGobanSize)(game, 9);
        }}}
        }else {if (selection == 2) {
            auto selection {printPlayersAndSelect(size, Color::Black)}; 
            CPP2_UFCS(selectPlayer)(game, Color::Black, selection);
            selection = printPlayersAndSelect(cpp2::move(size), Color::White);
            CPP2_UFCS(selectPlayer)(game, Color::White, cpp2::move(selection));
            CPP2_UFCS(print)(cliInterface, "Players selected.");
        }else {if (selection == 3) {
            CPP2_UFCS(playOne)(game);
        }else {if (selection == 4) {
            CPP2_UFCS(trainBlack)(game);
        }else {if (selection == 5) {
            CPP2_UFCS(evaluate)(game);
        }else {if (cpp2::move(selection) == 9) {
            createAi();
        }else {
            CPP2_UFCS(print)(cliInterface, "Invalid selection.");
        }}}}}}}
    } while ( !(exit));
  return 0; 
}

