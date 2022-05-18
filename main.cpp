#include "Rank.h"
#include "Suit.h"
#include "Card.h"
#include "CardList.h"

#define DECK_SIZE 52

bool is_texas(const CardList&);

CardList build_deck() {
    CardList deck;
    deck.reserve(DECK_SIZE);

    for(int i=0; i<RANK_COUNT; i++) {
        for(auto suit: Suit::names) {
            deck.push_back(Card(i, suit));
        }
    }

    return deck;
}

// returns chances of getting a pair of each rank
std::vector<float> pair(CardList pocket) {
    assert(is_texas(pocket));

    CardList hand = pocket;
    std::vector<int> counts(RANK_COUNT, 0);
    std::vector<float> odds(RANK_COUNT);

    for(int i=0; i<RANK_COUNT; i++) {
        counts[i] += hand.count(i);
        if (counts[i] > 1) {
            odds[i] = 1; // guaranteed
        }
    }
    return odds;
    // let s be the number of cards seen
    // let h be the number of cards in s that are of rank r
    //for(int i=)
}

std::vector<std::vector<float>> do_poker(CardList pocket) {
    std::vector<std::vector<float>> retval;
    retval.push_back(pair(pocket));
    return retval;
}

int main() {
    CardList deck = build_deck();
    deck.shuffle();

    CardList board;
    CardList pocket = deck.draw(5);

    auto results = do_poker(pocket);

    //PRINT(results);

    return 0;
}

bool is_texas(const CardList& pocket) {
    return pocket.size() == 2;
}
