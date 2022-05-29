#include <unordered_map>

template <typename key,typename value>
class dict: std::unordered_map<key,value> {

public:
    using std::unordered_map<key,value>::operator[];

    std::vector<key> keys() {
        std::vector<key> retval;
        for(auto x: *this) {
            retval.push_back(std::get<const key>(x));
        }
        return retval;
    }
    std::vector<value> values();
};
