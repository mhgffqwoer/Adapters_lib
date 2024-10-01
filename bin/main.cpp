#include <iostream>
#include <vector>
#include <sstream>

#include <map>

#include "Ranges.hpp"

int main() {
    std::stringstream out;
    std::vector<int32_t> myvec = {1, 2, 3, 4, 5};
    for (auto i :
         myvec | transform([](int32_t j) { return j * j; }) | take(4)) {
        out << i;
    }
    std::cout << out.str();
    return 0;
}