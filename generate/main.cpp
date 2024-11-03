
#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/main.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/main.cpp2"
#include "windows.h"

#include "io.h"
#include "game.h"

#line 6 "../src/main.cpp2"
[[nodiscard]] auto main() -> int;

//=== Cpp2 function definitions =================================================

#line 1 "../src/main.cpp2"

#line 6 "../src/main.cpp2"
[[nodiscard]] auto main() -> int{
    SetConsoleOutputCP(CP_UTF8);
    bool exit {false}; 
    do {
        printMenu();
        int selection {getInputMenu()}; 
        exit = [&] () -> bool { auto&& _expr = cpp2::move(selection);
            if (cpp2::impl::is(_expr, 1)) { if constexpr( requires{[]() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));return false; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));return false; }())),bool> ) return []() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));return false; }(); else return bool{}; else return bool{}; }

#line 22 "../src/main.cpp2"
            else if (cpp2::impl::is(_expr, 2)) { if constexpr( requires{[]() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));return false; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));return false; }())),bool> ) return []() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Human>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));return false; }(); else return bool{}; else return bool{}; }

#line 31 "../src/main.cpp2"
            else if (cpp2::impl::is(_expr, 3)) { if constexpr( requires{[]() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::Black, 500)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::White, 500)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));return false; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::Black, 500)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::White, 500)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));return false; }())),bool> ) return []() -> bool{clear();setNextMessage("Start a new game.");auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::Black, 500)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<RandomSlow>)(cpp2::shared, Color::White, 500)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<true>)(cpp2::move(game));return false; }(); else return bool{}; else return bool{}; }

#line 40 "../src/main.cpp2"
            else if (cpp2::impl::is(_expr, 4)) { if constexpr( requires{[]() -> bool{clear();auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<false>)(cpp2::move(game));return false; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear();auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<false>)(cpp2::move(game));return false; }())),bool> ) return []() -> bool{clear();auto player1 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::Black)}; auto player2 {CPP2_UFCS_TEMPLATE(cpp2_new<Random>)(cpp2::shared, Color::White)}; auto game {Game(cpp2::move(player1), cpp2::move(player2))}; CPP2_UFCS_TEMPLATE(play<false>)(cpp2::move(game));return false; }(); else return bool{}; else return bool{}; }

#line 48 "../src/main.cpp2"
           else if (cpp2::impl::is(_expr, 0)) { if constexpr( requires{[]() -> bool{clear("Bye.");return true; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear("Bye.");return true; }())),bool> ) return []() -> bool{clear("Bye.");return true; }(); else return bool{}; else return bool{}; }

#line 52 "../src/main.cpp2"
            else return []() -> bool{setNextMessage("Invalid selection.");return false; }(); }

#line 56 "../src/main.cpp2"
        ();
    } while ( !(exit));
  return 0; 
}

