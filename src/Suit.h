#pragma once

#include <set>
#include <string>

#define SUIT_COUNT 4

class Suit: std::string {
public:
    using std::string::c_str;
    Suit(std::string);

    const static std::set<std::string> names;
};

std::ostream& operator<< (std::ostream&, const Suit&);
