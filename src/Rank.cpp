#include "Rank.h"

const std::array<std::string, RANK_COUNT> Rank::names{"ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king"};
Rank::Rank(int r) {
    assert(r >= 0);
    assert(r < RANK_COUNT);
    value = r;
}

std::string Rank::to_str() const {
    return names[value];
}

Rank Rank::operator++ () {
    assert(value+1 < RANK_COUNT);
    value++;
    return Rank(value+1);
}

bool Rank::operator== (Rank other) const {
    return value == other.value;
}

std::ostream& operator<<(std::ostream& os, const Rank& rank) {
    os << rank.to_str();
    return os;
}
