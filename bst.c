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
    if (b == 27) exit(0);
    system("clear");
}

int conti_show() {
    char a, b;
    printf("Press n to show the next product information or press r to back to menu.\n");
    system("stty -icanon");
    system("stty -echo");
    a = getchar();
    b = getchar();
    system("stty icanon");
    system("stty echo");
    if (a == 'n' || b == 'n') {
        system("clear");
        return 1;
    };
    if (a == 'r' || b == 'r') {
        system("clear");
        return 0;
    }
    return 0;
}

void menu() {
    printf("1.Import file\n");
    printf("2.Search product(By product number)\n");
    printf("3.Search product(By the highest price)\n");
    printf("4.Imoprt product\n");
    printf("5.Delete product\n");
    printf("6.Export product\n");
    printf("7.List all information\n");
    printf("8.Modify product number\n");
    printf("9.Save and Exit\n");
}

node* import_file(char filename[], node* root) {
    int i = 1;
    char n[5];
    int a, b;
    FILE* fp;
    fp = fopen(filename, "r");
    assert(fp != NULL);
    if (!fp) {
        printf("No such file under the directory\n");
    }
    while (fscanf(fp, "%s %d %d", n, &a, &b) == 3) {
        root = insert(root, n, a, b);
        //printf("insert--%d\n", i);
        //printf("%s\n", root->product_num);
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
    //printf("root->product_num is %s\n", root->product_num);
    //printf("p_num is %s\n", p_num);
    //printf("prz is %d\n", prz);
    //printf("amt is %d\n", amt);
    //printf("----------------\n");
    if (!root) {
        //printf("insert TREE\n");
        root = make_node(p_num, prz, amt);
        return root;
    }
    /*if (root) {
        printf("大小：%d\n", strcmp(root->product_num, p_num));
    }*/
    if (strcmp(root->product_num, p_num) > 0) {
        //printf("TURE LEFT\n");
        root->left = insert(root->left, p_num, prz, amt);
    } else if (strcmp(root->product_num, p_num) < 0) {
        //printf("TURN RIGHT\n");
        root->right = insert(root->right, p_num, prz, amt);
    }
    /*else {
        node* newnode = make_node(p_num, prz, amt);
        node* tmp = root;
        while (tmp) {
            if (tmp->is_leaf) {
                if (tmp->product_num > p_num) {
                    tmp->left = newnode;
                    tmp->is_leaf = 0;
                    break;
                } else {
                    tmp->right = newnode;
                    tmp->is_leaf = 0;
                    break;
                }
            } else {
                if (tmp->product_num > p_num) {
                    if (!tmp->left) {
                        tmp->left = newnode;
                        break;
                    }
                    tmp = tmp->left;
                } else {
                    if (!tmp->right) {
                        tmp->right = newnode;
                        break;
                    }
                    tmp = tmp->right;
                }
            }
        }
    }*/
    return root;
}

node* del(node* root, char p_num[]) {
    // base case
    if (!root)
        return root;
    // If the key to be deleted
    // is smaller than the root's
    // key, then it lies in left subtree
    if (strcmp(p_num, root->product_num) < 0)
        root->left = del(root->left, p_num);
    // If the key to be deleted
    // is greater than the root's
    // key, then it lies in right subtree
    else if (strcmp(p_num, root->product_num) > 0)
        root->right = del(root->right, p_num);
    // if key is same as root's key,
    // then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        struct node* temp = minimum(root->right);

        // Copy the inorder
        // successor's content to this node
        strcpy(root->product_num, temp->product_num);
        root->price = temp->price;
        root->amount = temp->amount;

        // Delete the inorder successor
        root->right = del(root->right, temp->product_num);
    }
    return root;
}

node* search(node* root, char p_num[]) {
    if (!root) {
        //printf("ROOT is NULL\n");
        return NULL;
    }
    if (strcmp(root->product_num, p_num) == 0) {
        //printf("SEARCH FINISHED\n");
        return root;
    } else if (strcmp(root->product_num, p_num) > 0) {
        //printf("TURN LEFT\n");
        return search(root->left, p_num);
    } else {
        //printf("TURN RIGHT\n");
        return search(root->right, p_num);
    }
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
        // if given key is less than the root node, visit left subtree
        if (strcmp(p_num, root->product_num) < 0) {
            // update successor to current node before visiting left subtree
            succ = root;
            root = root->left;
        }
        // if given key is more than the root node, visit right subtree
        else if (strcmp(p_num, root->product_num) > 0) {
            root = root->right;
        }
        // if node with key's value is found, the successor is minimum value
        // node in its right subtree (if any)
        else {
            if (root->right)
                succ = minimum(root->right);
            break;
        }
        // if key doesn't exist in binary tree
        if (!root)
            return NULL;
    }
    return succ;
}

node* minimum(node* root) {
    while (root->left)
        root = root->left;
    return root;
}

void save(char name[], node* root) {
    FILE* fp;
    fp = fopen(name, "w");
    assert(fp != NULL);
    fclose(fp);
}