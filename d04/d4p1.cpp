#include <cmath>
#include <iostream>
#include <map>
#include <regex>
#include <string>

int checkWinners(std::map<std::string, int> &m, std::vector<std::string> &v)
{
  // returns the number of winning numbers
  int winCount = 0;
  for (auto &e : v) {
    if (m[e] == stoi(e)) {
      winCount++;
    }
  }
  return winCount;
}

int main(int argc, char *argv[])
{
  int sum = 0;
  std::string game;
  std::regex e("Card\\s*\\d+:\\s*((?:\\d+\\s*)+)\\|\\s*((?:\\d+\\s*)+)");
  // can't seem to figure out how to do this in one step, expression is creating
  // 1 token of all winning numbers, and 1 for all drawn numbers
  // first while grabs win and draw tokens,
  // second while tokenizes each digit and populates corresponding
  // datastructures

  while (getline(std::cin, game)) {
    std::sregex_iterator it(game.begin(), game.end(), e);
    std::sregex_iterator end;
    std::map<std::string, int> winners;
    std::vector<std::string> draw;

    while (it != end) {
      std::smatch m = *it;
      std::string winstr = m[1];
      std::string drawstr = m[2];
      std::regex num("\\d+");
      std::sregex_iterator winIt(winstr.begin(), winstr.end(), num);

      // populate winners map
      while (winIt != end) {
        int val = stoi(winIt->str());
        winners.insert({winIt->str(), val});
        winIt++;
      }

      // populate draw vector
      std::sregex_iterator drawIt(drawstr.begin(), drawstr.end(), num);
      while (drawIt != end) {
        draw.push_back(drawIt->str());
        drawIt++;
      }

      // check winning numbers and calculate score
      int wc = checkWinners(winners, draw);
      int points{};
      if (wc == 0) {
        points = 0;
      }
      else {
        points = pow(2, wc - 1);
      }
      sum += points;
      it++;
    }
  }
  std::cout << sum << std::endl;
  return 0;
}
