#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

int main() 
{
    while(true)
    {
        std::ifstream myFile("../data.json");
        std::ostringstream tmp;
        tmp << myFile.rdbuf();
        std::string s = tmp.str();

        auto j3 = json::parse(s);
        std::cout << j3["location"] << std::endl;
    }

    return 0;
}