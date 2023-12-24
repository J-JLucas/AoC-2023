#include <iostream>
#include <string>
#include <vector>
#include <regex>

std::vector<std::string> grid {};   // "engine" grid diagram

bool validate(std::regex_iterator<std::string::iterator> it, int lineNum) {
    // takes in a substring and checks if surrounded
    // by a validating character in the grid
    std::cout << std::endl;
    std::cout << grid[lineNum-1] << std::endl;
    std::cout << grid[lineNum] << std::endl;
    std::cout << grid[lineNum+1] << std::endl;
    std::cout << it->str() << std::endl;
    
    bool valid = false;
    int pos = it->position();
    for(int k = 0; k < it->length(); k++) {
	std::cout << "char: "<< (it->str())[k] << std::endl;
	std::cout << std::endl;
	// check left
	if(k == 0) {
	    std::cout << "left: " << grid[lineNum][pos-1] << std::endl;
	    if(grid[lineNum][pos-1] != '.') {valid = true;}
	}
	
	// check top left diagonal
	std::cout << "top left: " << grid[lineNum-1][pos-1] << std::endl;
	if(grid[lineNum-1][pos-1] != '.') {valid = true;}
	
	// check top
	std::cout << "top: " << grid[lineNum-1][pos] << std::endl;
	if(grid[lineNum-1][pos] != '.') {valid = true;}	
	
	// check top right diagonal
	std::cout << "top right: " << grid[lineNum-1][pos+1] << std::endl;
	if(grid[lineNum-1][pos+1] != '.') {valid = true;}
	
	// check right	
	if(k == it->length()-1) {
	    std::cout << "right: " << grid[lineNum][pos+1] << std::endl;
	    if(grid[lineNum][pos+1] != '.') {valid = true;}
	}	 
		
	// check bottom right diagonal
	std::cout << "bottom right: " << grid[lineNum+1][pos+1] << std::endl;
	if(grid[lineNum+1][pos+1] != '.') {valid = true;}
	
	// check bottom
	std::cout << "bottom: " << grid[lineNum+1][pos] << std::endl;
	if(grid[lineNum+1][pos] != '.') {valid = true;}

	// check bottom left diagonal	
	std::cout << "bottom left: " << grid[lineNum+1][pos-1] << std::endl;
	if(grid[lineNum+1][pos-1] != '.') {valid = true;}
	std::cout << std::endl;
	pos++;
    }
    std::cout << valid << std::endl;
    return valid;
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
    std::regex e ("(\\d)+");			
    for (int i = 0; i < grid.size()-1 ; i++) {
	std::string line = grid[i];
	std::regex_iterator<std::string::iterator> iter (line.begin(), line.end(), e);
	std::regex_iterator<std::string::iterator> end;
    
	//std::cout << line << std::endl;
	while (iter!=end) {
	    bool valid = validate(iter, i);
	    if(valid) {sum += stoi(iter->str()); std::cout << iter->str() << std::endl;}
	    iter++;
	}
    }
    for (auto line : grid) {
	std::cout << line << std::endl;
    }

    std::cout << sum << std::endl;
    return 0;
}
