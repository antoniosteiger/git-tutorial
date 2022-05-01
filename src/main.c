#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "espl_lib.h"

#define isnumber(n) (( n>=48 && n<=57 )? 1 : 0)
#define BUFFERSIZE 6

int make_int(char* buffer){
    unsigned int number = 0;
    int dec_multiplicator = 1;
    int i = BUFFERSIZE-1;
    
    //Find end of number
    while(i >= 0 && buffer[i] != '\n') { i--; }
    
    //Go through number digit by digit and add it to an actual int
    for(i--; i >= 0; i--){
            if(isnumber(buffer[i])){
            number = number + dec_multiplicator * ( buffer[i] - 48);
            dec_multiplicator *= 10;
            }
            else if(buffer[i] != '\n' || buffer[i] != '\0'){
                number = -1;
            }
        }
    return number;
}

int main(int argc, char** argv){
    char* buffer = calloc(BUFFERSIZE, sizeof(char));
    while(1){
        //Get the number from the user
        printf("Welcome. Please enter any number with no more than %d digits:\n", BUFFERSIZE-2); 
        fgets(buffer, BUFFERSIZE, stdin);

        //Turn the ascii code input into an unsigned int and print results
        unsigned int number = make_int(buffer);
        if(number != -1){
            printf("Number: %i \n", number);
            printf("%s \n", num_to_words(number));
            printf("Would you like to enter another number? Yes (y) or no (n)?\n");
            fgets(buffer, BUFFERSIZE, stdin);
            if(buffer[0] == 'y'){
                memset(buffer, 0, BUFFERSIZE);
                continue;
            }
            else{ break; }
        }
        else{
            printf("Sorry, this is not a valid number. Numbers with %d digits from 0 to 9 are supported.\n", BUFFERSIZE-2);
            printf("Would you like to try again? Yes (y) or no (n)?\n");
            fgets(buffer, BUFFERSIZE, stdin);
            if(buffer[0] == 'y'){
                memset(buffer, 0, BUFFERSIZE);
                continue;
            }
            else{ break; }
        }
    }
    printf("Thanks, bye.\n");
    free(buffer);
    return 0;
}