#include <map>
#include <cmath>

#include "CardList.h"
#include "dict.h"

#define DECK_SIZE 52
#define TEXAS_HAND_SIZE 2
#define print(X) (std::cout<<X<<std::endl)

bool is_texas(const CardList&);

int factorial(int);

int binomial(int, int);
float hypergeometric(int, int, int, int);

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

dict<Rank,float> pair(CardList);
void two_pair(CardList);

void do_poker(CardList);

int main() {
    CardList deck;

    deck = build_deck();
    deck.shuffle();

    CardList board;
    CardList pocket = deck.draw(TEXAS_HAND_SIZE);

    do_poker(pocket);

    return 0;
}

void do_poker(CardList pocket) {
    assert(is_texas(pocket));

    print(pocket);

    float total_prob;

    total_prob = 0;
    auto pair_results = pair(pocket);
    for(auto key: pair_results.keys()) {
        total_prob += pair_results[key];
    }
    std::cout << "Pair: " << total_prob << std::endl;
    for(auto key: pair_results.keys()) {
        int percentage = 100 * pair_results[key];
        std::printf("    %s: %d%%\n", key.c_str(), percentage);
    }
}

dict<Rank,float> pair(CardList pocket) {
    assert(is_texas(pocket));

    CardList hand = pocket; // TODO: table
    int count;
    dict<Rank,float> retval;

    for(Rank rank: Rank::names) {
        count = hand.count(rank);

        if (count > 1) { // guaranteed
            retval[rank] = 1;
        }
        else if (count == 1) { // need at least one more
            retval[rank] = hypergeometric(50, 5, 3, 1);
        }
        else { // need at least two more, but will not be useful
            // do nothing
        }
    }

    return retval;
}

void two_pair(CardList pocket) {
    assert(is_texas(pocket));


}

bool is_texas(const CardList& pocket) {
    return pocket.size() == TEXAS_HAND_SIZE;
}

// implementation credit goes to wikipedia page on the Binomial Coefficient
int binomial(int n, int k) {
    int c = 1, i;

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

/* Implementation credit goes to Graham Kemp,
"At least K successes in n tries without replacement",
URL (version: 2016-03-03): math.stackexchange.com/q/1680840
*/
float hypergeometric(
    int N, // population size
    int n, // sample size
    int K, // number of favoured items in population
    int k  // minimum accepted count of favoured items in sample
) {
    assert(0 <= k <= std::min(n, K));
    assert(K <= N);
    float retval = 0;
    for(int x=k; x<=std::min(n, K); x++) {
        retval += (float)(binomial(K, x) * binomial(N-K, n-x))
                                / binomial(N, n);
    }
    return retval;
}
