#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct node{
    long long int noHP;
    char name[26];
    char email[21];
    int point;
    struct node *right;
    struct node *left;
};

struct node* tree = NULL;

void insert(struct node **root, long long int value, char* name, char* email, int point);
struct node *createNode(struct node *parent, long long int value, char* name, char* email, int point);
void order(long long int phone_num);
int contains_author_title(char* word);
int is_email(char *str);
void order_drink(long long int phone_num);
struct node* search(struct node* curr, long long int phone_num);
int totalNodes(struct node* tree);
void InOrder(struct node* tree);
void remove_customer();
struct node* minValueNode(struct node* node);
struct node* deleteNode(struct node* root, long long int noHP);


int main(){
    long long int phone_num;
    int input_main;
    do{
        system("cls");
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
                do{
                    printf("Input phone number[10-13][numeric]: ");
                    scanf("%lld", &phone_num);
                    getchar();
                }while(phone_num < 1000000000 || phone_num > 1000000000000);
                if(search(tree, phone_num) != 0){
                    order_drink(phone_num);
                }
                else{
                    order(phone_num);
                }
                break;
            case 2:
                if(totalNodes(tree) == 0){
                    printf("There is no data !\n");
                    printf("\nPress Enter to continue...");
                    getchar();
                }else{
                    printf("--------------------------------------------------------------------------------------\n");
                    printf("| %-26s | %-16s | %-21s | %-10s |\n", "Name", "Phone Number", "Email", "Points");
                    printf("--------------------------------------------------------------------------------------\n");
                    InOrder(tree);
                    printf("\nPress Enter to continue...");
                    getchar();
                }
                break;
            case 3:
                remove_customer();
                break;
            default:
                break;
        }
    }while(input_main != 4);
    return 0;
}

void order(long long int phone_num){
    char name[26];
    char email[21];
    int point = 10;
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
    insert(&tree, phone_num, name, email, point);

    printf("Insert sucess !\n");
    printf("\nPress Enter to continue...");
    getchar();
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

struct node *createNode(struct node *parent, long long int value, char* name, char* email, int point) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->noHP = value;
    strcpy(newNode->name, name);
    strcpy(newNode->email, email);
    newNode->point = point;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insert(struct node **root, long long int value, char* name, char* email, int point){
    if (*root == NULL) {
        *root = createNode(NULL, value, name, email, point);
    } else if (value < (*root)->noHP) {
        if ((*root)->left == NULL) {
            struct node *temp = createNode(*root, value, name, email, point);
            (*root)->left = temp;
        } else {
            insert(&((*root)->left), value, name, email, point);
        }
    } else if (value > (*root)->noHP) {
        if ((*root)->right == NULL) {
            struct node *temp = createNode(*root, value, name, email, point);
            (*root)->right = temp;
        } else {
            insert(&((*root)->right), value, name, email, point);
        }
    }
}

void order_drink(long long int phone_num){
    int i = 0;
    char drink[10][25];
    int qty[i];
    double total;
    char again;
    char option;
    int point;
    int used_point;

    struct node* temp = search(tree, phone_num);

    if(temp->point >= 25){
        printf("Do you want to use your points[You have %d][y|n]: ", temp->point);
        scanf("%c", &option);
        getchar();

        if(option == 'y'){
            do{
                printf("How much[%d left]: ", temp->point);
                scanf("%d", &used_point);
                getchar();
            }while(used_point % 25 > 0);
            temp->point -= used_point;
            printf("\nYou have %d free drink(s) left.\n\n", used_point/25);
        }
    }

    do{
        do{
            printf("Input drink[Cafe Latte|Caramel Macchiato|Cappuccino|Cafe Mocha]: ");
            scanf("%[^\n]", drink[i]);
            getchar();
        }while((strcmp(drink[i], "Cafe Latte") != 0) && (strcmp(drink[i], "Caramel Macchiato") != 0) &&
               (strcmp(drink[i], "Cappuccino") != 0) && (strcmp(drink[i], "Cafe Mocha") != 0));

        do{
            printf("Input drink quantity[>= 1]: ");
            scanf("%d", &qty[i]);
            getchar();
        }while(qty[i] < 1);
        i++;
        printf("Do you want to order more[y|n]: ");
        scanf("%c", &again);
        getchar();
    }while(again != 'n');

    printf("Order Summary:\n");
    for(int j = 0; j < i; j++){
        printf("%s\t%dx - %d\n", drink[j], qty[j], qty[j]*30000);
        total += (qty[j]*30000) - ((used_point/25)*30000);
    }
    printf("Total: %.lf\n", total);
    point = total/50000;
    point = point*3;
    printf("Point Obtained: %d\n", point);
    temp->point += point;
    printf("\nPress Enter to continue...");
    getchar();
}

struct node* search(struct node* curr, long long int phone_num){
    if(curr == NULL){
        return curr;
    }

        // phone num found
    else if(phone_num == curr->noHP){
        return curr;
    }

        // phone->left
    else if(phone_num < curr->noHP){
        return search(curr->left, phone_num);
    }

        // phone-right
    else if(phone_num > curr->noHP){
        return search(curr->right, phone_num);
    }
}

int totalNodes(struct node* tree){
    if(tree == NULL){
        return 0;
    }
    return (totalNodes(tree->left) + totalNodes(tree->right) + 1);
}

void InOrder(struct node* tree){
    if(tree != NULL){
        InOrder(tree->left);
        printf("| %-26s | 0%-15lld | %-21s | %-10d |\n", tree->name, tree->noHP, tree->email, tree->point);
        printf("--------------------------------------------------------------------------------------\n");
        InOrder(tree->right);
    }
}

void remove_customer(){
    long long int phone_num;
    if(tree == NULL){
        printf("There is no data !\n");
        printf("\nPress Enter to continue ...");
        getchar();
    }
    else{
        printf("Input phone number: ");
        scanf("%lld", &phone_num);
        getchar();
        if(search(tree, phone_num) == NULL){
            printf("Data invalid!\n");
            printf("\nPress Enter to continue ...");
            getchar();
        }
        else if(search(tree, phone_num) != NULL){
            tree = deleteNode(tree, phone_num);
            printf("Delete success!\n");
            printf("\nPress Enter to continue ...");
            getchar();
        }
    }
}

struct node* minValueNode(struct node* node) {
    struct node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct node* deleteNode(struct node* root, long long int noHP) {
    if (root == NULL) {
        return root;
    }
    if (noHP < root->noHP) {
        root->left = deleteNode(root->left, noHP);
    }
    else if (noHP > root->noHP) {
        root->right = deleteNode(root->right, noHP);
    }
    else {
        if (root->left == NULL) {
            struct node* temp = (struct node *) root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = (struct node *)root->left;
            free(root);
            return temp;
        }
        struct node* temp = minValueNode(root->right);
        root->noHP = temp->noHP;
        root->right = deleteNode(root->right, temp->noHP);
    }
    return root;
}