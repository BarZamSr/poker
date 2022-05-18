#include <cstdio>
#include <iostream>
#include <random>
#include <algorithm> // std::shuffle()

#include "CardList.h"

#define print(X) (std::cout<<X<<std::endl)

std::ostream& operator<<(std::ostream& os, const CardList& cards) {
    os << "[";
    for(int i=0; i<cards.size(); i++) {
        if (i != 0) printf(" ");
        printf("%s", cards[i].to_str().c_str());
        if (i < cards.size()-1) printf("\n");
        // os << "  " << cards[i] << ((i==cards.size()-1)?"":"\n");
    }
    os << "]";
    return os;
}

int CardList::count(Rank rank) {
    int retval = 0;
    for(auto& card: *this) {
        if (card.is_rank(rank)) {
            retval++;
        }
    }
    return retval;
}

void CardList::shuffle() {
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(*this), std::end(*this), rng);
}

Card CardList::draw() {
    Card retval = back();
    pop_back();
    return retval;
}
CardList CardList::draw(int n) {
    assert(n > 0);
    assert(n <= size());

    CardList retval;
    retval.reserve(n);

    while(n-- > 0) {
        retval.push_back(draw());
    }

    return retval;
}

std::vector<CardList> CardList::combinations(int n) const {
    std::vector<CardList> retval;
    return retval;
}
CardList CardList::operator+ (const CardList& other) const {
    CardList sum(*this);
    sum.reserve(size() + other.size());
    for(auto& card: other) {
        sum.push_back(card);
    }
    return sum;
}
