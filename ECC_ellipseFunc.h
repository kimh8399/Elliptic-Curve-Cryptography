#ifndef ECC_ELLIPSEFUNC_H_INCLUDED
#define ECC_ELLIPSEFUNC_H_INCLUDED
/*
#ifdef __cplusplus
extern "C" {
#endif
*/
#include "ECC_libraries.h"

// Checks if the a and b values do not make a singular curve
bool validParameters(long long a, long long b);

// Given an x value, a value, b value and a field returns a corresponding y value
coord ellipseFunc(long long x, long long A, long long B, long long mod, long long &points);

//Algebraic addition of two points in a finite field
coord pointAddition(coord P, coord Q, long long mod, long long a);

// Scalar multilplication using double and add
coord scalarMulti(coord input, long long nTimes, long long a, long long  mod);

// Finds the order of a subgroup given it's parent group, and point
long long subGroupOrder(long long parentGroupOrder, coord point, long long a, long long mod);

//Needed to recursively calculate Bezouts Identity for modular inverse
long long bezouts(long long A, long long mod);

// Calculates the modular inverse of a number
long long modInverse(long long b, long long mod);

// Needed to check if a quadratic residue exists to solve congruence
bool hasSolution(long long b, long long ModValue, int &special);

// Calculates order of elliptic curve using brute force
vector <coord> findEllPoints(long long A, long long B, long long field, long long &parentGroupOrder);
/*
#ifdef __cplusplus
}
#endif
*/
#endif // ECC_ELLIPSEFUNC_H_INCLUDED
