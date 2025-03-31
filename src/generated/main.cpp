
#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../cpp2/main.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../cpp2/main.cpp2"

#include <QApplication>
#include "window.h"
#include "game.h"
#include "gui_interface.h"
#include "cli_interface.h"
#include "cli.h"
#include "interface.h"

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

static std::unique_ptr<Game> game = nullptr;

void signalHandler(int signal) {
    if (signal == SIGINT) {
        while(game != nullptr && !game->canBeStopped()) {
            std::cout << "Cannot stop, saving in progress..." << std::endl;
            using namespace std::literals::chrono_literals;
            std::this_thread::sleep_for(10ms);
        }
        std::exit(0);
    }
}

#line 41 "../cpp2/main.cpp2"
[[nodiscard]] auto cliApp() -> int;
#line 83 "../cpp2/main.cpp2"

int main(int argc, char *argv[]) {
    if (argc > 1 && static_cast<std::string>(argv[1]) == "nogui") {
        try { // CPP2 workaround: Try catch not yet supported.
            return cliApp();
        } catch (const std::exception& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        }
    }
    else {
        auto guiInterface = GuiInterface();
        auto game = std::make_unique<Game>(&guiInterface);
        auto guiApp = QApplication(argc, argv);
        auto window = Window(&guiInterface, game.get());
        guiInterface.window = &window;
        window.show();
        return guiApp.exec();
    }
    return 0;
}


//=== Cpp2 function definitions =================================================

#line 1 "../cpp2/main.cpp2"

#line 41 "../cpp2/main.cpp2"
[[nodiscard]] auto cliApp() -> int{
    windowsConfig();
    bool exit {false}; 
    auto cliInterface {CliInterface()}; 
    auto game {CPP2_UFCS_TEMPLATE(cpp2_new<Game>)(cpp2::unique, &cliInterface)}; 
    signal(SIGINT, signalHandler);
    do {
        auto size {CPP2_UFCS(getGobanSize)((*cpp2::impl::assert_not_null(game)))}; 
        auto players {CPP2_UFCS(getPlayerNames)((*cpp2::impl::assert_not_null(game)))}; 
        auto selection {cli::printMenuAndSelect(size, cpp2::move(players))}; 
        if (selection == 0) {
            CPP2_UFCS(clear)(cliInterface);
            CPP2_UFCS(print)(cliInterface, "Bye.");
            exit = true;
        }else {if (selection == 1) {
        if ((CPP2_UFCS(getGobanSize)((*cpp2::impl::assert_not_null(game))) == 9)) {
            CPP2_UFCS(setGobanSize)((*cpp2::impl::assert_not_null(game)), 13);
        }else {if ((CPP2_UFCS(getGobanSize)((*cpp2::impl::assert_not_null(game))) == 13)) {
            CPP2_UFCS(setGobanSize)((*cpp2::impl::assert_not_null(game)), 19);
        }else {if ((CPP2_UFCS(getGobanSize)((*cpp2::impl::assert_not_null(game))) == 19)) {
            CPP2_UFCS(setGobanSize)((*cpp2::impl::assert_not_null(game)), 9);
        }}}
        }else {if (selection == 2) {
            auto selection {cli::printPlayersAndSelect(size, Color::Black)}; 
            CPP2_UFCS(selectPlayer)((*cpp2::impl::assert_not_null(game)), Color::Black, selection);
            selection = cli::printPlayersAndSelect(cpp2::move(size), Color::White);
            CPP2_UFCS(selectPlayer)((*cpp2::impl::assert_not_null(game)), Color::White, cpp2::move(selection));
            CPP2_UFCS(print)(cliInterface, "Players selected.");
        }else {if (selection == 3) {
            CPP2_UFCS(playOne)((*cpp2::impl::assert_not_null(game)));
        }else {if (selection == 4) {
            CPP2_UFCS(trainBlack)((*cpp2::impl::assert_not_null(game)));
        }else {if (selection == 5) {
            CPP2_UFCS(evaluate)((*cpp2::impl::assert_not_null(game)));
        }else {if (cpp2::move(selection) == 9) {
            createAi();
        }else {
            CPP2_UFCS(print)(cliInterface, "Invalid selection.");
        }}}}}}}
    } while ( !(exit));
  return 0; 
}

