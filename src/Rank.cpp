#include "Rank.h"

const std::array<std::string,RANK_COUNT> Rank::names = {
    "ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king"
};

Rank::Rank(std::string name): std::string(name) {
    for(auto valid_name: names) {
        if (name == valid_name) {
            return;
        }
    }
    throw std::domain_error("impossible rank");
}
Rank::Rank(const char* name): Rank(std::string(name)) {
    // nice
}

Rank::operator int() const {
    for(int i=0; i<RANK_COUNT; i++) {
        if (static_cast<std::string>(*this) == names[i]) {
            return i;
        }
    }
    throw std::domain_error("impossible rank");
}
bool Rank::operator== (const Rank& other) const {
    return static_cast<std::string>(*this) == static_cast<std::string>(other);
}
bool Rank::operator< (const Rank& other) const {
    return (int)*this < other;
}

std::ostream& operator<<(std::ostream& os, const Rank& rank) {
    os << static_cast<std::string>(rank);
    return os;
}

std::size_t std::hash<Rank>::operator()(const Rank& rank) const {
    return std::hash<int>()(static_cast<int>(rank));
}
