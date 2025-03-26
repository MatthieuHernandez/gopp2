
#ifndef COLOR_H_CPP2
#define COLOR_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "../src/color.h2"
class Color;
#line 2 "../src/color.h2"
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "../src/color.h2"
class Color {
private: cpp2::i8 _value; private: constexpr Color(cpp2::impl::in<cpp2::i64> _val);

private: constexpr auto operator=(cpp2::impl::in<cpp2::i64> _val) -> Color& ;
public: static const Color None;
public: static const Color Black;
public: static const Color White;
public: [[nodiscard]] constexpr auto get_raw_value() const& -> cpp2::i8;
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

#line 5 "../src/color.h2"
};

[[nodiscard]] auto otherColor(cpp2::impl::in<Color> c) -> Color;

#line 17 "../src/color.h2"
 [[nodiscard]] auto colorName(cpp2::impl::in<Color> c) -> std::string;
#endif
