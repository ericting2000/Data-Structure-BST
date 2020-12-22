#include "bst.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void esc_to_exit() {
    char a, b;
    printf("Press esc to quit or enter to continue.\n");
    scanf("%c", &a);
    system("stty -icanon");
    system("stty -echo");
    b = getchar();
    system("stty icanon");
    system("stty echo");
    if (b == 27) exit(0);
    system("clear");
}

void menu() {
    printf("1.Import file\n");
    printf("2.Search product(By name)\n");
    printf("3.Search product(By the highest price)\n");
    printf("4.Imoprt product\n");
    printf("5.Delete product\n");
    printf("6.Export product\n");
    printf("7.List all information\n");
    printf("8.Modify product number\n");
    printf("9.Save and Exit\n");
}

node* import_file(char filename[]) {
    FILE* fp;
    fp = fopen(filename, "r");
    if (!fp) {
        printf("No such file under the directory\n");
    }

    fclose(fp);
}