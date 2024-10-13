
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
            if (cpp2::impl::is(_expr, 1)) { if constexpr( requires{[]() -> bool{clear();Game game {}; CPP2_UFCS(play)(cpp2::move(game));return false; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear();Game game {}; CPP2_UFCS(play)(cpp2::move(game));return false; }())),bool> ) return []() -> bool{clear();Game game {}; CPP2_UFCS(play)(cpp2::move(game));return false; }(); else return bool{}; else return bool{}; }

#line 19 "../src/main.cpp2"
           else if (cpp2::impl::is(_expr, 2)) { if constexpr( requires{[]() -> bool{clear("Bye.");return true; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear("Bye.");return true; }())),bool> ) return []() -> bool{clear("Bye.");return true; }(); else return bool{}; else return bool{}; }

#line 23 "../src/main.cpp2"
            else return []() -> bool{setNextMessage("Invalid selection.");return false; }(); }

#line 27 "../src/main.cpp2"
        ();
    } while ( !(exit));
  return 0; 
}

