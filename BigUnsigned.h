// BigUnsigned.h
#ifndef BIGUNSIGNED_H
#define BIGUNSIGNED_H

#include <iostream>
#include <vector>
#include <string>

class BigUnsigned {
private:
    std::vector<unsigned char> digits;

public:
    // Constructores
    BigUnsigned(unsigned n = 0);
    BigUnsigned(const /*unsigned*/ char* ); 
    BigUnsigned(const BigUnsigned&);

    // Operadores de asignación
    BigUnsigned& operator=(const BigUnsigned&);

    // Operadores de flujo
    friend std::ostream& operator<<(std::ostream&, const BigUnsigned&);
    friend std::istream& operator>>(std::istream&, BigUnsigned&);

    // Operadores de comparación
    bool operator==(const BigUnsigned&) const;
    friend bool operator<(const BigUnsigned&, const BigUnsigned&);
    bool operator<=(const BigUnsigned&) const; // Implementación de comparación <=, no solicitada en el enunciado
    bool operator>=(const BigUnsigned& other) const; // Implementación de comparación >=, no solicitada en el enunciado
    bool operator!=(const BigUnsigned& other) const; // Implementación de comparación !=, no solicitada en el enunciado

    // Operadores de incremento/decremento
    BigUnsigned& operator++();      // Pre-incremento
    BigUnsigned operator++(int);    // Post-incremento
    BigUnsigned& operator--();      // Pre-decremento
    BigUnsigned operator--(int);    // Post-decremento

    // Operadores aritméticos
    friend BigUnsigned operator+(const BigUnsigned&, const BigUnsigned&);
    BigUnsigned operator-(const BigUnsigned&) const;
    BigUnsigned operator*(const BigUnsigned&) const;
    friend BigUnsigned operator/(const BigUnsigned&, const BigUnsigned&);
    BigUnsigned operator%(const BigUnsigned&) const;

};

#endif // BIGUNSIGNED_H
