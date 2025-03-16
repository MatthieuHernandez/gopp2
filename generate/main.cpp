
#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/main.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/main.cpp2"
#include "io.h"
#include "game.h"
#include "../src/gui.h"

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

#line 33 "../src/main.cpp2"
[[nodiscard]] auto cpp2_main() -> int;
#line 63 "../src/main.cpp2"

/*int main() {
    try { // CPP2 workaround: Try catch not yet supported.
        return cpp2_main();
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}*/


#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Window window;
    window.show();
    return app.exec();
}


//=== Cpp2 function definitions =================================================

#line 1 "../src/main.cpp2"

#line 33 "../src/main.cpp2"
[[nodiscard]] auto cpp2_main() -> int{
    windowsConfig();
    signal(SIGINT, signalHandler);
    bool exit {false}; 
    auto game {Game()}; 
    do {
        auto size {CPP2_UFCS(getGobanSize)(game)}; 
        auto players {CPP2_UFCS(getPlayerNames)(game)}; 
        auto selection {printMenuAndSelect(cpp2::move(size), cpp2::move(players))}; 
        if (selection == 0) {
            clear("Bye.");
            exit = true;
        }else {if (selection == 1) {
            CPP2_UFCS(changeGobanSize)(game);
        }else {if (selection == 2) {
            CPP2_UFCS(selectPlayers)(game);
        }else {if (selection == 3) {
            CPP2_UFCS(playOne)(game);
        }else {if (selection == 4) {
            CPP2_UFCS(trainBlack)(game);
        }else {if (selection == 5) {
            CPP2_UFCS(evaluate)(game);
        }else {if (cpp2::move(selection) == 9) {
            createAi();
        }else {
            setNextMessage("Invalid selection.");
        }}}}}}}
    } while ( !(exit));
  return 0; 
}

