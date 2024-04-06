#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char getLargestChar(FILE* f){
    char new_char;
    char max_char = 0;

    while(!feof(f)){                                             //finds the max char
        fread(&new_char, sizeof(char), 1, f);                    //reads lines and stores it to buffer

        if(new_char == '\n')
            return max_char;
        //printf("char = %d \n", new_char);

        max_char = (new_char > max_char) ? new_char : max_char;
    }

    return max_char;
}


int main() {
    FILE* f = fopen("test.txt", "r");
    if(f == NULL)                                                       //checks if file opens correctly
        return -1;

    int char_value;
    for(int i = 0; !feof(f); i++){ 
        char_value = getLargestChar(f);
        printf("%d:  %d \n", i, char_value);
    }
}
