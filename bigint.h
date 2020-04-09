
#include <iostream>
#include <cstring>
#include <string>

#ifndef BIGINT_H
#define BIGINT_H

class BigInt{
    friend BigInt operator - (const BigInt& posit);
    friend BigInt operator - ( const BigInt& left, const BigInt& right);
    friend BigInt operator + ( const BigInt& left, const BigInt& right);
    friend std::ostream& operator <<(std::ostream &os, const BigInt& bInt);
private:
    char * number;
    size_t number_len;
    char sign;
private:    
    BigInt(const char* num, const char& sgn);
public:
    BigInt(int x = 0);
    BigInt(int64_t x);
    BigInt(const BigInt& bInt);
    ~BigInt();
    BigInt& operator = (const BigInt&);
    
    bool operator== (const BigInt&) const;
    bool operator!= (const BigInt&) const;
    bool operator > (const BigInt&) const;
    bool operator < (const BigInt&) const;
    bool operator<= (const BigInt&) const;
    bool operator>= (const BigInt&) const;

};
#endif /* BIGINT_H */