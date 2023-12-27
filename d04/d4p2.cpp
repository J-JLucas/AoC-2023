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
  std::string game{};
  std::vector<std::string> cardTable{};
  std::vector<int> cardCounts{};
  std::regex e("Card\\s*\\d+:\\s*((?:\\d+\\s*)+)\\|\\s*((?:\\d+\\s*)+)");

  // Ideally would like to just 1 pass... maybe refactor later
  while (getline(std::cin, game)) {
    cardTable.push_back(game);
    cardCounts.push_back(1);
  }

  // Second pass: for each card in the cardtable,
  // calculate winners and update cardcount of subsequent cards
  for (int i = 0; i < cardTable.size(); i++) {
    std::sregex_iterator it(cardTable[i].begin(), cardTable[i].end(), e);
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

      // check winning numbers and update running sum
      // and future cardcounts
      int wc = checkWinners(winners, draw);
      sum += cardCounts[i];
      for (int j = 1; j <= wc; j++) {
        cardCounts[i + j] += cardCounts[i];
      }
      it++;
    }
  }
  std::cout << "sum: " << sum << std::endl;
  return 0;
}
