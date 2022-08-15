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

Pol function(vector<Frac> y, Frac dif[50][50], int x)
{
    Pol result;
    Pol multiplier(&one,1);
    for (int i = 0; i <= x ; i++)
    {
        Frac a[2] = {y[i]*(-1),one};
        result = result + multiplier * dif[i][0];
        multiplier = multiplier * Pol(a,2);
    }
    return result;
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
    Frac difference[50][50];
    vector<Frac> all_x;
    Pol Final;
    for (int iter = 0; true; iter++)
    {
        int f_x, f_y, x, y;
        cout << "enter the value of x and f(x)" << endl;
        cin >> x;
        if (x == -1)
        {
            break;
        }
        cin >> y >> f_x >> f_y;
        if (check(all_x, Frac(x, y)))
        {
            cout << " invalid " << endl;
            continue;
        }
        difference[0][iter] = Frac(f_x, f_y);
        all_x.push_back(Frac(x,y));
        for (int i = 0; i < iter; i++)
        {
            difference[i + 1][iter - i - 1] = (difference[i][iter - i] - difference[i][iter - i - 1]) * ((all_x[iter] - all_x[iter - i - 1]).inverse());
        }
        Final = function(all_x,difference,iter);
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