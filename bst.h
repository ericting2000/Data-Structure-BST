#ifndef BST_H_
#define BST_H_

typedef struct node {
    char product_num[3];
    int price, amount;
    struct node *left, *right;
    int is_leaf;
} node;

node* make_tree();
node* import_file(char filename[]);
node* insert();
node* del();
node* search();
node* inorder();
node* freenode();
#endif