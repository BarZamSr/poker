#include <array>
#include <string>
#include <iostream>

#define RANK_COUNT 13

class Rank: std::string {
public:
    using std::string::c_str;

    const static std::array<std::string,RANK_COUNT> names;

    Rank(std::string);
    Rank(const char*);

    operator int() const;
    bool operator== (const Rank&) const;
    bool operator< (const Rank&) const;

    friend std::ostream& operator<<(std::ostream&, const Rank&);
};

template<>
class std::hash<Rank> {
public:
    std::size_t operator()(const Rank& k) const;
};
