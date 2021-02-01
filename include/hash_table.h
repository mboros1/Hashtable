#ifndef HASH_TABLE
#define HASH_TABLE

#include <stddef.h>
#include <stdint.h>

// linked list set as a fat node; each node contains 2 key-value pairs, makes pointer-dereferencing less likely if
// hashes are well distributed
typedef struct list_node ListNode;
struct list_node {
    // 0,1 is key,value 1, 2,3 is key,value 2
    int keypairs[4];
    // link to next fat node
    ListNode* next;
    // boolean value, set when key-value slot taken, unset when it's open
    uint8_t full[2];
};
typedef struct hash_table hashtable;
struct hash_table{
    // array of data; most cases the leaves have a length of 1 so array access is faster
    ListNode* data;
    // the total capacity of the hashmap
    int capacity;
    // current number of elements placed
    int count;
};

typedef int keyType;
typedef int valType;

int allocate(hashtable** ht, int size);
int put(hashtable* ht, keyType key, valType value);
int get(hashtable* ht, keyType key, valType *values, int num_values, int* num_results);
int erase(hashtable* ht, keyType key);
int deallocate(hashtable* ht);

#endif