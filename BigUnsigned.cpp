// BigUnsigned.cpp
#include "BigUnsigned.h"
#include <algorithm>

// Constructor por defecto
BigUnsigned::BigUnsigned(unsigned n) {
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
}

// Constructor desde un array de unsigned char
BigUnsigned::BigUnsigned(const /*unsigned*/ char* num) {
    while (*num) {
        digits.push_back(*num - '0');
        num++;
    }
    std::reverse(digits.begin(), digits.end());
}

// Constructor de copia
BigUnsigned::BigUnsigned(const BigUnsigned& other) : digits(other.digits) {}

// Operador de asignación
BigUnsigned& BigUnsigned::operator=(const BigUnsigned& other) {
    if (this != &other) {
        digits = other.digits;
    }
    return *this;
}

// Operador de flujo de salida
std::ostream& operator<<(std::ostream& os, const BigUnsigned& num) {
    for (auto it = num.digits.rbegin(); it != num.digits.rend(); ++it) {
        os << static_cast<int>(*it);
    }
    return os;
}

// Operador de flujo de entrada
std::istream& operator>>(std::istream& is, BigUnsigned& num) {
    std::string input;
    is >> input;
    num.digits.clear();
    for (auto it = input.rbegin(); it != input.rend(); ++it) {
        num.digits.push_back(*it - '0');
    }
    return is;
}

// Operador de comparación ==
bool BigUnsigned::operator==(const BigUnsigned& other) const {
    return digits == other.digits;
}

// Operador de comparación <
bool operator<(const BigUnsigned& a, const BigUnsigned& b) {
    if (a.digits.size() != b.digits.size()) {
        return a.digits.size() < b.digits.size();
    }
    for (auto it_a = a.digits.rbegin(), it_b = b.digits.rbegin(); it_a != a.digits.rend(); ++it_a, ++it_b) {
        if (*it_a != *it_b) {
            return *it_a < *it_b;
        }
    }
    return false;
}

// operador de comparación <=
bool BigUnsigned::operator<=(const BigUnsigned& other) const {
    // Implementación de comparación
    return *this < other || *this == other;
}

// Operador de comparación >=
bool BigUnsigned::operator>=(const BigUnsigned& other) const {
    // Implementación de comparación
    return !(*this < other);
}

// Operador de comparación !=
bool BigUnsigned::operator!=(const BigUnsigned& other) const {
    // Implementación de comparación
    return !(*this == other);
}
// Pre-incremento
BigUnsigned& BigUnsigned::operator++() {
    *this = *this + BigUnsigned(1);
    return *this;
}

// Post-incremento
BigUnsigned BigUnsigned::operator++(int) {
    BigUnsigned temp = *this;
    //++(*this);
    //return temp;
    return ++(*this);
}

// Pre-decremento
BigUnsigned& BigUnsigned::operator--() {
    /*
    if (*this == BigUnsigned(static_cast<unsigned int>(0))) {
        throw std::invalid_argument("Negative result1");
    }
    */
    *this = *this - BigUnsigned(1);
    return *this;
}

// Post-decremento
BigUnsigned BigUnsigned::operator--(int) {
    /*
    if (*this == BigUnsigned(static_cast<unsigned int>(0))) {
        throw std::invalid_argument("Negative result2");
    }
    */
    BigUnsigned temp = *this;
    //--(*this);
    //return temp;
    return --(*this);
}

// Operador aritmético +
BigUnsigned operator+(const BigUnsigned& a, const BigUnsigned& b) {
    BigUnsigned result;
    unsigned carry = 0;
    size_t maxSize = std::max(a.digits.size(), b.digits.size());
    for (size_t i = 0; i < maxSize || carry; ++i) {
        unsigned sum = carry;
        if (i < a.digits.size()) sum += a.digits[i];
        if (i < b.digits.size()) sum += b.digits[i];
        result.digits.push_back(sum % 10);
        carry = sum / 10;
    }
    return result;
}

// Operador aritmético -
BigUnsigned BigUnsigned::operator-(const BigUnsigned& other) const {
    if (*this < other) {
        //throw std::invalid_argument("Negative result3");
        std::cerr << "Error: Negative result. The result of the subtraction is negative." << std::endl;
    }
    BigUnsigned result;
    unsigned borrow = 0;
    for (size_t i = 0; i < digits.size(); ++i) {
        int diff = digits[i] - (i < other.digits.size() ? other.digits[i] : 0) - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits.push_back(diff);
    }
    // Remove leading zeros
    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }
    return result;
}

// Operador aritmético *
BigUnsigned BigUnsigned::operator*(const BigUnsigned& other) const {
    BigUnsigned result;
    result.digits.resize(digits.size() + other.digits.size(), 0);
    for (size_t i = 0; i < digits.size(); ++i) {
        unsigned carry = 0;
        for (size_t j = 0; j < other.digits.size() || carry; ++j) {
            unsigned long long current = result.digits[i + j] + digits[i] * (j < other.digits.size() ? other.digits[j] : 0) + carry;
            result.digits[i + j] = current % 10;
            carry = current / 10;
        }
    }
    // Remove leading zeros
    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }
    return result;
}

// Operador aritmético /
BigUnsigned operator/(const BigUnsigned& a, const BigUnsigned& b) {
    if (b == BigUnsigned(static_cast<unsigned int>(0))) {
        throw std::invalid_argument("Division by zero");
    }
    BigUnsigned result, current;
    for (auto it = a.digits.rbegin(); it != a.digits.rend(); ++it) {
        current.digits.insert(current.digits.begin(), *it);
        while (current.digits.size() > 1 && current.digits.back() == 0) {
            current.digits.pop_back();
        }
        unsigned x = 0, l = 0, r = 10;
        while (l <= r) {
            unsigned m = (l + r) / 2;
            BigUnsigned t = b * BigUnsigned(m);
            if (t <= current) {
                x = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        result.digits.push_back(x);
        current = current - b * BigUnsigned(x);
    }
    std::reverse(result.digits.begin(), result.digits.end());
    // Remove leading zeros
    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }
    return result;
}

// Operador aritmético %
BigUnsigned BigUnsigned::operator%(const BigUnsigned& other) const {
    return *this - (*this / other) * other;
}