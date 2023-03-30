#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void order();
int digits_only(const char *s);
int contains_author_title(char* word);

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
//                order();
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
    }while(strlen(email) < 10 || strlen(email) > 20);
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
    if(strlen(email_address) < 10 || strlen(email_address) > 20){
        return 0;
    }
    return 1;
}

int check_email_valid(char* email_address){

    if(check_email_length(email_address)){

    }
    return 0;
}
