//
// Created by martin on 1/29/21.
//

#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "hash_table.h"

#define RUN_TEST(f) printf("Running %s...\t", #f); \
                    f();                           \
                    printf("Completed %s\n", #f);

void test_alloc(){
    hashtable *ht = NULL;
    int size = 5000000;
    allocate(&ht, size);
//    printf("%ld %ld %p\n", ht->capacity, ht->count, ht->data);
    assert(ht->capacity == 3*size);
    assert(ht->count == 0);
    assert(ht->data != NULL);
    for(int i = 0; i < ht->capacity; ++i){
        ListNode n = ht->data[i];
        assert(&n != NULL);
//        printf("%d: ListNode{next: %p, val: [%d %d], full: %x }\n", i, n.next, n.val[0], n.val[1], n.full);
        assert(n.next == 0);
        assert(n.keypairs[0] == 0);
        assert(n.keypairs[1] == 0);
        assert(n.keypairs[2] == 0);
        assert(n.keypairs[3] == 0);
        assert(n.full == 0);
    }
    deallocate(ht);
}


int main(void){
    printf("Running unit tests\n");
    RUN_TEST(test_alloc);
    return 0;
}