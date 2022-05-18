#pragma once

#include "Rank.h"
#include "Suit.h"

class Card {
    Rank rank;
    Suit suit;
public:
    Card(Rank, Suit);
    bool is_rank(Rank);
    std::string to_str() const;
    friend std::ostream& operator<<(std::ostream&, const Card&);
};
