#include <stdio.h>
#include <string.h>
#include <ctype.h>


int handleInput(char *);
void convertToUppercase(char *);
void output(char *, char *, int, int);

int main(int argc, char *argv[]){
    if(argc < 3){
        if(handleInput(argv[1])){
            return 1;
        }        
    }
    else{
        fprintf(stderr, "ERROR: Wrong amount of arguments!\n");
        return 1;
    }
    return 0;
}

int handleInput(char *userInput){

    int max_add_len = 103; // Because of '\n' and '\0' and to help with conditions later on
    int max_chr_len = 127; // From ascii table values

    char currentAddress[max_add_len];
    char potentialAddress[max_add_len];
    char enabledChars[max_chr_len];

    int charCount = 0;
    int addressCount = 0;
    int input_len = 0;
    int address_length = 0;

    if(userInput != NULL){
        input_len = strlen(userInput);
        convertToUppercase(userInput);        
    }
    // initializes enabledChars with 0 in all indices -> instead of storing chars, we store booleans
    for(int position = 0; position < max_chr_len; position++){
        enabledChars[position] = 0;
    }

    while(fgets(currentAddress, sizeof(currentAddress), stdin) != NULL){
        convertToUppercase(currentAddress);
        // (-2) -> to account for \n and \0, (-3) -> no \n to account for in argv[1], only \0 -> so max chars allowed is 100
        address_length = strlen(currentAddress);
        if(address_length > (max_add_len - 2) || input_len > (max_add_len - 3)){
            fprintf(stderr, "ERROR: Max address length exceeded!\n");
            return 1;
        }
        if(strncmp(currentAddress, userInput, input_len) == 0){
            if(enabledChars[(int)currentAddress[input_len]] != 1){
                enabledChars[(int)currentAddress[input_len]] = 1;
                charCount++;
            }
            addressCount++;
            strcpy(potentialAddress, currentAddress);
        }
    }
    output(enabledChars, potentialAddress, addressCount, max_chr_len);
    return 0;
}

void convertToUppercase(char *string){
    for(int index = 0; index < (int)strlen(string); index++){
        string[index] = toupper(string[index]);
    }
}

void output(char *enabledChars, char *potentialAddress, int addressCount, int max_chr_len){
    if(addressCount == 0){
        printf("Not found\n");
    }
    else if(addressCount == 1){
        printf("Found: %s", potentialAddress);
    }
    else{
        printf("Enable: ");
        for(int currentChar = 0; currentChar < max_chr_len; currentChar++){
            if(enabledChars[currentChar] == 1){
                printf("%c", currentChar); // prints all indices as chars if the index stores the value 1
            }
        }
        printf("\n");
    }
}