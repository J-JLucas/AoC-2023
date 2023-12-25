#include <iostream>
#include <string>
#include <vector>
#include <regex>

std::vector<std::string> grid {};   // "engine" grid diagram
std::vector<std::map<int, std::string>> gearTable{};

int validate(std::regex_iterator<std::string::iterator> it, int lineNum) {
    // takes in a substring and checks if surrounded
    // by a validating character in the grid
/*
    std::cout << std::endl;
    std::cout << grid[lineNum-1] << std::endl;
    std::cout << grid[lineNum] << std::endl;
    std::cout << grid[lineNum+1] << std::endl;
    std::cout << it->str() << std::endl;
*/    
    int gearRatio = 1;
    int pos = it->position();
    int lbound = pos-1;
    int ubound = lbound+2;
    int matchCount = 0;
    //std::cout << grid[lineNum] << std::endl;
    //std::cout << "lbound: " << lbound << " ubound: " << ubound << std::endl;
    std::regex e("(\\d)+");

    for (int k = -1; k < 2; k++) {
        std::string line = grid[lineNum+k];
	std::regex_iterator<std::string::iterator> iter (line.begin(), line.end(), e);
	std::regex_iterator<std::string::iterator> end;
   
	while(iter != end) {
	    int head = iter->position();
	    int tail = head + iter->length()-1;
//	    std::cout << "head: " << head << " tail: " << tail << std::endl;
	    if(!(tail < lbound || head > ubound)) {
//		std::cout << "inbounds: " << iter->str() << std::endl;
		gearRatio *= stoi(iter->str());
		matchCount++;
	    }
//	    else {std::cout << "oob" << std::endl;}
	    iter++;
	}
    }
//    std::cout << "matchcount: " << matchCount << std::endl;
//    std::cout << gearRatio << std::endl;
    if(matchCount == 2 ) { return gearRatio;}
    else {return 0;}
}

int main(int argc, char* argv[]) {
    
    int sum = 0;
    std::string line{};

    // pad input for easy position accessing
    getline(std::cin, line);
    int trueLen = line.length(); 
    std::string padding(trueLen + 2, '.');
    grid.push_back(padding);
    grid.push_back('.' + line + '.');

    // create 'engine' grid
    while(getline(std::cin, line)) { line = '.'+ line + '.'; grid.push_back(line); }
    grid.push_back(padding);
    
    // for each line match all numerical substrings
    std::regex e ("\\*");			
    for (int i = 0; i < grid.size()-1 ; i++) {
	std::string line = grid[i];
	std::regex_iterator<std::string::iterator> iter (line.begin(), line.end(), e);
	std::regex_iterator<std::string::iterator> end;
    
	//std::cout << line << std::endl;
	while (iter!=end) {
	    //std::cout << iter->str() << std::endl;
	    sum += validate(iter, i);
	    iter++;
	}
    }

    std::cout << "sum total: " << sum << std::endl;
    return 0;
}
