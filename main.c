#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.c"
#include "bst.h"

int main() {
    char option[2];
    char filename[50];
    printf("Please select the operation from below:\n");
    menu();
    while (scanf("%s", option) == 1) {
        //printf("%s\n", option);
        if (strcmp("1", option) == 0) {
            system("clear");
            printf("Please insert the file name in this form : (XXX.txt)\n");
            scanf("%s", filename);
            import_file(filename);
        }
        if (strcmp("2", option) == 0) {
        }
        if (strcmp("3", option) == 0) {
        }
        if (strcmp("4", option) == 0) {
        }
        if (strcmp("5", option) == 0) {
        }
        if (strcmp("6", option) == 0) {
        }
        if (strcmp("7", option) == 0) {
        }
        if (strcmp("8", option) == 0) {
        }
        if (strcmp("9", option) == 0) {
            system("clear");
            printf("Your file has been saved successfully,see you soon!\n");
            exit(0);
        }
        esc_to_exit();
        printf("Please select the operation from below:\n");
        menu();
    }
}