enum Color: uint8_t {
    None = 0,
    Black = 1,
    White = 2,
};

void switchPlayer(Color& c) {
    if (c == Color::Black) {
        c = Color::White;
    }
    else if (c == Color::White) {
        c =  Color::Black;
    }
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