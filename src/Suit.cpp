#include "Suit.h"

const std::set<std::string> Suit::names = {
    "hearts", "spades", "clubs", "diamonds"
};

Suit::Suit(std::string name) {

    if (names.contains(name)) {
        *this = name;
    }
}

/*
std::ostream& operator<<(std::ostream& os, const Suit& suit) {
    os << suit;
    return os;
}
*/
