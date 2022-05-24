#include "Rank.h"
#include "Suit.h"

class Card: std::pair<Rank,Suit> {
public:
    std::string to_str() const;
    friend std::ostream& operator<<(std::ostream&, const Card&);

    Rank get_rank() const;
    Suit get_suit() const;

    bool is_rank(Rank) const;
    bool is_suit(Suit) const;

    using std::pair<Rank,Suit>::pair;
};
