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
    throw std::domain_error("rank name");
}
Rank::Rank(const char* name): Rank(std::string(name)) {
    // nice
}

bool Rank::operator== (const Rank& other) const {
    return static_cast<std::string>(*this) == static_cast<std::string>(other);
}
bool Rank::operator< (const Rank& other) const {
    return get_number() < other.get_number();
}

unsigned int Rank::get_number() const {
    for(int i=0; i<RANK_COUNT; i++) {
        if (static_cast<std::string>(*this) == names[i]) {
            return i;
        }
    }
    throw std::domain_error("impossible rank");
}

std::ostream& operator<<(std::ostream& os, const Rank& rank) {
    os << static_cast<std::string>(rank);
    return os;
}
