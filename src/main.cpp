#include <map>
#include <cmath>
#include "CardList.h"

#define DECK_SIZE 52
#define TEXAS_HAND_SIZE 2
#define print(X) (std::cout<<X<<std::endl)

bool is_texas(const CardList&);

u_int16_t ranged_product(u_int16_t, u_int16_t);
int factorial(u_int16_t);
int binomial_coefficient(int, int);

CardList build_deck() {
    CardList deck = CardList();
    deck.reserve(DECK_SIZE);

    for(auto suit: Suit::names) {
        for(auto rank: Rank::names) {
            deck.push_back(Card(rank, suit));
        }
    }
    return deck;
}

// returns chances of getting a pair of each rank
std::map<Rank,float> pair(CardList pocket) {
    assert(is_texas(pocket));

    CardList hand = pocket;
    int count;// std::vector<int> counts(RANK_COUNT, 0);
    std::map<Rank,float> odds;

    for(auto rank: Rank::names) {
        count = hand.count(rank);

        if (count > 1) { // guaranteed
            odds[rank] = 1;
        }
        if (count == 1) { // need at least one more
            odds[rank] = 1 - ((47.f/50) * (47.f/49) * (47.f/48) * (47.f/47) * (47.f/46));
        }
        if (count == 0) { // need at least two more
            odds[rank] = 1 - (
                ((46.f/50) * (43.f/49) * (41.f/48) * (40.f/47) * (40.f/46))
            );
            // P = 50
            // p = 4
            // S = 5
            // s = 2
        }
    }

    return odds;
}

std::vector<std::vector<float>> do_poker(CardList pocket) {
    std::vector<std::vector<float>> retval;
    // retval.push_back(pair(pocket));
    return retval;
}

float empirical(
    int deck_size,
    int desired_in_deck,
    int sample_size,
    int target
) {
    unsigned int samples_taken = 0, samples_accepted = 0;
    CardList deck;

    while(true) {
        // building the target population
        deck = build_deck();
        while(deck.count("ace") > desired_in_deck) {
            deck.draw("ace");
        }
        while(deck.size() > deck_size) {
            deck.draw("two"); // making sure to draw some other rank
        }

        assert(deck.size() == deck_size);
        assert(deck.count("ace") == desired_in_deck);

        deck.shuffle();

        // taking and measuring samples
        while(deck.size() > sample_size) {
            if (deck.draw(sample_size).count("ace") >= target) {
                samples_accepted++;
            }
            samples_taken++;

            if (samples_taken == UINT16_MAX) {
                return (float)samples_accepted/samples_taken;
            }
        }
    }
}

float theoretical(
    int deck_size,
    int desired_in_deck,
    int to_draw,
    int target
) {
    int product_zero = binomial_coefficient(to_draw, target-1);
    float product_one = 1;
    for(int i=1; i<target; i++) {
        product_one *= (float)desired_in_deck /
                                deck_size;
        desired_in_deck--;
        deck_size--;
        to_draw--;
    }
    float product = 1;
    for(int i=0; i<to_draw; i++) {
        product *= (float)(deck_size - desired_in_deck) /
                                    deck_size;
        deck_size--;
    }
    return product_one * product_zero* (1-product);
}

int main() {
    int up, low;
    while(false) {
        std::cin >> up;
        std::cin >> low;
        print(ranged_product(up, low));
    }

    CardList deck;

    print(empirical(50, 3, 5, 2));
    print(theoretical(50, 3, 5, 2));

    return 0;

    deck = build_deck();
    deck.shuffle();


    CardList board;
    CardList pocket = deck.draw(TEXAS_HAND_SIZE);
    print(pocket);

    auto results = do_poker(pocket);

    for(auto result: results) {
        for(auto odds: result) {
            print(odds);
        }
    }

    return 0;
}

bool is_texas(const CardList& pocket) {
    return pocket.size() == TEXAS_HAND_SIZE;
}

u_int16_t ranged_product(u_int16_t upper_bound, u_int16_t lower_bound) {
    return (upper_bound < lower_bound) ? 1 : (upper_bound * ranged_product(upper_bound-1, lower_bound));
}
int factorial(u_int16_t n) {
    return ranged_product(n, 2);
}
int binomial_coefficient(int n, int k) {
    return ranged_product(n, n-k+1) / factorial(k);
}
