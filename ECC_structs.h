#ifndef ECC_STRUCTS_H_INCLUDED
#define ECC_STRUCTS_H_INCLUDED

struct coord
{
    long long x;
    long long y;
    long long y2;
    bool valid;
};

struct line
{
    long long remainder;
    long long someQ;
    long long quotient;
    long long check;
};
#endif // ECC_STRUCTS_H_INCLUDED
