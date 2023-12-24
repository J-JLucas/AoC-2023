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
    
    std::regex e ("(\\d)+");	//match numerical substrings

    for (int i = 1; i < grid.size()-1 ; i++) {
	std::string line = grid[i];
	std::regex_iterator<std::string::iterator> rit (line.begin(), line.end(), e);
	std::regex_iterator<std::string::iterator> rend;

	std::cout << line << std::endl;
	while (rit!=rend) {
	    std::cout << "Matched: \"" << rit->str() << "\", ";
	    std::cout << "Position: " << rit->position() << ", ";
	    std::cout << "Length: " << rit->length() << std::endl;
	    ++rit;
	}
    }
    return 0;
}
