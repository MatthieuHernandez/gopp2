
#ifndef MOVE_H_CPP2
#define MOVE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/move.h2"

#line 3 "../src/move.h2"
class Move;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/move.h2"
#include "color.h"

#line 3 "../src/move.h2"
class Move {
    private: std::array<cpp2::u8,2> position; 
    private: Color color; 
    public: Move() = default;
    public: Move(Move const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Move const&) -> void = delete;

#line 6 "../src/move.h2"
};

#line 1 "../src/move.h2"

//=== Cpp2 function definitions =================================================

#line 1 "../src/move.h2"

#endif
