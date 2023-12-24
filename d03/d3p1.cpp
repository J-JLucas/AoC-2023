#include <iostream>
#include <string>
#include <vector>
#include <regex>

int main(int argc, char* argv[]) {
    
    int sum = 0;
    std::string line{};
    std::vector<std::string> grid {};

    // pad input for easy position accessing
    getline(std::cin, line);
    int trueLen = line.length(); 
    std::string padding(trueLen + 2, '.');
    grid.push_back(padding);
   
    // create 'engine' grid
    while(getline(std::cin, line)) { 
	line = '.'+ line + '.';
	grid.push_back(line);
    }
    grid.push_back(padding);

    /*
    for(const auto &str : grid) {
       std::cout << str << std::endl;
    }
    */

    return 0;
}
