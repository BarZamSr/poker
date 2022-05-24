#include <iostream>

#include "Card.h"

std::string Card::to_str() const {
    char buffer[50];
    std::string retval;
    sprintf(buffer, "%5s", get_rank().c_str());
    retval += buffer;
    retval += " of ";
    sprintf(buffer, "%-8s", get_suit().c_str());
    retval += buffer;
    return retval;
}

Rank Card::get_rank() const {
    return std::get<Rank>(*this);
}
Suit Card::get_suit() const {
    return std::get<Suit>(*this);
}


bool Card::is_rank(Rank rank) const {
    return rank == get_rank();
}
bool Card::is_suit(Suit suit) const {
    return suit == get_suit();
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}
