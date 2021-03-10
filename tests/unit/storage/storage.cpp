//
// Created by Черных Никита Алекандрович on 3/6/21.
//

#include <gtest/gtest.h>

extern "C" {
#include "storage.h"
}

// default values :
const size_t size_multiplier = 2;
const size_t size = 0;
const size_t capacity = 2;
const size_t load_maximum = 2 / 3;

const size_t hash_base = 519;
const size_t step = 1;

// key data :
const char *key = "aaa";

const size_t expected_hash = 1;

// elements :
char el_first_type[] = "aaa";
char el_first_colour[] = "bbbb";
char el_first_name[] = "cccc";

Metadata el_first = {el_first_type, el_first_colour, el_first_name};

char el_second_type[] = "aaa1";
char el_second_colour[] = "bbbb";
char el_second_name[] = "cccc";
Metadata el_second = {el_second_type, el_second_colour, el_second_name};

// expected map sizes :
const size_t size_first_add = 1;
const size_t size_second_add = 2;
const size_t capacity_before_realoc = 2;
const size_t size_after_realoc = 3;
const size_t capacity_after_realoc = 4;

// expected storage size :
const size_t storage_size_added = 2;
const size_t storage_capacity_allocated = 8;

// used to free allocated maps before free_storage test
void free_map(Element *map, size_t capacity) {
    for (size_t i = 0; i < capacity; ++i) {
        if (map[i].data == NULL) {
            continue;
        }

        free(map[i].data);
        map[i].data = NULL;
    }
    free(map);
}

TEST(initialize, create_map) {
    Element *expected_map = (Element *) calloc(capacity, sizeof(Element));
    EXPECT_TRUE(expected_map != NULL);

    for (size_t i = 0; i < capacity; ++i) {
        expected_map[i].data = NULL;
        expected_map[i].capacity = 0;
        expected_map[i].size = 0;
    }

    Element *got_map = create_map(capacity);
    EXPECT_TRUE(got_map != NULL);

    for (size_t i = 0; i < capacity; ++i) {
        ASSERT_EQ(expected_map[i].data, got_map[i].data);
        ASSERT_EQ(expected_map[i].capacity, got_map[i].capacity);
        ASSERT_EQ(expected_map[i].size, got_map[i].size);
    }

    free_map(expected_map, capacity);
    free_map(got_map, capacity);
}

TEST(initialize, create_storage) {
    Element *expected_map = create_map(capacity);
    EXPECT_TRUE(expected_map != NULL);

    Storage *got_storage = create_storage(size_multiplier, size, capacity, load_maximum, hash_base, step);
    EXPECT_TRUE(got_storage != NULL);
    EXPECT_TRUE(got_storage->map != NULL);

    ASSERT_EQ(capacity, got_storage->capacity);
    ASSERT_EQ(size, got_storage->size);
    ASSERT_EQ(size_multiplier, got_storage->size_multiplier);
    ASSERT_EQ(load_maximum, got_storage->load_maximum);
    ASSERT_EQ(hash_base, got_storage->hash_base);
    ASSERT_EQ(step, got_storage->step);

    for (size_t i = 0; i < capacity; ++i) {
        ASSERT_EQ(expected_map[i].data, got_storage->map[i].data);
        ASSERT_EQ(expected_map[i].capacity, got_storage->map[i].capacity);
        ASSERT_EQ(expected_map[i].size, got_storage->map[i].size);
    }

    free_map(expected_map, capacity);
    free_map(got_storage->map, capacity);
    free(got_storage);
}

TEST(initialize, free_allocated_storage) {
    Storage *got_storage = create_storage(size_multiplier, size, capacity, load_maximum, hash_base, step);
    EXPECT_TRUE(got_storage != NULL);
    EXPECT_TRUE(got_storage->map != NULL);

    free_storage(&got_storage);
    EXPECT_TRUE(got_storage == NULL);
}

TEST(initialize, free_allocated_storage_empty_map) {
    Storage *got_storage = create_storage(size_multiplier, size, capacity, load_maximum, hash_base, step);
    EXPECT_TRUE(got_storage != NULL);

    free_map(got_storage->map, capacity);
    got_storage->map = NULL;
    free_storage(&got_storage);
    EXPECT_TRUE(got_storage == NULL);
}

TEST(initialize, free_empty_storage) {
    Storage *got_storage = NULL;

    free_storage(&got_storage);
    EXPECT_TRUE(got_storage == NULL);
}


TEST(hash, get_hash_of_element) {
    Storage *got_storage = create_storage(size_multiplier, size, capacity, load_maximum, hash_base, step);
    EXPECT_TRUE(got_storage != NULL);
    EXPECT_TRUE(got_storage->map != NULL);

    ASSERT_EQ(capacity, got_storage->capacity);
    ASSERT_EQ(size, got_storage->size);
    ASSERT_EQ(size_multiplier, got_storage->size_multiplier);
    ASSERT_EQ(load_maximum, got_storage->load_maximum);
    ASSERT_EQ(hash_base, got_storage->hash_base);
    ASSERT_EQ(step, got_storage->step);

    ASSERT_EQ(expected_hash, hash(key, got_storage));
    free_storage(&got_storage);
}

TEST(add_element, add_element_to_empty_storage) {
    Storage *got_storage = create_storage(size_multiplier, size, capacity, load_maximum, hash_base, step);
    EXPECT_TRUE(got_storage != NULL);
    EXPECT_TRUE(got_storage->map != NULL);

    ASSERT_EQ(capacity, got_storage->capacity);
    ASSERT_EQ(size, got_storage->size);
    ASSERT_EQ(size_multiplier, got_storage->size_multiplier);
    ASSERT_EQ(load_maximum, got_storage->load_maximum);
    ASSERT_EQ(hash_base, got_storage->hash_base);
    ASSERT_EQ(step, got_storage->step);

    EXPECT_TRUE(add(&el_first, got_storage));

    size_t place = hash(el_first.type, got_storage);

    EXPECT_TRUE(got_storage->map[place].size == size_first_add);
    EXPECT_TRUE(got_storage->map[place].capacity == capacity_before_realoc);
    EXPECT_TRUE(got_storage->map[place].data != NULL);
    EXPECT_EQ(got_storage->map[place].data[0].type, el_first.type);
    EXPECT_EQ(got_storage->map[place].data[0].name, el_first.name);
    EXPECT_EQ(got_storage->map[place].data[0].colour, el_first.colour);


    free_storage(&got_storage);
}

TEST(add_element, add_two_element_same_key_to_empty_storage) {
    Storage *got_storage = create_storage(size_multiplier, size, capacity, load_maximum, hash_base, step);
    EXPECT_TRUE(got_storage != NULL);
    EXPECT_TRUE(got_storage->map != NULL);

    ASSERT_EQ(capacity, got_storage->capacity);
    ASSERT_EQ(size, got_storage->size);
    ASSERT_EQ(size_multiplier, got_storage->size_multiplier);
    ASSERT_EQ(load_maximum, got_storage->load_maximum);
    ASSERT_EQ(hash_base, got_storage->hash_base);
    ASSERT_EQ(step, got_storage->step);

    EXPECT_TRUE(add(&el_first, got_storage));
    EXPECT_TRUE(add(&el_first, got_storage));

    size_t place = hash(el_first.type, got_storage);

    EXPECT_TRUE(got_storage->map[place].size == size_second_add);
    EXPECT_TRUE(got_storage->map[place].capacity == capacity_before_realoc);
    EXPECT_TRUE(got_storage->map[place].data != NULL);
    for (size_t i = 0; i < got_storage->map[place].size; ++i) {
        EXPECT_EQ(got_storage->map[place].data[i].type, el_first.type);
        EXPECT_EQ(got_storage->map[place].data[i].name, el_first.name);
        EXPECT_EQ(got_storage->map[place].data[i].colour, el_first.colour);
    }


    free_storage(&got_storage);
}

TEST(add_element, add_three_element_same_key_to_empty_storage) {
    Storage *got_storage = create_storage(size_multiplier, size, capacity, load_maximum, hash_base, step);
    EXPECT_TRUE(got_storage != NULL);
    EXPECT_TRUE(got_storage->map != NULL);

    ASSERT_EQ(capacity, got_storage->capacity);
    ASSERT_EQ(size, got_storage->size);
    ASSERT_EQ(size_multiplier, got_storage->size_multiplier);
    ASSERT_EQ(load_maximum, got_storage->load_maximum);
    ASSERT_EQ(hash_base, got_storage->hash_base);
    ASSERT_EQ(step, got_storage->step);

    EXPECT_TRUE(add(&el_first, got_storage));
    EXPECT_TRUE(add(&el_first, got_storage));
    EXPECT_TRUE(add(&el_first, got_storage));

    size_t place = hash(el_first.type, got_storage);

    EXPECT_TRUE(got_storage->map[place].size == size_after_realoc);
    EXPECT_TRUE(got_storage->map[place].capacity == capacity_after_realoc);
    EXPECT_TRUE(got_storage->map[place].data != NULL);
    for (size_t i = 0; i < got_storage->map[place].size; ++i) {
        EXPECT_EQ(got_storage->map[place].data[i].type, el_first.type);
        EXPECT_EQ(got_storage->map[place].data[i].name, el_first.name);
        EXPECT_EQ(got_storage->map[place].data[i].colour, el_first.colour);
    }


    free_storage(&got_storage);
}

TEST(add_element, add_elements_to_resize_empty_storage) {
    Storage *got_storage = create_storage(size_multiplier, size, capacity, load_maximum, hash_base, step);
    EXPECT_TRUE(got_storage != NULL);
    EXPECT_TRUE(got_storage->map != NULL);

    ASSERT_EQ(capacity, got_storage->capacity);
    ASSERT_EQ(size, got_storage->size);
    ASSERT_EQ(size_multiplier, got_storage->size_multiplier);
    ASSERT_EQ(load_maximum, got_storage->load_maximum);
    ASSERT_EQ(hash_base, got_storage->hash_base);
    ASSERT_EQ(step, got_storage->step);

    EXPECT_TRUE(add(&el_first, got_storage));
    EXPECT_TRUE(add(&el_second, got_storage));

    size_t first_place = hash(el_first.type, got_storage);
    size_t second_place = hash(el_second.type, got_storage);

    EXPECT_TRUE(got_storage->map[first_place].size == size_first_add);
    EXPECT_TRUE(got_storage->map[first_place].capacity == capacity_before_realoc);
    EXPECT_TRUE(got_storage->map[first_place].data != NULL);
    EXPECT_EQ(got_storage->map[first_place].data[0].type, el_first.type);
    EXPECT_EQ(got_storage->map[first_place].data[0].name, el_first.name);
    EXPECT_EQ(got_storage->map[first_place].data[0].colour, el_first.colour);

    EXPECT_TRUE(got_storage->map[second_place].size == size_first_add);
    EXPECT_TRUE(got_storage->map[second_place].capacity == capacity_before_realoc);
    EXPECT_TRUE(got_storage->map[second_place].data != NULL);
    EXPECT_EQ(got_storage->map[second_place].data[0].type, el_second.type);
    EXPECT_EQ(got_storage->map[second_place].data[0].name, el_second.name);
    EXPECT_EQ(got_storage->map[second_place].data[0].colour, el_second.colour);

    EXPECT_EQ(storage_size_added,got_storage->size);
    EXPECT_EQ(storage_capacity_allocated,got_storage->capacity);
    free_storage(&got_storage);
}

