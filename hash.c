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

// funcion para crear la hash table
HashTable* createHashTable() {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) return NULL; // no se pudo alocar la tabla hash
    
    ht->capacity = INITIAL_CAPACITY;
    ht->size = 0;
    ht->buckets = (HTEntry**)calloc(INITIAL_CAPACITY, sizeof(HTEntry*));
    
    // no se pudieron alocar las buckets
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }
    
    return ht;
}

void htInsert(HashTable* ht, const char* key, void* value) {
    if (!ht || !key) return;
    
    if ((double)ht->size / ht->capacity >= LOAD_FACTOR_THRESHOLD) {
        resize(ht);
    }
    
    size_t index = hash(key) % ht->capacity;
    HTEntry* entry = ht->buckets[index];
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value; // cambiamos valor existente
            return;
        }
        entry = entry->next;
    }
    
    // creamos nuevo elemento y lo ponemos al principio de la cadena.
    HTEntry* newEntry = createEntry(key, value);
    if (newEntry) {
        newEntry->next = ht->buckets[index];
        ht->buckets[index] = newEntry;
        ht->size++;
    }
}

// funcion para obtener valores de la tabla hash
void* htGet(HashTable* ht, const char* key) {
    if (!ht || !key) return NULL;
    
    size_t index = hash(key) % ht->capacity;
    HTEntry* entry = ht->buckets[index];
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    
    return NULL;
}

// funcion para eliminar un elemento de la tabla hash
void htRemove(HashTable* ht, const char* key) {
    if (!ht || !key) return;
    
    size_t index = hash(key) % ht->capacity;
    HTEntry* entry = ht->buckets[index];
    HTEntry* prev = NULL;
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                ht->buckets[index] = entry->next;
            }
            
            free(entry->key);
            free(entry);
            ht->size--;
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

// funcion para destruir la tabla hash
void destroyHashTable(HashTable* ht) {
    if (!ht) return;
    
    for (size_t i = 0; i < ht->capacity; i++) {
        HTEntry* entry = ht->buckets[i];
        while (entry) {
            HTEntry* next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    
    free(ht->buckets);
    free(ht);
}

int htIsEmpty(HashTable* ht) {
    return ht ? ht->size == 0 : 1;
}

size_t htSize(HashTable* ht) {
    return ht ? ht->size : 0;
}