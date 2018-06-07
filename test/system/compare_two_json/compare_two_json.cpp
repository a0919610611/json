#include "json.hpp"
#include <iostream>

using nlohmann::json;
int main()
{
    json j1, j2;
    std::cin >> j1;
    std::cin >> j2;
    puts((j1==j2)?"yes":"no");

    return 0;
}
