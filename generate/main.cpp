
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
#line 101 "../src/main.cpp2"


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
    do {
        printMenu();
        int selection {getInputMenu()}; 
        exit = [&] () -> bool { auto&& _expr = cpp2::move(selection);
            if (cpp2::impl::is(_expr, 1)) { if constexpr( requires{[]() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));waitInput();return false; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));waitInput();return false; }())),bool> ) return []() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));waitInput();return false; }(); else return bool{}; else return bool{}; }

#line 26 "../src/main.cpp2"
            else if (cpp2::impl::is(_expr, 2)) { if constexpr( requires{[]() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));waitInput();return false; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));waitInput();return false; }())),bool> ) return []() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));waitInput();return false; }(); else return bool{}; else return bool{}; }

#line 36 "../src/main.cpp2"
            else if (cpp2::impl::is(_expr, 3)) { if constexpr( requires{[]() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));waitInput();return false; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));waitInput();return false; }())),bool> ) return []() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));waitInput();return false; }(); else return bool{}; else return bool{}; }

#line 46 "../src/main.cpp2"
            else if (cpp2::impl::is(_expr, 4)) { if constexpr( requires{[]() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::Black, 500)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::White, 500)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));waitInput();return false; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::Black, 500)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::White, 500)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));waitInput();return false; }())),bool> ) return []() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::Black, 500)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::White, 500)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));waitInput();return false; }(); else return bool{}; else return bool{}; }

#line 56 "../src/main.cpp2"
            else if (cpp2::impl::is(_expr, 5)) { if constexpr( requires{[]() -> bool{clear();auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<false>)(cpp2::move(game));waitInput();return false; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear();auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<false>)(cpp2::move(game));waitInput();return false; }())),bool> ) return []() -> bool{clear();auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<false>)(cpp2::move(game));waitInput();return false; }(); else return bool{}; else return bool{}; }

#line 65 "../src/main.cpp2"
            else if (cpp2::impl::is(_expr, 6)) { if constexpr( requires{[]() -> bool{clear();auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, Color::White)}; auto game {Game(player1, player2)}; cpp2::i32 i {0}; while( true ) {CPP2_UFCS_TEMPLATE(play<false>)(game);CPP2_UFCS(train)((*cpp2::impl::assert_not_null(player1)));CPP2_UFCS(train)((*cpp2::impl::assert_not_null(player2)));if (i % 20 == 19) {CPP2_UFCS(save)((*cpp2::impl::assert_not_null(player1)));}++i;}return false; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear();auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, Color::White)}; auto game {Game(player1, player2)}; cpp2::i32 i {0}; while( true ) {CPP2_UFCS_TEMPLATE(play<false>)(game);CPP2_UFCS(train)((*cpp2::impl::assert_not_null(player1)));CPP2_UFCS(train)((*cpp2::impl::assert_not_null(player2)));if (i % 20 == 19) {CPP2_UFCS(save)((*cpp2::impl::assert_not_null(player1)));}++i;}return false; }())),bool> ) return []() -> bool{clear();auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Ai>)(cpp2::shared, Color::White)}; auto game {Game(player1, player2)}; cpp2::i32 i {0}; while( true ) {CPP2_UFCS_TEMPLATE(play<false>)(game);CPP2_UFCS(train)((*cpp2::impl::assert_not_null(player1)));CPP2_UFCS(train)((*cpp2::impl::assert_not_null(player2)));if (i % 20 == 19) {CPP2_UFCS(save)((*cpp2::impl::assert_not_null(player1)));}++i;}return false; }(); else return bool{}; else return bool{}; }

#line 83 "../src/main.cpp2"
            else if (cpp2::impl::is(_expr, 9)) { if constexpr( requires{[]() -> bool{createAi();setNextMessage("AI created.");return false; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{createAi();setNextMessage("AI created.");return false; }())),bool> ) return []() -> bool{createAi();setNextMessage("AI created.");return false; }(); else return bool{}; else return bool{}; }
                //clear();

#line 89 "../src/main.cpp2"
           else if (cpp2::impl::is(_expr, 0)) { if constexpr( requires{[]() -> bool{clear("Bye.");return true; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear("Bye.");return true; }())),bool> ) return []() -> bool{clear("Bye.");return true; }(); else return bool{}; else return bool{}; }

#line 93 "../src/main.cpp2"
            else return []() -> bool{setNextMessage("Invalid selection.");return false; }(); }

#line 97 "../src/main.cpp2"
        ();
    } while ( !(exit));
  return 0; 
}

