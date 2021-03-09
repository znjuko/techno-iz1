//
// Created by Черных Никита Алекандрович on 3/5/21.
//
#include "processing.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>

const size_t size_multiplier = 2;
const size_t size = 0;
const size_t capacity = 2;
const size_t load_maximum = 2 / 3;

const size_t hash_base = 519;
const size_t step = 1;

const char *about = "about";
const char *print = "print";
const char *add_extra = "add";
const char *stop = "stop";

int main() {
    Storage *st = create_storage(size_multiplier, size, capacity, load_maximum, hash_base, step);

    char *cmd = "about";

    do {
        if (!strcmp(cmd, about)) {
            printf("HELP: \n");
            printf("\t'about' - command used to output help info about used commands\n");
            printf("\t'print' - command used to print stored values, grouped by type\n");
            printf("\t'add' - command used to add values to storage\n");
            printf("\t'stop' - command used to stop execution\n");
            continue;
        }

        if (!strcmp(cmd, print)) {
            print_values(st);
            continue;
        }

        if (!strcmp(cmd, stop)) {
            break;
        }

        if (!strcmp(cmd, add_extra)) {
            printf("Input type of animal: ");
            char *type = get_string();

            if(type == NULL) {
                printf("\nfailed to allocate memory; stopping execution...");
                break;
            }

            printf("Input colour of animal: ");
            char *colour = get_string();

            if(colour == NULL) {
                printf("\nfailed to allocate memory; stopping execution...");
                break;
            }

            printf("Input name of animal: ");
            char *name = get_string();

            if(name == NULL) {
                printf("\nfailed to allocate memory; stopping execution...");
                break;
            }

            Metadata animal = {type, colour, name};

            if(!add(&animal, st)){
                printf("\nfailed to add animal to storage; stopping execution...");
                break;
            }

            continue;
        }

        printf("unknown command: %s\n", cmd);
    } while (printf("\nInput command: "), cmd = get_string(), cmd != NULL);


    free_storage(&st);

    return 0;
}