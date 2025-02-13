#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include "BigUnsigned.h"

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

void testBigUnsignedOperations(const BigUnsigned& num1, const BigUnsigned& num2) {
    std::cout << "Testing operations with: " << num1 << " and " << num2 << std::endl;

    BigUnsigned sum = num1 + num2;
    std::cout << num1 << " + " << num2 << " = " << sum << std::endl;

    if(num2 < num1) {
        BigUnsigned diff = num1 - num2;
        std::cout << num1 << " - " << num2 << " = " << diff << std::endl;
    } else {
        std::cout << "Negative result." << std::endl;
    }


    BigUnsigned prod = num1 * num2;
    std::cout << num1 << " * " << num2 << " = " << prod << std::endl;

    if (num2 != BigUnsigned(static_cast<unsigned int>(0))) {
        BigUnsigned quot = num1 / num2;
        std::cout << num1 << " / " << num2 << " = " << quot << std::endl;

        BigUnsigned rem = num1 % num2;
        std::cout << num1 << " % " << num2 << " = " << rem << std::endl;
    } else {
        std::cout << "Division and modulo by zero are not allowed." << std::endl;
    }


    std::cout << "Incrementing " << num1 << ": " << ++BigUnsigned(num1) << std::endl;
    std::cout << "Decrementing " << num1 << ": " << --BigUnsigned(num1) << std::endl;

    std::cout << "Incrementing " << num2 << ": " << BigUnsigned(num2)++ << std::endl;
    std::cout << "Decrementing " << num2 << ": " << BigUnsigned(num2)-- << std::endl;

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
            BigUnsigned bigNum1(static_cast<unsigned>(std::stoul(num1)));
            BigUnsigned bigNum2(static_cast<unsigned>(std::stoul(num2)));
            testBigUnsignedOperations(bigNum1, bigNum2);
        } else {
            std::cout << "At least one of the numbers is not a valid integer." << std::endl;
        }
        //std::cout << "You entered: " << num1 << " and " << num2 << std::endl;
    } else if (argc == 3) {
        if (endsWithTxt(argv[1]) && endsWithTxt(argv[2])) {
            std::cout << "Both arguments end with '.txt'." << std::endl;

            std::ifstream file1(argv[1]);
            std::ifstream file2(argv[2]);

            if (!file1.is_open() || !file2.is_open()) {
                std::cerr << "Error opening one of the files." << std::endl;
                return 1;
            }

            std::string num1, num2;
            file1 >> num1;
            file2 >> num2;

            std::cout << "Read from file 1: " << num1 << std::endl;
            std::cout << "Read from file 2: " << num2 << std::endl;

            if (areIntegers(num1, num2)) {
                std::cout << "Both numbers are valid integers." << std::endl;
                BigUnsigned bigNum1(reinterpret_cast<const /*unsigned*/ char*>(num1.c_str()));
                BigUnsigned bigNum2(reinterpret_cast<const /*unsigned*/ char*>(num2.c_str()));
                testBigUnsignedOperations(bigNum1, bigNum2);
            } else {
                std::cout << "At least one of the numbers in the files is not a valid integer." << std::endl;
            }

            file1.close();
            file2.close();
        } else {
            std::cout << "At least one argument does not end with '.txt'." << std::endl;
        }
    } else {
        std::cerr << "Error: This program requires 0 or 2 arguments." << std::endl;
    }
    return 0;
}