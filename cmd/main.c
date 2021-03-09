//
// Created by Черных Никита Алекандрович on 3/5/21.
//
#include <stdio.h>
#include <storage.h>
#include <string.h>
#include <stdlib.h>

const size_t size_multiplier = 2;
const size_t size = 0;
const size_t capacity = 2;
const size_t load_maximum = 2 / 3;

const size_t hash_base = 519;
const size_t step = 1;


int main() {

    Storage *st = create_storage(size_multiplier, size, capacity, load_maximum, hash_base, step);

    Metadata el = {"aaa", "bbbb", "cccc"};
//    for(int i = 0; i < 4 ; ++i) {
//        add(&el, st);
//        el.colour +=i;
//        el.name += i;
//        el.type +=i;
//    }
    add(&el, st);
    add(&el, st);
    add(&el, st);
    add(&el, st);

    Metadata el1 = {"aaa1", "bbbb", "cccc"};

    add(&el, st);
    add(&el1, st);
    add(&el1, st);
    add(&el1, st);
    add(&el1, st);

    print_values(st);
    free_storage(&st);

    return 0;
}