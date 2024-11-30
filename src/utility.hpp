#include <vector>
#include <string>
#include <sstream>
#include <fstream>

std::vector<std::string> split(std::string line, char seperator) {
    std::vector<std::string> splitString;
    std::string stringPart;
    std::stringstream input(line);
    while (std::getline(input, stringPart, seperator)) {
        if (stringPart != "") {
            splitString.push_back(stringPart);
        }
    }
    return splitString;
}

std::vector<std::string> load() {
    std::ifstream in("data.txt");
    std::vector<std::string> data;
    std::string line;
    while (std::getline(in, line)) {
        data.push_back(line);
    }
    return data;
}