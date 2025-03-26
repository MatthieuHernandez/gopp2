
#ifndef ENGINE_H_CPP2
#define ENGINE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/engine.h2"

#line 4 "../src/engine.h2"
template<cpp2::i8 Size> class Engine;


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/engine.h2"
#include "goban.h"
#include "move.h"

#line 4 "../src/engine.h2"
template<cpp2::i8 Size> class Engine {

    public: Goban<Size> goban {}; 
    public: std::vector<Move> moves {}; 
    public: std::vector<std::array<std::array<Stone,Size>,Size>> states {}; 

    public: cpp2::i16 blackPoint {0}; 
    public: cpp2::i16 whitePoint {0}; 

    public: explicit Engine();

#line 18 "../src/engine.h2"
    public: auto playMove(Move& m) & -> void;

#line 34 "../src/engine.h2"
    private: auto countLiberties(cpp2::impl::in<Stone> stone, cpp2::i16& count, State<bool,Size>& processedStones) & -> void;

#line 62 "../src/engine.h2"
    private: [[nodiscard]] auto numberOfLiberties(Stone& stone) & -> cpp2::i16;

#line 70 "../src/engine.h2"
    private: auto removeGroup(Stone& stone, cpp2::i16& count, State<bool,Size>& processedStones) & -> void;

#line 83 "../src/engine.h2"
    private: [[nodiscard]] auto captureStones(Stone& stone) & -> cpp2::i16;

#line 105 "../src/engine.h2"
    public: [[nodiscard]] auto isValidMove(Move& m) & -> bool;

#line 129 "../src/engine.h2"
    public: [[nodiscard]] auto isFinish() const& -> bool;

#line 139 "../src/engine.h2"
    private: auto countTerritory(cpp2::impl::in<Stone> stone, cpp2::i16& count, Color& color, 
        State<bool,Size>& processedStones1, State<bool,Size>& processedStones2) & -> void;

#line 168 "../src/engine.h2"
    public: auto countScore() & -> void;

#line 206 "../src/engine.h2"
    private: auto findValidMove(Move& m, State<bool,Size>& processedStones, cpp2::i32& count) & -> void;

#line 225 "../src/engine.h2"
    public: auto closerValidMove(Move& m) & -> void;
    public: Engine(Engine const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(Engine const&) -> void = delete;


#line 238 "../src/engine.h2"
};

#endif
