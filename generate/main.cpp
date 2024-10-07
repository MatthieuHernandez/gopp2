
#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/main.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/main.cpp2"
#include "io.h"

#line 3 "../src/main.cpp2"
[[nodiscard]] auto main() -> int;

//=== Cpp2 function definitions =================================================

#line 1 "../src/main.cpp2"

#line 3 "../src/main.cpp2"
[[nodiscard]] auto main() -> int{
    bool exit {false}; 
    printMenu();
    do {
        int selection {getInputMenu()}; 
        exit = [&] () -> bool { auto&& _expr = cpp2::move(selection);
            if (cpp2::impl::is(_expr, 1)) { if constexpr( requires{[]() -> bool{clear();printGoban();print("Not yet implemented.");return false; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear();printGoban();print("Not yet implemented.");return false; }())),bool> ) return []() -> bool{clear();printGoban();print("Not yet implemented.");return false; }(); else return bool{}; else return bool{}; }

#line 15 "../src/main.cpp2"
           else if (cpp2::impl::is(_expr, 2)) { if constexpr( requires{[]() -> bool{clear("Bye.");return true; }();} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(([]() -> bool{clear("Bye.");return true; }())),bool> ) return []() -> bool{clear("Bye.");return true; }(); else return bool{}; else return bool{}; }

#line 19 "../src/main.cpp2"
            else return []() -> bool{print("Invalid selection.");return false; }(); }

#line 23 "../src/main.cpp2"
        ();
    } while ( !(exit));
  return 0; 
}

