#include "fraction.h"
const int max_poly_size = 10;
Frac temp_fraction[1] = {Frac()};
class Pol
{
    Frac coef[max_poly_size];
    int degree;

public:
    Pol(Frac *a = temp_fraction, int size = 1)
    {
        assert(size > 0);
        int start = size - 1;
        for (int i = size - 1; i > 0; i--)
        {
            if (a[i].a_() != 0)
            {
                break;
            }
            start--;
        }
        for (int i = 0; i <= start && i < max_poly_size; i++)
        {
            // assert(a[i].value)
            coef[i] = a[i];
            degree = i;
        }
        assert(degree > -1);
    }
    double value(double x)
    {
        double result = 0;
        for (int i = degree; i >= 0; i--)
        {
            result = result * x + coef[i].value();
        }
        return result;
    }
    double value(Frac f)
    {
        double x = f.value();
        double result = 0;
        for (int i = degree; i >= 0; i--)
        {
            result = result * x + coef[i].value();
        }
        return result;
    }
    void copy(Pol p)
    {
        for (int i = 0; i < p.degree + 1; i++)
        {
            coef[i] = p.coef[i];
        }
        degree = p.degree;
    }

    Pol operator+(Pol p)
    {
        int n_degree = max(degree, p.degree);
        Frac n_coef[n_degree];
        for (int i = 0; i <= n_degree; i++)
        {
            n_coef[i] = An(i) + p.An(i);
        }
        return Pol(n_coef, n_degree + 1);
        // return n_p;
    }
    Pol operator-(Pol p)
    {
        int n_degree = max(degree, p.degree);
        Frac n_coef[n_degree];
        for (int i = 0; i <= n_degree; i++)
        {
            n_coef[i] = An(i) - p.An(i);
        }
        return Pol(n_coef, n_degree + 1);
        // return n_p;
    }

    Pol operator*(Pol p)
    {
        int n_degree = degree + p.degree;
        Frac n_coef[n_degree + 1];
        for (int i = 0; i <= n_degree; i++)
        {
            n_coef[i] = Frac();
        }

        for (int i = 0; i <= p.degree; i++)
        {
            for (int j = 0; j <= degree; j++)
            {
                n_coef[i + j] = n_coef[i + j] + An(j) * (p.An(i));
            }
        }
        return Pol(n_coef, n_degree + 1);
    }

    Pol operator*(Frac f)
    {
        Frac n_coef[degree + 1];
        for (int i = 0; i <= degree; i++)
        {
            n_coef[i] = An(i) * f;
        }
        return Pol(n_coef, degree + 1);
    }

    Frac An(int i)
    {
        assert(i >= 0);
        if (i > degree)
        {
            return Frac();
        }
        return coef[i];
    }

    friend ostream &operator<<(ostream &os, const Pol &temp)
    {
        Pol p = temp;
        // constant term;
        if ((p.An(0)).a_() != 0 || p.degree == 0)
        {
            os << p.coef[0];
        }
        // others
        for (int i = 1; i < p.degree + 1; i++)
        {
            if ((p.coef[i]).is_int())
            {

                if (p.coef[i].a_() > 0)
                {
                    os << "+";
                    if (p.coef[i].a_() != 1)
                    {
                        os << p.coef[i];
                    }
                    os << "x^" << i;
                }
                else if (p.coef[i].a_() < 0)
                {
                    if (p.coef[i].a_() != -1)
                    {
                        os << p.coef[i];
                    }
                    else
                    {
                        os << "-";
                    }
                    os << "x^" << i;
                }
            }
            else
            {
                if (p.coef[i].a_() > 0)
                {
                    os << "+" << p.coef[i] << "x^" << i;
                }
                else if (p.coef[i].a_() < 0)
                {
                    os << p.coef[i] << "x^" << i;
                }
            }
        }
        return os;
    }
};

Pol inverse(Pol p, int precision = 10)
{
    assert((p.An(0)).a_() != 0);
    Frac temp = (p.An(0)).inverse();
    Frac constant = p.An(0);
    p = p - Pol(&constant, 1);
    p = p * Pol(&temp, 1);
    Pol final;
    Pol multiplier = p;
    for (int i = 0; i < precision; i++)
    {
        if (i % 2 == 0)
        {
            final = final + multiplier;
        }
        else
        {
            final = final - multiplier;
        }
        multiplier = multiplier * p;
    }
    final = Pol(&temp, 1) * final;
    final = Pol(&temp, 1) - final;
    return final;
}
