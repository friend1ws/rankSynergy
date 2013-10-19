#ifndef __RANDOM_H__
#define __RANDOM_H__
#include <cstdlib>
#define RANDOM static_cast<double>(rand()) / static_cast<double>(RAND_MAX + 1.0)

double exprand (void);
double gamrand (double a);
double betarand(double b_alpha, double b_beta);

template<typename kind> inline 
kind gen_rand(kind max) {
    double tmp = RANDOM;
    return tmp * max;
}

#endif


