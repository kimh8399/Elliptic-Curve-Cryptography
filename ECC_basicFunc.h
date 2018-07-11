#ifndef ECC_BASICFUNC_H_INCLUDED
#define ECC_BASICFUNC_H_INCLUDED

#include "ECC_libraries.h"

using namespace std;

// calculates a number to the power of an index with integers
long long intPower(long long base, long long index);

// randomly generates numbers given a top and bottom range
long long randomNumberGen(long long botRange, long long topRange);

//Ouputs a vector containing the the bits of an input
vector <bool> findBits(long long input);

// Checks if an input is a perfect square
bool perfectSquare(long long input, long long* previous);

// Finds the mod of a number, both positive and negative
long long modFunc(long long input, long long mod);

// Outputs the factors of an input into an array
vector <long long> factors(long long input);

// Randomly generates a prime number above the bot number
long long primeNumMax(long long bot);

#endif // ECC_BASICFUNC_H_INCLUDED
