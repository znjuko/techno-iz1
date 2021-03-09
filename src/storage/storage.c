//
// Created by Черных Никита Алекандрович on 3/5/21.
//
#include "storage.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

Element *create_map(size_t capacity) {
    Element *map = (Element *) calloc(capacity, sizeof(Element));
    if (map == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < capacity; ++i) {
        map[i].data = NULL;
        map[i].capacity = 0;
        map[i].size = 0;
    }
    return map;
};

size_t hash(const char *key, Storage *st) {
    size_t place = 0;
    // because multiplying by 0 equals 0
    size_t multiply = 1;

    for (size_t i = 0; i < strlen(key); ++i) {
        place += multiply * key[i];
        multiply *= st->hash_base;
    }

    place %= st->capacity;

    return place;
};

bool resize(Storage *st) {
    size_t old_capacity = st->capacity;
    st->capacity = st->capacity * st->size_multiplier;
    Element *new_map = create_map(st->capacity);

    if (new_map == NULL) {
        return false;
    }

    if (st->map == NULL) {
        st->map = new_map;
        return true;
    }

    for (size_t i = 0; i < old_capacity; ++i) {
        if (st->map[i].data == NULL) {
            continue;
        }

        // if pointer is not NULL -> then there is more then 0 element
        size_t place = hash(st->map[i].data[0].type, st);
        new_map[place] = st->map[i];
    }
    // remove old map and write new map
    free(st->map);
    st->map = new_map;

    return true;
};

bool add(Metadata *element, Storage *st) {
    st->size++;
    if (st->size / st->capacity >= st->load_maximum) {
        if (!resize(st)) {
            return false;
        };
    };

    size_t place = hash(element->type, st);
    // if there is any elements in key and keys are not equal -> increase place to add
    while (st->map[place].data != NULL && strcmp(st->map[place].data[0].type, element->type) != 0) {
        place = (place + st->step) % st->capacity;
    }

    if (st->map[place].data == NULL) {
        st->map[place].data = calloc(st->size_multiplier, sizeof(Metadata));
        st->map[place].size = 0;
        st->map[place].capacity = st->size_multiplier;
    }

    if (st->map[place].size >= st->map[place].capacity) {
        st->map[place].data = (Metadata *) realloc(st->map[place].data,
                                                   st->map[place].capacity * st->size_multiplier * sizeof(Metadata));
        st->map[place].capacity *= st->size_multiplier;
    }

    if (st->map[place].data == NULL) {
        return false;
    }

    st->map[place].data[st->map[place].size] = *element;
    st->map[place].size++;

    return true;
};

void print_values(Storage *st) {
    printf("output:\n");
    printf("{\n");

    for (size_t i = 0; i < st->capacity; ++i) {
        if (st->map[i].data == NULL) {
            continue;
        }
        printf("\t{\n");
        printf("\t\tType: %s;\n", st->map[i].data[0].type);

        printf("\t\tElements:[\n");
        for (size_t j = 0; j < st->map[i].size; ++j) {
            printf("\t\t\t{\n");
            printf("\t\t\t\tName: %s;\n", st->map[i].data[j].name);
            printf("\t\t\t\tColour: %s;\n", st->map[i].data[j].colour);
            printf("\t\t\t};\n");
        }

        printf("\t\t];\n");

        printf("\t};\n");

    }

    printf("};");
};


Storage *create_storage(
        size_t size_multiplier, size_t size,
        size_t capacity, size_t load_maximum,

        size_t hash_base, size_t step) {
    Element *map = create_map(capacity);
    if (map == NULL) {
        return NULL;
    }
    Storage *st = malloc(sizeof(Storage));
    st->size_multiplier = size_multiplier;
    st->size = size;
    st->capacity = capacity;
    st->load_maximum = load_maximum;
    st->hash_base = hash_base;
    st->map = map;
    st->step = step;

    return st;
}


void free_storage(Storage **st) {
    if (*st == NULL) {
        return;
    }

    if ((*st)->map == NULL) {
        free(*st);
        (*st) = NULL;
        return;
    }

    for (size_t i = 0; i < (*st)->capacity; ++i) {
        if ((*st)->map[i].data == NULL) {
            continue;
        }

        free((*st)->map[i].data);
    }

    free((*st)->map);
    free(*st);
    (*st) = NULL;
}