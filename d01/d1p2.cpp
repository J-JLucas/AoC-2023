/* AoC 2023 Day1 Part 2
 * Big challenge was parsing overlapping words
 * eg. oneight
 * new to RegEx, originally only grabbing "one" and not recognizing "eight"
 * was originally using regex_token_iterator, and after switching to regex_iterator 
 * it forward lookahead starts working?
 * big help here:
 * https://stackoverflow.com/questions/41099513/c-regex-for-overlapping-matches 
 * */


#include <iostream>
#include <string>
#include <regex>

char getDigit(std::string s) {
    // converts input string from written number to single char digit
    // or converts digit string to a char
    if(s == "one" || s == "1") {return '1';}
    else if(s == "two" || s == "2") {return '2';}
    else if(s == "three" || s == "3") {return '3';}
    else if(s == "four" || s == "4") {return '4';}
    else if(s == "five" || s == "5") {return '5';}
    else if(s == "six" || s == "6") {return '6';}
    else if(s == "seven" || s == "7") {return '7';}
    else if(s == "eight" || s == "8") {return '8';}
    else if(s == "nine" || s == "9") {return '9';}
    else { std::cout << "invalid string" << std::endl; return '0'; }
}

int main(int argc, char *argv[]) {

    long int sum = 0;
    std::string line;
    std::regex e("(?=(one|1|two|2|three|3|four|4|five|5|six|6|seven|7|eight|8|nine|9)).");
    
    while(getline(std::cin, line)) {
	std::sregex_iterator results(line.begin(), line.end(), e);
        std::sregex_iterator end;	    //need this, can't just use nullpointer???
	std::smatch match = *results;
	std::string first = match.str(1);   // idk why index 1, that's what SO said to do! better research the docs...
	std::string last{};

	while(results != end) {
	    match = *results;
	    last = match.str(1);
	    results++;
	}

	std::string coord;
	coord = getDigit(first);
	coord += getDigit(last);
	sum += stoi(coord);	
    }

    std::cout << sum << std::endl;

    return 0;
}
