
#ifndef MOVE_H_CPP2
#define MOVE_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/move.h2"
class Color;
#line 2 "../src/move.h2"
    

#line 7 "../src/move.h2"
class Move;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/move.h2"
class Color {
private: cpp2::u8 _value; private: constexpr Color(cpp2::impl::in<cpp2::i64> _val);

private: constexpr auto operator=(cpp2::impl::in<cpp2::i64> _val) -> Color& ;
public: static const Color None;
public: static const Color Black;
public: static const Color White;
public: [[nodiscard]] constexpr auto get_raw_value() const& -> cpp2::u8;
public: constexpr explicit Color();
public: constexpr Color(Color const& that);
public: constexpr auto operator=(Color const& that) -> Color& ;
public: constexpr Color(Color&& that) noexcept;
public: constexpr auto operator=(Color&& that) noexcept -> Color& ;
public: [[nodiscard]] auto operator<=>(Color const& that) const& -> std::strong_ordering = default;
public: [[nodiscard]] auto to_string_impl(cpp2::impl::in<std::string_view> prefix) const& -> std::string;
public: [[nodiscard]] auto to_string() const& -> std::string;
public: [[nodiscard]] auto to_code() const& -> std::string;
public: [[nodiscard]] static auto from_string(cpp2::impl::in<std::string_view> s) -> Color;
public: [[nodiscard]] static auto from_code(cpp2::impl::in<std::string_view> s) -> Color;

#line 5 "../src/move.h2"
};

class Move {
    private: Color color; 
    private: std::array<cpp2::u8,2> position; 
    private: bool pass; 

    public: explicit Move(cpp2::impl::in<Color> col, cpp2::impl::in<std::array<cpp2::u8,2>> pos = {}, cpp2::impl::in<bool> pas = false);

#line 18 "../src/move.h2"
    public: Move(Move const& that);
#line 18 "../src/move.h2"
    public: auto operator=(Move const& that) -> Move& ;
#line 18 "../src/move.h2"
    public: Move(Move&& that) noexcept;
#line 18 "../src/move.h2"
    public: auto operator=(Move&& that) noexcept -> Move& ;

};

auto switchPlayer(Color& color) -> void;

//=== Cpp2 function definitions =================================================

#line 1 "../src/move.h2"

#line 1 "../src/move.h2"

constexpr Color::Color(cpp2::impl::in<cpp2::i64> _val)
                                                          : _value{ cpp2::unchecked_narrow<cpp2::u8>(_val) } {  }
constexpr auto Color::operator=(cpp2::impl::in<cpp2::i64> _val) -> Color&  { 
                                                          _value = cpp2::unchecked_narrow<cpp2::u8>(_val);
                                                          return *this; }
inline CPP2_CONSTEXPR Color Color::None{ 0 };

inline CPP2_CONSTEXPR Color Color::Black{ 1 };

inline CPP2_CONSTEXPR Color Color::White{ 2 };

[[nodiscard]] constexpr auto Color::get_raw_value() const& -> cpp2::u8 { return _value; }
constexpr Color::Color()
                                        : _value{ None._value }{}
constexpr Color::Color(Color const& that)
                                              : _value{ that._value }{}
constexpr auto Color::operator=(Color const& that) -> Color& {
                                              _value = that._value;
                                              return *this;}
constexpr Color::Color(Color&& that) noexcept
                                              : _value{ std::move(that)._value }{}
constexpr auto Color::operator=(Color&& that) noexcept -> Color& {
                                              _value = std::move(that)._value;
                                              return *this;}
[[nodiscard]] auto Color::to_string_impl(cpp2::impl::in<std::string_view> prefix) const& -> std::string{

auto pref {cpp2::to_string(prefix)}; 
if ((*this) == None) {return pref + "None"; }
if ((*this) == Black) {return pref + "Black"; }
if ((*this) == White) {return cpp2::move(pref) + "White"; }
return "invalid Color value"; 
}

[[nodiscard]] auto Color::to_string() const& -> std::string { return to_string_impl(""); }
[[nodiscard]] auto Color::to_code() const& -> std::string { return to_string_impl("Color::"); }
[[nodiscard]] auto Color::from_string(cpp2::impl::in<std::string_view> s) -> Color{

auto x {s}; 
if ("None" == x) {return None; }
else {if ("Black" == x) {return Black; }
else {if ("White" == cpp2::move(x)) {return White; }
#line 1 "../src/move.h2"
}}
CPP2_UFCS(report_violation)(cpp2::type_safety, CPP2_UFCS(c_str)(("can't convert string '" + cpp2::to_string(s) + "' to enum of type Color")));
return None; 
}

[[nodiscard]] auto Color::from_code(cpp2::impl::in<std::string_view> s) -> Color{
std::string str {s}; return from_string(cpp2::string_util::replace_all(cpp2::move(str), "Color::", "")); }

#line 12 "../src/move.h2"
    Move::Move(cpp2::impl::in<Color> col, cpp2::impl::in<std::array<cpp2::u8,2>> pos, cpp2::impl::in<bool> pas)
        : color{ col }
        , position{ pos }
        , pass{ pas }{

#line 16 "../src/move.h2"
    }

#line 18 "../src/move.h2"
    Move::Move(Move const& that)
    : color{ that.color }
    , position{ that.position }
    , pass{ that.pass }{
#line 19 "../src/move.h2"
    }
#line 18 "../src/move.h2"
    auto Move::operator=(Move const& that) -> Move& {
    color = that.color;
    position = that.position;
    pass = that.pass;
    return *this;
#line 19 "../src/move.h2"
    }
#line 18 "../src/move.h2"
    Move::Move(Move&& that) noexcept
    : color{ std::move(that).color }
    , position{ std::move(that).position }
    , pass{ std::move(that).pass }{
#line 19 "../src/move.h2"
    }
#line 18 "../src/move.h2"
    auto Move::operator=(Move&& that) noexcept -> Move& {
    color = std::move(that).color;
    position = std::move(that).position;
    pass = std::move(that).pass;
    return *this;
#line 19 "../src/move.h2"
    }

#line 22 "../src/move.h2"
auto switchPlayer(Color& color) -> void{
    if ((color == Color::Black)) 
    {
        color = Color::Black;
    }
    else {if ((color == Color::White)) {
        color =  Color::White;
    }}
}
#endif

