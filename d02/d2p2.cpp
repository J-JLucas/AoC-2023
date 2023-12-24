#include <iostream>
#include <string>
#include <regex>

const int red {12};
const int blue {14};
const int green {13};

struct roundstruct {int r; int b; int g;};
roundstruct truth = {red, blue, green};

bool validate(roundstruct &round) {
    // returns true if round is invalid
    bool status{};
    
    if (round.r > truth.r) {status = true;}
    if (round.b > truth.b) {status = true;}
    if (round.g > truth.g) {status = true;}

    return status;
}

int main(int argc, char *argv[]) {
    std::string line {};
    int sum {};

    while(getline(std::cin, line)) {
	std::regex gameRegex("Game (\\d+): (.*)");	    // grab game number and create token from remaining rounds
	std::regex roundRegex("(\\d+) (\\w+)");		    // parse each round from 'rounds token'
	std::smatch gameMatch;

	if (std::regex_match(line, gameMatch, gameRegex)) {
	    int gameId = stoi(gameMatch[1]);
	    bool gameStatus = false;
	    std::stringstream roundsStream(gameMatch[2]);
	    std::string roundStr {};
	    
	    while (std::getline(roundsStream, roundStr, ';')) {
		// parse round and populate round struct
		roundstruct round {};
		bool roundStatus = false;
	        std::sregex_iterator it(roundStr.begin(), roundStr.end(), roundRegex);
	        std::sregex_iterator it_end;

	        while (it != it_end) {
		    if ((*it)[2] == "red") { round.r = stoi((*it)[1]);}
		    if ((*it)[2] == "blue") { round.b = stoi((*it)[1]);}
		    if ((*it)[2] == "green") { round.g = stoi((*it)[1]);}
		    it++;
		}
		roundStatus = validate(round);
		if (roundStatus) {gameStatus = roundStatus;}
	    }
	    if (!gameStatus) {sum += gameId;}
	}
    }
    std::cout << sum << std::endl;
    return 0;
}
