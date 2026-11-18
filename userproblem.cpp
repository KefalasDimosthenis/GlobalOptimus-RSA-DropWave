#include "userproblem.h"
#include <stdio.h>
#include <cmath>

UserProblem::UserProblem()
    : Problem(5)
{
}

double UserProblem::funmin(Data &x)
{
    double sum_sq = 0.0;
    int d = getDimension();

    for(int i = 0; i < d; i++)
    {
        sum_sq += x[i] * x[i];
    }

    double numerator = std::cos(12.0 * std::sqrt(sum_sq));
    double denominator = (0.5 * sum_sq) + 2.0;

    return 1.0 - (numerator / denominator);
}

Data UserProblem::gradient(Data &x)
{

    Data g;
    int d = getDimension();
    g.resize(d);

    double sum_sq = 0.0;
    for(int i = 0; i < d; i++) sum_sq += x[i] * x[i];

    double r = std::sqrt(sum_sq);
    double cos_val = std::cos(12.0 * r);
    double sin_val = std::sin(12.0 * r);
    double denom = 0.5 * sum_sq + 2.0;

    if (r < 1e-10) {
        for(int i = 0; i < d; i++) g[i] = 0.0;
        return g;
    }

    for(int i = 0; i < d; i++)
    {
        double term1 = (12.0 * sin_val * x[i] / r) * denom;
        double term2 = cos_val * x[i];
        g[i] = (term1 + term2) / (denom * denom);
    }

    return g;
}

void UserProblem::init(QJsonObject &params)
{
    int d = params["opt_dimension"].toString().toInt();
    if(d <= 0) d = 5;
    setDimension(d);

    Data l, r;
    l.resize(d);
    r.resize(d);

    for(int i = 0; i < d; i++)
    {
        l[i] = -5.12;
        r[i] = 5.12;
    }

    setLeftMargin(l);
    setRightMargin(r);
}

QJsonObject UserProblem::done(Data &x)
{
    QJsonObject t;
    return t;
}

UserProblem::~UserProblem()
{
}
