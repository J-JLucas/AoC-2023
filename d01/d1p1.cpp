#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

    int sum = 0;
    std::string line;
    
    while(getline(std::cin, line)) {
	char first = 0;
	char last = '0';
	
	for (int i = 0; i < line.length(); i++) {
	    if (isdigit(line[i])) {
		if(!first) {first = line[i]; last = first;}  //set both incase only 1 digit appears
		else {last = line[i];}
	    }
	}
	
	std::string coord;
	coord = first;
	coord += last;
	std::cout << coord << std::endl;
	
	sum += stoi(coord);	
    }

    std::cout << sum << std::endl;

    return 0;
}
