#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>

typedef struct HashTable HashTable;

HashTable* createHashTable();
void htInsert(HashTable* ht, const char* key, void* value);
void* htGet(HashTable* ht, const char* key);
void htRemove(HashTable* ht, const char* key);
void destroyHashTable(HashTable* ht);
int htIsEmpty(HashTable* ht);
size_t htSize(HashTable* ht);

#endif
