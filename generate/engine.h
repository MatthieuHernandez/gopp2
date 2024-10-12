
#ifndef ENGINE_H_CPP2
#define ENGINE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/engine.h2"

#line 3 "../src/engine.h2"
class Engine;


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/engine.h2"
#include "move.h"

#line 3 "../src/engine.h2"
class Engine {

    private: std::array<Color,361> goban_state {Color::None}; 

    public: static auto start() -> void;

#line 11 "../src/engine.h2"
    public: static auto playMove() -> void;

#line 15 "../src/engine.h2"
    public: [[nodiscard]] static auto isFinish() -> bool;
    public: Engine() = default;
    public: Engine(Engine const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Engine const&) -> void = delete;


#line 18 "../src/engine.h2"
};


//=== Cpp2 function definitions =================================================

#line 1 "../src/engine.h2"

#line 7 "../src/engine.h2"
    auto Engine::start() -> void{

    }

#line 11 "../src/engine.h2"
    auto Engine::playMove() -> void{

    }

#line 15 "../src/engine.h2"
    [[nodiscard]] auto Engine::isFinish() -> bool{
        return false; 
    }
#endif

