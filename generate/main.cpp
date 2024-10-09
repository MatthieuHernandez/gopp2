
#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/main.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/main.cpp2"
#include "io.h"
#include "engine.h"

#line 4 "../src/main.cpp2"
[[nodiscard]] auto main() -> int;

//=== Cpp2 function definitions =================================================

#line 1 "../src/main.cpp2"

#line 4 "../src/main.cpp2"
[[nodiscard]] auto main() -> int{
    bool exit {false}; 
    printMenu();
    do {
        int selection {getInputMenu()}; 
        exit = [&] () -> bool { auto&& _expr = cpp2::move(selection);
            if (cpp2::impl::is(_expr, 1)) { if constexpr( requires{[]() -> bool{clear();Engine engine {}; CPP2_UFCS(startGame)(cpp2::move(engine));return false; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear();Engine engine {}; CPP2_UFCS(startGame)(cpp2::move(engine));return false; }())),bool> ) return []() -> bool{clear();Engine engine {}; CPP2_UFCS(startGame)(cpp2::move(engine));return false; }(); else return bool{}; else return bool{}; }

#line 16 "../src/main.cpp2"
           else if (cpp2::impl::is(_expr, 2)) { if constexpr( requires{[]() -> bool{clear("Bye.");return true; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear("Bye.");return true; }())),bool> ) return []() -> bool{clear("Bye.");return true; }(); else return bool{}; else return bool{}; }

#line 20 "../src/main.cpp2"
            else return []() -> bool{print("Invalid selection.");return false; }(); }

#line 24 "../src/main.cpp2"
        ();
    } while ( !(exit));
  return 0; 
}

