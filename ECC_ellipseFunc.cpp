#include "ECC_libraries.h"
#include "ECC_basicFunc.h"
#include "ECC_ellipseFunc.h"

// Checks if the a and b values do not make a singular curve
bool validParameters(long long a, long long b)
{
    long long check = 4 * ((intPower(a, (long long)3))) + 27 * (intPower(b, (long long)2));
    if(check == 0)
        return false;
    else
        return true;
}

// Given an x value, a value, b value and a field returns a corresponding y value
coord ellipseFunc(long long x, long long A, long long B, long long mod, long long &points)
{
    long long yValue;
    long long yTempA;
    long long yTempB;
    long long yTempC;
    long long index = 3;
    int special = 0;
    coord buff;

    yTempA = intPower(x, index);
    yTempB = A * x;
    yTempC = B;
    yValue = yTempA + yTempB + yTempC;
    yValue = modFunc(yValue, mod);

    // Quadratic residues are problem here
    if(hasSolution(yValue, mod, special))
    {
        long long check = yValue;
        long long multiple = 1;
        while(true)
        {
            if(perfectSquare(check, &multiple))
            {
                if(special)
                    points ++;
                else
                    points += 2;
                buff.x = x;
                buff.y = modFunc(multiple, mod);
                buff.y2 = modFunc(-multiple, mod);
                buff.valid = true;
                return buff;
            }
            check += mod;
        }
    }
    else
    {
        buff.x = x;
        buff.y = 2 * mod;
        buff.y2 = 2 * mod;
        buff.valid = false;
        return buff;
    }
}

//Algebraic addition of two points in a finite field
coord pointAddition(coord P, coord Q, long long mod, long long a)
{
    long long slope;
    coord buff;
    if(P.x == Q.x && P.y == Q.y)
        slope = modFunc(modFunc((3 * intPower(P.x, (long long)2)) + a, mod) * bezouts((long long)2 * P.y, mod), mod);
    else if(P.x - Q.x == 0)
    {
        buff.x = 0;
        buff.y = 0;
        return buff;
    }
    else
        slope = modFunc(modFunc(P.y - Q.y, mod) * bezouts(P.x - Q.x, mod), mod);

    buff.x = modFunc((intPower(slope, (long long)2) - P.x - Q.x), mod);
    buff.y = modFunc(-(P.y + slope * (buff.x - P.x)), mod);

    return buff;
}

// Scalar multilplication using double and add
coord scalarMulti(coord input, long long nTimes, long long a, long long  mod)
{
    coord pointAdd;
    coord buffAdd = input;
    vector <bool> binary;
    bool hasStart = false;
    binary = findBits(nTimes);

    for(int i = 0; i < binary.size(); i++)
    {
        if(binary[i] && !hasStart)
        {
            pointAdd = buffAdd;
            hasStart = true;
        }
        else if(binary[i])
            pointAdd = pointAddition(pointAdd, buffAdd, mod, a);

        buffAdd = pointAddition(buffAdd, buffAdd, mod, a);
    }
    return pointAdd;
}

// Finds the order of a subgroup given it's parent group, and point
long long subGroupOrder(long long parentGroupOrder, coord point, long long a, long long mod);

//Needed to recursively calculate Bezouts Identity for modular inverse
long long bezouts(long long a, long long b)
{
	long long b0 = b, t, q;
	long long x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

// Calculates the modular inverse of a number
/*
long long modInverse(long long b, long long mod)
{
    if(mod == (long long)2)
    {
        if(modFunc(b, mod) == (long long)1)
            return (long long)1;
        else
            return (long long)2;
    }
    vector <line> steps;
    b = modFunc(b, mod);
    steps = euclidAlg(b, mod);

    long long p1 = 0;
    long long p2 = 1;
    long long p3;
    for(int i = 2;i < steps.size(); i++)
    {
        p3 = modFunc((p1 - (p2 * steps[i - 2].someQ)), mod);
        p1 = p2;
        p2 = p3;

    }
    int sizeSteps = steps.size();
    p3 = modFunc((p1 - (p2 * steps[sizeSteps - 2].someQ)), mod);
    return p3;
}
*/

// Needed to check if a quadratic residue exists to solve congruence
bool hasSolution(long long b, long long ModValue, int &special)
{
    int check = modFunc(b, ModValue);

    if(check == 0)
    {
        special++;
        return true;
    }
    long long eulersCrit = (ModValue - 1) / 2;
    long long answer = b;
    long long buffMultiply = b;
    long long pointAdd;
    vector <bool> eulerBits;
    bool hasStart = false;
    eulerBits = findBits(eulersCrit);

    for(int i = 0; i < eulerBits.size(); i++)
    {
        if(eulerBits[i] && !hasStart)
        {
            pointAdd = buffMultiply;
            hasStart = true;
        }
        else if(eulerBits[i])
        {
            pointAdd = modFunc(pointAdd * buffMultiply, ModValue);
        }
        buffMultiply = modFunc(buffMultiply * buffMultiply, ModValue);
    }
    pointAdd = modFunc(pointAdd, ModValue);
    if(pointAdd == 1)
        return true;
    else
        return false;
}


vector <coord> findEllPoints(long long A, long long B, long long field, long long & parentGroupOrder)
{
    vector <coord> ellipsePoints;

    parentGroupOrder = 1;
    coord buff;
    for(int i = 0; i < field; i++)
    {
        buff = ellipseFunc(i, A, B, field, parentGroupOrder);
        if(!(buff.y2 > field && buff.y > field))
            ellipsePoints.push_back(buff);
    }
    return ellipsePoints;
}

long long subGroupOrder(long long parentGroupOrder, coord point, long long a, long long mod)
{
    vector <long long> listOfFactor = factors(parentGroupOrder);
    long long i = 0;
    coord check;

    for(; i < listOfFactor.size(); i++)
    {
        check = scalarMulti(point, listOfFactor[i],a, mod);
        if(check.x == 0 & check.y == 0)
            break;
    }
    return listOfFactor[i];
}

