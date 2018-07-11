#include "ECC_libraries.h"
#include "ECC_basicFunc.h"


//calculates a number to the power of an index with integers
long long intPower(long long base, long long index)
{
    long long answer = base;
    for(int i = 1; i < index; i++)
        answer *= base;
    return answer;
}

// randomly generates numbers given a top and bottom range
long long randomNumberGen(long long botRange, long long topRange)
{
    return rand() % topRange + botRange;
}

//Ouputs a vector contaix   ning the the bits of an input
vector <bool> findBits(long long input)
{
    vector <bool> bits;
    long long checkBits = 1;
    for(int i = 0; i < sizeof(input)* 8; i++)
    {
        if(input & checkBits)
            bits.push_back(1);
        else
            bits.push_back(0);
        checkBits <<= 1;
    }
    return bits;
}

// Checks if an input is a perfect square
bool perfectSquare(long long input, long long* previous)
{
    long long square = *previous;
    square *= square;

    while(true)
    {
        square = *previous;
        square *= square;
        if(input == square)
            return true;
        else if(square< input)
        {
            int buff = *previous;
            buff++;
            *previous = buff;
        }
        else if(square > input)
            return false;
    }
}

//Finds the mod of a number, both positive and negative
long long modFunc(long long input, long long mod)
{
    if(mod == 2)
    {
        if(input % mod == 1)
            return 1;
        else
            return 0;
    }
    if(input < 0)
    {
        long long r = -1;
        long long answer;
        while(true)
        {
            if(r * mod < input)
            {
                answer = input - (r * mod);
                return answer;
            }
            r--;
        }
    }
    input = input % mod;
    return input;
}

vector <long long> factors(long long input)
{
    vector <long long> listOfFactor;
    for(long long i = 2; i < input; i++)
    {
        if(input % i == 0)
            listOfFactor.push_back(i);
    }
    listOfFactor.push_back(input);
    return listOfFactor;
}

long long primeNumMax(long long bot)
{
    bool isPrime = true;
    long long buff = randomNumberGen(bot, 5000);
    while(true)
    {
        for(; buff < buff * 10; buff++)
        {
            isPrime = true;
            for(int i = 2; i < buff; i++)
            {
                if(buff%i == 0)
                {
                    isPrime = false;
                    break;
                }
            }
            if(isPrime)
                break;
        }
        return buff;
    }
}
