#include <iostream>
#include <cassert>
using namespace std;

long long int gcd(long long int a, long long int b)
{
    a = abs(a);
    b = abs(b);
    assert(b != 0);
    while (a % b != 0)
    {
        int temp = a;
        a = b;
        b = temp % b;
    }
    return b;
}

int sign(long long int a)
{
    if (a < 0)
    {
        return -1;
    }
    return 1;
}

// Fraction class
class Frac
{
    long long int a, b;

public:
    Frac(long long int x = 0, long long int y = 1)
    {
        int g = gcd(x, y);
        a = sign(x) * sign(y) * abs(x) / g;
        b = abs(y) / g;
    }
    Frac operator+(Frac x)
    {
        Frac n(a * x.b + b * x.a, b * x.b);
        return n;
    }
    Frac operator-(Frac x)
    {
        Frac n(a * x.b - b * x.a, b * x.b);
        return n;
    }
    Frac operator*(Frac x)
    {
        Frac n(a * x.a, b * x.b);
        return n;
    }
    Frac operator*(int x)
    {
        Frac n(a * x, b);
        return n;
    }
    bool operator==(Frac x)
    {
        return ((a == x.a) && (b == x.b));
    }
    Frac operator/(Frac x)
    {
        Frac n(a * x.b, b * x.a);
        return n;
    }
    Frac inverse()
    {
        return Frac(b, a);
    }

    double value()
    {
        return (double)a / (double)b;
    }
    int a_()
    {
        return a;
    }
    int b_()
    {
        return b;
    }
    void reset(int x, int y)
    {
        Frac n(x, y);
        a = n.a;
        b = n.b;
    }
    friend ostream &operator<<(ostream &os, const Frac &f)
    {
        if (f.b == 1)
        {
            os << f.a;
        }
        else
        {
            os << f.a << "/" << f.b;
        }
        return os;
    }
    bool is_int()
    {
        if (b == 1)
        {
            return true;
        }
        return false;
    }
};
