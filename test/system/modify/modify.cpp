#include "json.hpp"
#include <iostream>

using json = nlohmann::json;
int main()
{
    json j;
    std::cin>>j;
    j["happy"] = false;
    std::cout << j;

    return 0;
}
