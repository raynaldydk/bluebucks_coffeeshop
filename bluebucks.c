#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

struct node{
    long long int noHP;
    struct node *right;
    struct node *left;
};

struct node *createNode(struct node *parent, long long int value);
void insert(struct node **root, long long int value);
void inorderTraversal(struct node *tree);
void order();
int digits_only(const char *s);
int contains_author_title(char* word);
int is_email(char *str);

int main(){
    int input_main;
    do{
        printf("BlueBucks\n");
        printf("=============\n");
        printf("1. Process Order\n");
        printf("2. View All Customer\n");
        printf("3. Remove Customer\n");
        printf("4. Exit\n");
        printf(">>");
        scanf("%d", &input_main);
        getchar();
        switch(input_main){
            case 1:
                order();
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                break;
        }
    }while(input_main != 4);
    return 0;
}

void order(){
    long long int phone_num;
    char name[26];
    char email[21];
    int nDigits;
    do{
        printf("Input phone number[10-13][numeric]: ");
        scanf("%lld", &phone_num);
        getchar();
    }while(phone_num < 1000000000 || phone_num > 1000000000000);
//    check phone number exist or not

    do{
        printf("Input name[5-25][Mr. | Mrs.]: ");
        scanf("%[^\n]", name);
        getchar();
    }while(strlen(name) < 5 || strlen(name) > 25 || contains_author_title(name) != 1);

    do{
        printf("Input email[10-20][email format]: ");
        scanf("%s", email);
        getchar();
    }while(!is_email(email));

    // Insert BST

    printf("Insert sucess !\n");
}

int contains_author_title(char* word){
    if(strstr(word, "Mr.") || strstr(word, "Mrs.")){
        return 1;
    }
    return 0;
}

int is_email(char *str) {
    int len = strlen(str);
    int at_index = -1, dot_index = -1;

    if(strlen(str) < 10 || strlen(str) > 20){
        return 0;
    }

    // Find the position of the "@" symbol and the last "."
    for (int i = 0; i < len; i++) {
        if (str[i] == '@') {
            at_index = i;
        }
        else if (str[i] == '.') {
            dot_index = i;
        }
    }

    // Check that both the "@" symbol and the last "." are present
    if (at_index == -1 || dot_index == -1) {
        return 0;
    }

    // Check that the "@" symbol comes before the last "."
    if (at_index > dot_index) {
        return 0;
    }

    // Check that there is at least one character before the "@"
    if (at_index == 0) {
        return 0;
    }

    // Check that there is at least one character between the "@" and the last "."
    if (dot_index - at_index < 2) {
        return 0;
    }

    // Check that there is at least one character after the last "."
    if (len - dot_index <= 1) {
        return 0;
    }

    return 1;
}

struct node *createNode(struct node *parent, long long int value) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->noHP = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insert(struct node **root, long long int value){
    if (*root == NULL) {
        *root = createNode(NULL, value);
    } else if (value < (*root)->noHP) {
        if ((*root)->left == NULL) {
            struct node *temp = createNode(*root, value);
            (*root)->left = temp;
        } else {
            insert(&((*root)->left), value);
        }
    } else if (value > (*root)->noHP) {
        if ((*root)->right == NULL) {
            struct node *temp = createNode(*root, value);
            (*root)->right = temp;
        } else {
            insert(&((*root)->right), value);
        }
    }
}

void inorderTraversal(struct node *tree) {
    if (tree != NULL) {
        inorderTraversal(tree->left);
        printf("%lld\n", tree->noHP);
        inorderTraversal(tree->right);
    }
    getchar();
}
