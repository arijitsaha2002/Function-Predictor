#include <iostream>
#include <vector>
#include <arijit.h>
#include "HEADER/polynomial.h"
using namespace std;

Frac one(1);

bool check(vector<Frac> xi, Frac x)
{
    for (size_t i = 0; i < xi.size(); i++)
    {
        if (xi[i] == x)
        {
            return true;
        }
    }
    return false;
}

void modifier(vector<Pol> &p, Frac f_, Frac x_, vector<Frac> &xi)
{
    for (size_t i = 0; i < p.size(); i++)
    {
        Frac a[2] = {x_ * (-1), one};
        p[i] = p[i] * Pol(a, 2) * (xi[i] - x_).inverse();
    }
}

void new_term(vector<Pol> &p, Frac f_, Frac x_, vector<Frac> &xi)
{
    Pol temp(&f_, 1);
    for (size_t i = 0; i < xi.size(); i++)
    {
        Frac coef = (x_ - xi[i]).inverse();
        Frac a[2] = {xi[i] * (-1), one};
        temp = temp * Pol(a, 2);
        temp = temp * Pol(&coef, 1);
    }
    p.push_back(temp);
    xi.push_back(x_);
}

Pol add(vector<Pol> p)
{
    Pol temp;
    for (size_t i = 0; i < p.size(); i++)
    {
        temp = temp + p[i];
    }
    return temp;
}

int main()
{
    vector<Pol> Each_term;
    vector<Frac> all_x;
    Pol Final;
    while (true)
    {
        int f_x, f_y, x, y;
        cout << "enter the value of x and f(x)" << endl;
        cin >> x;
        if (x == -1)
        {
            break;
        }
        cin >> y >> f_x >> f_y;
        if (check(all_x,Frac(x,y)))
        {
            cout << " invalid " << endl;
            continue;
        }
        
        modifier(Each_term, Frac(f_x, f_y), Frac(x, y), all_x);
        new_term(Each_term, Frac(f_x, f_y), Frac(x, y), all_x);
        Final = add(Each_term);
        cout << Final << endl;
    }
    while (true)
    {
        int x, y;
        cout << "enter the value of x " << endl;
        cin >> x >> y;
        cout << Final.value(Frac(x, y)) << endl;
    }

    return 0;
}