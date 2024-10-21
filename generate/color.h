enum Color: uint8_t {
    None = 0,
    Black = 1,
    White = 2,
};

Color otherColor(const Color& c) {
    if (c == Color::Black) {
        return Color::White;
    }
    else if (c == Color::White) {
        return Color::Black;
    }
    return Color::None;
}

std::string colorName(const Color& c) {
    if (c == Color::Black) {
        return "Black";
    }
    else if (c == Color::White) {
        return "White";
    }
    return "None";
}
