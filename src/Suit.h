#include <set>
#include <string>

#define SUIT_COUNT 4

class Suit: std::string {
public:
    const static std::set<std::string> names;

    using std::string::c_str;

    Suit(std::string);

    bool operator==(const Suit&) const;

    friend std::ostream& operator<<(std::ostream&, const Suit&);
};
