#include <map>
#include <cmath>
#include "CardList.h"

#define DECK_SIZE 52
#define TEXAS_HAND_SIZE 2
#define print(X) (std::cout<<X<<std::endl)

bool is_texas(const CardList&);

unsigned long factorial(unsigned short);

unsigned long nCk(unsigned short, unsigned short);

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
    int N, // population size
    int n, // sample size
    int K, // number of favoured items in population
    int k  // minimum accepted count of favoured items in sample
) {
    unsigned int samples_taken = 0, samples_accepted = 0;
    CardList deck;

    while(true) {
        // building the target population
        deck = build_deck();
        while(deck.count("ace") > K) {
            deck.draw("ace");
        }
        while(deck.size() > N) {
            deck.draw("two"); // making sure to draw some other rank
        }

        assert(deck.size() == N);
        assert(deck.count("ace") == K);

        deck.shuffle();

        // taking and measuring samples
        while(deck.size() > n) {
            if (deck.draw(n).count("ace") >= k) {
                samples_accepted++;
            }
            samples_taken++;

            if (samples_taken == UINT16_MAX) {
                return (float)samples_accepted/samples_taken;
            }
        }
    }
}
/* Implementatio credit goes to Graham Kemp,
    "At least K successes in n tries without replacement",
    URL (version: 2016-03-03): math.stackexchange.com/q/1680840
*/
float theoretical(
    int N, // population size
    int n, // sample size
    int K, // number of favoured items in population
    int k // minimum accepted count of favoured items in sample
) {
    /*
    float retval = 1;

    for(int i=1; i<target; i++) {
        retval -= (float)binomial_coefficient()desired_in_deck/deck_size
    }

    float product = 1;
    for(int i=0; i<to_draw; i++) {
        product *= (float)(deck_size - desired_in_deck) /
                                    deck_size;
        deck_size--;
    }
    return product_one * product_zero* (1-product);
    */
    assert(0 <= k <= std::min(n, K));
    assert(K < N);
    float retval = 0;
    for(int x=k; x<=std::min(n, K); x++) {
        retval += (float)(nCk(K, x) * nCk(N-K, n-x))
                            / nCk(N, n);
    }
    return retval;
}

int main() {
    // chance of pocket aces
    print(empirical(52, 2, 4, 2));
    print(theoretical(52, 2, 4, 2));
    print(1.f/221);
    CardList deck;



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

unsigned long factorial(unsigned short n) {
    return (n<2) ? 1 : (n*factorial(n-1));
}
// implementation credit goes to wikipedia page on the Binomial Coefficient
unsigned long nCk(unsigned short n, unsigned short k) {
    unsigned long c = 1, i;

    // take advantage of symmetry
    if (k > n-k)
    k = n-k;

    for (i = 1; i <= k; i++, n--) {
        // return 0 on potential overflow
        if (c/i >= ULONG_MAX/n) return 0;

        // split c * n / i into (c / i * i + c % i) * n / i
        c = c / i * n + c % i * n / i;
    }

    return c;
}
