//
// Created by martin on 1/29/21.
//

#include "miller_rabin.h"

#include "miller_rabin.h"
#include <stdlib.h>

// generate a random number less than or equal to x
size_t random_number(size_t x) {
    size_t divisor = RAND_MAX/(x+1);
    size_t retval;
    do {
        retval = rand()/divisor;
    } while (retval > x);
    return retval;
}

// only positive exponents. Vulnerable to overflow
size_t power(size_t x, size_t y) {
    size_t ret = 1;
    if (y == 0) {
        return ret;
    }
    if (y < 0) {
        return -1;
    }
    for (int i = 0; i < y; ++i) {
        ret *= x;
    }
    return ret;
}

// calculate a^b mod n
size_t power_mod(size_t a, size_t b, size_t n) {
    size_t x = 1, y = a;
    while (b > 0) {
        if (b%2 == 1) {
            x =(x*y)%n;
        }
        y = (y*y)%n;
        b /= 2;
    }
    return x%n;
}

int miller_rabin(size_t x) {
    if (x < 2 || (x > 2 && x%2 == 0)) {
        return 0;
    }
    size_t d = x-1;
    size_t s = 0;
    while (d % 2 == 0) {
        d = d / 2;
        ++s;
    }
    size_t k = 30;
    for(int i =0; i < k; ++i) {
        size_t a = random_number(x-1);
        if (a < 2) {
            a = 2;
        }
        for (int j = 0; j <  s; ++j) {
            size_t root  = power_mod(a,power(2,s)*d,x);
            if (root != 1 && root != x-1) {
                return 0;
            }
        }
    }
    return 1;
}