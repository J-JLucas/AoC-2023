#include <iostream>
#include <string>
#include <regex>

const int red {12};
const int blue {14};
const int green {13};

//struct round = {int id, int r, int b, int g};
//round truth = {-1, red, blue, green};

int main(int argc, char *argv[]) {

    std::string line {};
    while(getline(std::cin, line)) {
	std::regex game_regex("Game (\\d+): (.*)");  // The regex pattern to match the game number and rounds
	std::regex round_regex("(\\d+) (\\w+)");  // The regex pattern to match the counts and colours in each round
	std::smatch game_match;
	    if (std::regex_match(line, game_match, game_regex)) {
		std::string game_number = game_match[1];
	        std::cout << "Game Number: " << game_number << "\n";

		std::stringstream rounds_stream(game_match[2]);
		std::string round;
		int roundNum = 1;
		while (std::getline(rounds_stream, round, ';')) {
		    std::cout << "Round "<< roundNum << ": ";

		    std::sregex_iterator it(round.begin(), round.end(), round_regex);
			std::sregex_iterator it_end;
		    while (it != it_end) {
			std::cout << (*it)[2] << ": " << (*it)[1] << ", ";
		        ++it;
		    }
		    roundNum++;
		    std::cout << std::endl;
		}
	    }
    }
    return 0;
}
