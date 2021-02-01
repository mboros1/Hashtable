//
// Created by martin on 1/28/21.
//

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "hash_table.h"
#include "miller_rabin.h"


// Initialize the components of a hashtable.
// The size parameter is the expected number of elements to be inserted.
// This method returns an error code, 0 for success and -1 otherwise (e.g., if the parameter passed to the method is not null, if malloc fails, etc).
int allocate(hashtable** ht, int size) {
    // allocates hash table, capacity is set to 3x the size to minimize possibility of collisions
    *ht = malloc(sizeof(hashtable));
    if (!(*ht)) {
        fprintf(stderr, "failed to malloc hashtable\n");
        return -1;
    }
//    int n = size;
//    n--;
//    n |= n >> 1;   // Divide by 2^k for consecutive doublings of k up to 32,
//    n |= n >> 2;   // and then or the results.
//    n |= n >> 4;
//    n |= n >> 8;
//    n |= n >> 16;
//    n++;

    size_t n = size % 2 == 0 ? 3*size+1 : 3*size;
    while(!miller_rabin(n)){
        n += 2;
    }

    printf("Size: %ld\n", n);

    (*ht)->capacity = n;
    (*ht)->count = 0;
    (*ht)->data = malloc(n*sizeof(ListNode));
    if (!((*ht)->data)){
        fprintf(stderr, "Failed to malloc hashtable data\n");
        return -1;
    }
    memset((*ht)->data, 0, n*sizeof(ListNode));

    return 0;
}


// This method inserts a key-value pair into the hash table.
// It returns an error code, 0 for success and -1 otherwise (e.g., if malloc is called and fails).
int put(hashtable* ht, keyType key, valType value) {
    int bucket = key % (ht->capacity);
    ListNode* n = &(ht->data[bucket]);
    uint8_t* full = n->full;

    do {
        if (full[0] == 0){
            n->keypairs[0] = key;
            n->keypairs[1] = value;
            n->full[0]++;
            return 0;
        } else if (full[1] == 0) {
            n->keypairs[2] = key;
            n->keypairs[3] = value;
            n->full[1]++;
            return 0;
        } else if (!(n->next)){
            ListNode* next = malloc(sizeof(ListNode));
            if (!next) return -1;
            next->keypairs[0] = key;
            next->keypairs[1] = value;
            next->full[0]++;
            n->next = next;
            return 0;
        }
        n = n->next;
    }
    while (n);

    return 0;
}

// This method retrieves entries with a matching key and stores the corresponding values in the
// values array. The size of the values array is given by the parameter
// num_values. If there are more matching entries than num_values, they are not
// stored in the values array to avoid a buffer overflow. The function returns
// the number of matching entries using the num_results pointer. If the value of num_results is greater than
// num_values, the caller can invoke this function again (with a larger buffer)
// to get values that it missed during the first call.
// This method returns an error code, 0 for success and -1 otherwise (e.g., if the hashtable is not allocated).
int get(hashtable* ht, keyType key, valType *values, int num_values, int* num_results) {
    size_t bucket = key % (ht->capacity);
    ListNode* n = &(ht->data[bucket]);
    int i = 0;
    do {
        uint8_t* full = n->full;
        if (full[0] && n->keypairs[0] == key){
            values[i++] = n->keypairs[1];
        }
        if (full[1] && n->keypairs[2] == key){
            values[i++] = n->keypairs[3];
        }
        n = n->next;
    } while (n && i < num_values);

    *num_results = i;

    return 0;
}

// This method erases all key-value pairs with a given key from the hash table.
// It returns an error code, 0 for success and -1 otherwise (e.g., if the hashtable is not allocated).
int erase(hashtable* ht, keyType key) {
    size_t bucket = key % (ht->capacity);
    ListNode* n = &(ht->data[bucket]);
    ListNode* next = n;
    while(next){
        if (n->keypairs[0] == key){
            n->keypairs[0] = 0;
            n->keypairs[1] = 0;
            n->full[0]--;
        }
        if (n->keypairs[2] == key){
            n->keypairs[2] = 0;
            n->keypairs[3] = 0;
            n->full[1]--;
        }
        if ( (next->full[0]+next->full[1]) == 0 && next != n){
            ListNode* temp = next->next;
            *next = *temp;
            free(temp);
        }
        next = next->next;
    }

    return 0;
}

// This method frees all memory occupied by the hash table.
// It returns an error code, 0 for success and -1 otherwise.
int deallocate(hashtable* ht) {
    ListNode* dat = ht->data;

    // iterate over array data, freeing any linked lists encountered
    for(int i = 0; i < ht->capacity; ++i){
        ListNode* n = &(dat[i]);
        while(n->next){
            ListNode* temp = n->next;
            n->next = temp->next;
            free(temp);
        }
    }
    // free the data array and then rest of hashtable data
    free(dat); free(ht);
    return 0;
}

