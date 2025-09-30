#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16 // capacidad inicial
#define LOAD_FACTOR_THRESHOLD 0.75 // si llega al 75% de lleno conseguimos mas espacio

typedef struct HTEntry {
    // usar strings como key nos facilita la funcion hash
    char* key; 
    void* value; 
    struct HTEntry* next;
} HTEntry;

typedef struct HashTable {
    HTEntry** buckets; // buckets para guardar pares key-value
    size_t capacity;
    size_t size;
} HashTable;

// Funcion hash djb2 usada por su simplicidad
static unsigned long hash(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

static HTEntry* createEntry(const char* key, void* value) {
    HTEntry* entry = (HTEntry*) malloc(sizeof(HTEntry));
    if (!entry) return NULL; // si malloc falla retornamos NULL

    entry->key = (char*) malloc(strlen(key)+1);
    if (!entry->key) {
        free(entry);
        return NULL;
    }

    strcpy(entry->key, key);
    entry->value = value;
    entry->next = NULL;
    return entry;
}

// funcion helper para cambiar el tamaño dinamicamente a la tabla hash
static void resize(HashTable* ht) {
    size_t oldCapacity = ht->capacity;
    HTEntry** oldBuckets = ht->buckets;

    ht->capacity *= 2;
    ht->size = 0;
    ht->buckets = (HTEntry**)calloc(ht->capacity, sizeof(HTEntry*));

    if (!ht->buckets) {
        // si no pudimos alocar los buckets usamos los valores viejos
        // y no incrementamos el tamaño
        ht->capacity = oldCapacity;
        ht->buckets = oldBuckets;
        return;
    }

    // volvemos a usar la funcion hash en todos los elementos existentes
    for (size_t i = 0; i < oldCapacity; i++) {
        HTEntry* entry = oldBuckets[i];
        while (entry) {
            HTEntry* next = entry->next;

            size_t index = hash(entry->key) % ht->capacity;
            entry->next = ht->buckets[index];
            ht->buckets[index] = entry;
            ht->size++;
            
            entry = next;
        }
    }
    free(oldBuckets);
}
