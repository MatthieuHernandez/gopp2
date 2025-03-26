
#ifndef STONE_H_CPP2
#define STONE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/stone.h2"

#line 3 "../src/stone.h2"
class Stone;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/stone.h2"
#include "color.h"

#line 3 "../src/stone.h2"
class Stone {
    public: Color color; 
    public: cpp2::i8 col; 
    public: cpp2::i8 row; 
    public: float estimation; 

#line 10 "../src/stone.h2"
    public: Stone();

#line 17 "../src/stone.h2"
    public: Stone(cpp2::impl::in<Color> p, cpp2::impl::in<cpp2::i8> c, cpp2::impl::in<cpp2::i8> r, cpp2::impl::in<float> e = 0.0f);

#line 24 "../src/stone.h2"
    public: Stone(Stone const& that);
#line 24 "../src/stone.h2"
    public: auto operator=(Stone const& that) -> Stone& ;
#line 24 "../src/stone.h2"
    public: Stone(Stone&& that) noexcept;
#line 24 "../src/stone.h2"
    public: auto operator=(Stone&& that) noexcept -> Stone& ;

#line 30 "../src/stone.h2"
    public: template<cpp2::i8 Size> [[nodiscard]] auto getIndex() const& -> cpp2::i16;

#line 34 "../src/stone.h2"
    public: [[nodiscard]] auto operator<=>(Stone const& that) const& -> std::strong_ordering = default;
};

#endif
