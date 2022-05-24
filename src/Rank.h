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

    bool operator== (const Rank&) const;
    bool operator< (const Rank&) const;

    unsigned int get_number() const;

    friend std::ostream& operator<<(std::ostream&, const Rank&);
};
