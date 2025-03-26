
#ifndef COLOR_H_CPP2
#error This file is part of a '.h2' header compiled to be consumed from another -pure-cpp2 file. To use this file, write '#include "color.h2"' in a '.h2' or '.cpp2' file compiled with -pure-cpp2.
#endif

#ifndef COLOR_HPP_CPP2
#define COLOR_HPP_CPP2



//=== Cpp2 function definitions =================================================

#line 1 "../src/color.h2"

#line 1 "../src/color.h2"

 constexpr Color::Color(cpp2::impl::in<cpp2::i64> _val)
                                                          : _value{ cpp2::unchecked_narrow<cpp2::i8>(_val) } {  }
constexpr auto Color::operator=(cpp2::impl::in<cpp2::i64> _val) -> Color&  { 
                                                          _value = cpp2::unchecked_narrow<cpp2::i8>(_val);
                                                          return *this; }
inline CPP2_CONSTEXPR Color Color::None{ 0 };

inline CPP2_CONSTEXPR Color Color::Black{ 1 };

inline CPP2_CONSTEXPR Color Color::White{ 2 };

[[nodiscard]] constexpr auto Color::get_raw_value() const& -> cpp2::i8 { return _value; }
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
#line 1 "../src/color.h2"
}}
CPP2_UFCS(report_violation)(cpp2::type_safety, CPP2_UFCS(c_str)(("can't convert string '" + cpp2::to_string(s) + "' to enum of type Color")));
return None; 
}

[[nodiscard]] auto Color::from_code(cpp2::impl::in<std::string_view> s) -> Color{
std::string str {s}; return from_string(cpp2::string_util::replace_all(cpp2::move(str), "Color::", "")); }

#line 7 "../src/color.h2"
[[nodiscard]] auto otherColor(cpp2::impl::in<Color> c) -> Color{
    if (c == Color::Black) {
        return Color::White; 
    }
    else {if (c == Color::White) {
        return Color::Black; 
    }}
    return Color::None; 
}

#line 17 "../src/color.h2"
 [[nodiscard]] auto colorName(cpp2::impl::in<Color> c) -> std::string{
    if (c == Color::Black) {
        return "Black"; 
    }
    else {if (c == Color::White) {
        return "White"; 
    }}
    return "None"; 
}
#endif

