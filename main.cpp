#include <iostream>
#include <string>
#include <cctype>

bool isInteger(const std::string& str) {
    if (str.empty() || ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+'))) return false;
    char * p;
    strtol(str.c_str(), &p, 10);
    return (*p == 0);
}

bool areIntegers(const std::string& str1, const std::string& str2) {
    return isInteger(str1) && isInteger(str2);
}

bool endsWithTxt(const std::string& str) {
    const std::string suffix = ".txt";
    return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::string num1, num2;
        std::cout << "Please enter the first number: ";
        std::cin >> num1;
        std::cout << "Please enter the second number: ";
        std::cin >> num2;
        if (areIntegers(num1, num2)) {
            std::cout << "Both numbers are valid integers." << std::endl;
        } else {
            std::cout << "At least one of the numbers is not a valid integer." << std::endl;
        }
        //std::cout << "You entered: " << num1 << " and " << num2 << std::endl;
    } else if (argc == 3) {
        if (endsWithTxt(argv[1]) && endsWithTxt(argv[2])) {
            std::cout << "Both arguments end with '.txt'." << std::endl;
        } else {
            std::cout << "At least one argument does not end with '.txt'." << std::endl;
        }
    } else {
        std::cerr << "Error: This program requires 0 or 2 arguments." << std::endl;
    }
    return 0;
}