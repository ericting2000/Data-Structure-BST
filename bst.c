#include "bst.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void esc_to_exit() {
    char a, b;
    printf("Press enter to continue.\n");
    scanf("%c", &a);
    system("stty -icanon");
    system("stty -echo");
    b = getchar();
    system("stty icanon");
    system("stty echo");
    system("clear");
}

int conti_show() {
    char a, b;
    printf("Press 'N' to show the next product information or press 'R' to back to menu.\n");
    system("stty -icanon");
    system("stty -echo");
    a = getchar();
    if (a == 'N') {
        system("clear");
        system("stty icanon");
        system("stty echo");
        return 1;
    }
    if (a == 'R') {
        system("clear");
        system("stty icanon");
        system("stty echo");
        return 0;
    }
    b = getchar();
    system("stty icanon");
    system("stty echo");
    if (b == 'N') {
        system("clear");
        return 1;
    }
    if (b == 'R') {
        system("clear");
        return 0;
    }
    /*if (a == 'N' || b == 'N') {
        system("clear");
        return 1;
    }
    if (a == 'R' || b == 'R') {
        system("clear");
        return 0;
    }*/
    return 0;
}

void menu() {
    printf("1.Import file\n");
    printf("2.Search product(By product number)\n");
    printf("3.Imoprt product\n");
    printf("4.Delete product\n");
    printf("5.Export product\n");
    printf("6.List all information\n");
    printf("7.Modify product number\n");
    printf("8.Save and Exit\n");
}

node* import_file(char filename[], node* root) {
    int i = 1;
    char n[5];
    int a, b;
    FILE* fp;
    fp = fopen(filename, "r");
    //assert(fp != NULL);
    if (!fp) {
        printf("No such file under the directory\n");
        return NULL;
    }
    while (fscanf(fp, "%s %d %d", n, &a, &b) == 3) {
        root = insert(root, n, a, b);
        i++;
    }
    fclose(fp);
    return root;
}

node* make_node(char p_num[], int prz, int amt) {
    node* newnode = malloc(sizeof(node));
    strcpy(newnode->product_num, p_num);
    newnode->price = prz;
    newnode->amount = amt;
    newnode->left = newnode->right = NULL;
    //node->is_leaf = 1;
    return newnode;
}

node* insert(node* root, char p_num[], int prz, int amt) {
    if (!root) {
        root = make_node(p_num, prz, amt);
        return root;
    }
    if (strcmp(root->product_num, p_num) > 0)
        root->left = insert(root->left, p_num, prz, amt);
    else if (strcmp(root->product_num, p_num) < 0)
        root->right = insert(root->right, p_num, prz, amt);
    return root;
}

node* del(node* root, char p_num[]) {
    if (!root)
        return root;

    if (strcmp(p_num, root->product_num) < 0)
        root->left = del(root->left, p_num);
    else if (strcmp(p_num, root->product_num) > 0)
        root->right = del(root->right, p_num);
    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = minimum(root->right);
        strcpy(root->product_num, temp->product_num);
        root->price = temp->price;
        root->amount = temp->amount;
        root->right = del(root->right, temp->product_num);
    }
    return root;
}

node* search(node* root, char p_num[]) {
    if (!root)
        return NULL;

    if (strcmp(root->product_num, p_num) == 0)
        return root;
    else if (strcmp(root->product_num, p_num) > 0)
        return search(root->left, p_num);
    else
        return search(root->right, p_num);
}

void inorder_pt(node* root) {
    if (root) {
        inorder_pt(root->left);
        printf("     %s           %d        %d\n", root->product_num, root->price, root->amount);
        inorder_pt(root->right);
    }
}

node* inorder_succ(node* root, char p_num[]) {
    node* succ = NULL;
    while (1) {
        if (!root)
            return NULL;

        if (strcmp(p_num, root->product_num) < 0) {
            succ = root;
            root = root->left;
        } else if (strcmp(p_num, root->product_num) > 0)
            root = root->right;
        else {
            if (root->right)
                succ = minimum(root->right);
            break;
        }
    }
    return succ;
}

node* minimum(node* root) {
    while (root->left)
        root = root->left;
    return root;
}

void savetool(node* root, FILE* fp) {
    if (root) {
        savetool(root->left, fp);
        fprintf(fp, "%s %d %d", root->product_num, root->price, root->amount);
        fputs("\n", fp);
        savetool(root->right, fp);
    }
}

void save(char name[], node* root) {
    FILE* fp;
    fp = fopen(name, "w");
    //assert(fp != NULL);
    savetool(root, fp);
    fclose(fp);
}

void freetree(node* root) {
    if (!root)
        return;
    freetree(root->left);
    freetree(root->right);
    free(root);
}