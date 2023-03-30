#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
    char phone_num[14];
    char name[26];
    char email[21];
    do{
        printf("Input phone number[10-13][numeric]: ");
        scanf("%s", phone_num);
        getchar();
    }while(digits_only(phone_num) != 1 || strlen(phone_num) < 10 || strlen(phone_num) > 13);
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
    // check email format

    printf("Insert sucess !\n");
}

int digits_only(const char *s){
    while (*s) {
        if (isdigit(*s++) == 0)
            return 0;
    }
    return 1;
}

int contains_author_title(char* word){
    if(strstr(word, "Mr.") || strstr(word, "Mrs.")){
        return 1;
    }
    return 0;
}

int check_email_length(char* email_address){

    return 1;
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
