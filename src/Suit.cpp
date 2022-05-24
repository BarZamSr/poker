#include <stdexcept>
#include "Suit.h"

const std::set<std::string> Suit::names = {
    "hearts", "spades", "clubs", "diamonds"
};

Suit::Suit(std::string name): std::string(name) {
    if (!(names.contains(name))) {
        throw std::domain_error("suit name");
    }
}

bool Suit::operator==(const Suit& other) const {
    return static_cast<std::string>(*this) == static_cast<std::string>(other);
}

std::ostream& operator<<(std::ostream& os, const Suit& suit) {
    os << static_cast<std::string>(suit);
    return os;
}
