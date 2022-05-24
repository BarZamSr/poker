#include <vector>

#include "Card.h"

class CardList: std::vector<Card> {
public:
    int count(Rank);
    void shuffle();
    void sort();

    Card draw();
    CardList draw(int);
    Card draw(Rank);

    std::vector<CardList> combinations(int) const;
    CardList operator+ (const CardList&) const;

    using std::vector<Card>::operator[];

    using std::vector<Card>::begin;
    using std::vector<Card>::end;

    using std::vector<Card>::size;
    using std::vector<Card>::reserve;

    using std::vector<Card>::push_back;
};

std::ostream& operator<<(std::ostream&, const CardList&);
