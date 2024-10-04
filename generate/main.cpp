

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/main.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/main.cpp2"
#define CPP2_IMPORT_STD

#include "../src/io.h"

#line 5 "../src/main.cpp2"
[[nodiscard]] auto main() -> int;

//=== Cpp2 function definitions =================================================

#line 1 "../src/main.cpp2"

#line 5 "../src/main.cpp2"
[[nodiscard]] auto main() -> int{
    int result {0}; 
    std::string message {""}; 
    do {
        printMenu(message);
        int selection {getResponseMenu()}; 
        std::tie(result, message) = processResponseMenu(cpp2::move(selection));
    } while ( (result != 0));
  return result; 
}

