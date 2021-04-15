#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int main(int, char**) {

    std::ifstream myFile("date.json");
    std::ostringstream tmp;
    tmp << myFile.rdbuf();
    std::string s = tmp.str();
    std::cout << s << std::endl;

    return 0;
}
