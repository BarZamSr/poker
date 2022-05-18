#include <iostream>

#include "Card.h"

Card::Card(Rank r, Suit s): rank(r), suit(s) {}

bool Card::is_rank(Rank r) { return rank==r; }

std::string Card::to_str() const {
    char buffer[50];
    std::string retval;
    sprintf(buffer, "%5s", rank.to_str().c_str());
    retval += buffer;
    retval += " of ";
    sprintf(buffer, "%-8s", suit.c_str());
    retval += buffer;
    return retval;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.rank << " of " << (card.suit);
    return os;
}
