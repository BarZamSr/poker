#pragma once

#include <array>
#include <string>

#define RANK_COUNT 13

class Rank {
    const static std::array<std::string, RANK_COUNT> names;
    int value;
public:
    Rank(int);
    std::string to_str() const;
    Rank operator++ ();
    bool operator== (Rank) const;
};

std::ostream& operator<<(std::ostream&, const Rank&);
