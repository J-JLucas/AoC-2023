#include <iostream>
#include <regex>
#include <string>

struct roundstruct {
  int r;
  int b;
  int g;
};

void calculateMinimum(roundstruct &round, roundstruct &gameMin)
{
  // returns true if round is invalid
  bool status{};

  if (round.r > gameMin.r) {
    gameMin.r = round.r;
  }
  if (round.b > gameMin.b) {
    gameMin.b = round.b;
  }
  if (round.g > gameMin.g) {
    gameMin.g = round.g;
  }

  return;
}

int main(int argc, char *argv[])
{
  std::string line{};
  int sum{};

  while (getline(std::cin, line)) {
    std::regex gameRegex("Game (\\d+): (.*)"); // grab game number and create
                                               // token from remaining rounds
    std::regex roundRegex(
        "(\\d+) (\\w+)"); // parse each round from 'rounds token'
    std::smatch gameMatch;

    if (std::regex_match(line, gameMatch, gameRegex)) {
      int gameId = stoi(gameMatch[1]);
      roundstruct gameMin{};
      std::stringstream roundsStream(gameMatch[2]);
      std::string roundStr{};

      while (std::getline(roundsStream, roundStr, ';')) {
        // parse round and populate round struct
        roundstruct round{};
        std::sregex_iterator it(roundStr.begin(), roundStr.end(), roundRegex);
        std::sregex_iterator it_end;

        while (it != it_end) {
          if ((*it)[2] == "red") {
            round.r = stoi((*it)[1]);
          }
          if ((*it)[2] == "blue") {
            round.b = stoi((*it)[1]);
          }
          if ((*it)[2] == "green") {
            round.g = stoi((*it)[1]);
          }
          it++;
        }
        calculateMinimum(round, gameMin);
      }
      int power = gameMin.r * gameMin.b * gameMin.g;
      sum += power;
    }
  }
  std::cout << sum << std::endl;
  return 0;
}
