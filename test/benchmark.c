//
// Created by martin on 1/28/21.
//


#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "hash_table.h"

// Hash table stress test



int main(void) {

    hashtable* ht=NULL;
    int num_tests = 50000000;
    assert(allocate(&ht, num_tests)==0);

    int seed = 2;
    srand(seed);
    printf("Performing stress test. Inserting 50 million keys.\n");

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    for (int i = 0; i < num_tests; i += 1) {
        int key = rand();
        int val = rand();
        assert(put(ht, key, val)==0);
    }

    gettimeofday(&stop, NULL);
    double secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("50 million insertions took %f seconds\n", secs);

    assert(deallocate(ht)==0);

    return 0;
}
