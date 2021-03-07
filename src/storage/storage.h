//
// Created by Черных Никита Алекандрович on 3/5/21.
//

#ifndef TECHNO_IZ1_STORAGE_H
#define TECHNO_IZ1_STORAGE_H

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char *type;
    char *colour;
    char *name;
} Metadata;

typedef struct {
    size_t size;
    size_t capacity;

    Metadata *data;
} Element;

typedef struct {
    size_t size_multiplier;
    size_t size;
    size_t capacity;
    size_t load_maximum;

    size_t hash_base;
    size_t step;

    Element *map;
} Storage;

bool add(Metadata *element, Storage *st);

void print_values(Storage *st);

Storage *create_storage(size_t size_multiplier, size_t size, size_t capacity, size_t load_maximum, size_t hash_base, size_t step);

void free_storage(Storage *st);


#endif //TECHNO_IZ1_STORAGE_H
