#include <iostream>
#include <regex>
#include <string>
#include <vector>

std::vector<std::string> grid{}; // "engine" grid diagram

bool validate(std::regex_iterator<std::string::iterator> it, int lineNum) {
  // takes in a substring and checks if surrounded
  // by a validating each character of substring referenced to the 'grid'
  bool valid = false;
  int pos = it->position();
  for (int k = 0; k < it->length(); k++) {
    // check left
    if (k == 0) {
      if (grid[lineNum][pos - 1] != '.') {
        valid = true;
      }
    }
    // check top left diagonal
    if (grid[lineNum - 1][pos - 1] != '.') {
      valid = true;
    }
    // check top
    if (grid[lineNum - 1][pos] != '.') {
      valid = true;
    }
    // check top right diagonal
    if (grid[lineNum - 1][pos + 1] != '.') {
      valid = true;
    }
    // check right
    if (k == it->length() - 1) {
      if (grid[lineNum][pos + 1] != '.') {
        valid = true;
      }
    }
    // check bottom right diagonal
    if (grid[lineNum + 1][pos + 1] != '.') {
      valid = true;
    }
    // check bottom
    if (grid[lineNum + 1][pos] != '.') {
      valid = true;
    }
    // check bottom left diagonal
    if (grid[lineNum + 1][pos - 1] != '.') {
      valid = true;
    }
    pos++;
  }
  return valid;
}

int main(int argc, char *argv[]) {
  int sum = 0;
  std::string line{};

  // pad input for easy position accessing
  getline(std::cin, line);
  int trueLen = line.length();
  std::string padding(trueLen + 2, '.');
  grid.push_back(padding);
  grid.push_back('.' + line + '.');

  // create 'engine' grid
  while (getline(std::cin, line)) {
    line = '.' + line + '.';
    grid.push_back(line);
  }
  grid.push_back(padding);

  // for each line match all numerical substrings
  std::regex e("(\\d)+");
  for (int i = 0; i < grid.size() - 1; i++) {
    std::string line = grid[i];
    std::regex_iterator<std::string::iterator> iter(line.begin(), line.end(),
                                                    e);
    std::regex_iterator<std::string::iterator> end;

    while (iter != end) {
      bool valid = validate(iter, i);
      if (valid) {
        sum += stoi(iter->str());
        std::cout << iter->str() << std::endl;
      }
      iter++;
    }
  }
  std::cout << sum << std::endl;
  return 0;
}
