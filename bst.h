#ifndef BST_H_
#define BST_H_

typedef struct node {
    char product_num[5];
    int price, amount;
    struct node *left, *right;
    //int is_leaf;
} node;

node* make_node(char p_num[], int prz, int amt);
node* import_file(char filename[], node* root);
node* insert(node* root, char p_num[], int prz, int amt);
node* del(node* root, char p_num[]);
node* search(node* root, char p_num[]);
void inorder_pt(node* root);
node* inorder_succ(node* root, char p_num[]);
node* minimum(node* root);
void save(char name[], node* root);
#endif