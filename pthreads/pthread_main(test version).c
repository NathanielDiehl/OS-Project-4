#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h> 

#define NUM_THREADS 3
char* fileName = "..\\read_files\\wiki_text.txt";

typedef struct line_data_struct {
    int threadNum;
    long int startLineNum;
    long int endLineNum;
}line_data;



char  getLargestCharInLine(char* str){
    char max_char = 0;

    for(int i = 0; str[i] != '\0' && str[i] != '\n'; i++)                                        //finds the max char
        max_char = (str[i]  > max_char) ? str[i]  : max_char;
    return max_char;
}

void*  readLines(void *arg){
    sleep(1);
    FILE* f = fopen(fileName, "r");
    if(f == NULL)                                                                     //checks if file opens correctly
        return NULL;

    char* line      = (char*) malloc( 2001 );
    int thread_num     = ((line_data*)arg)->threadNum;
    long int start_line_num    = ((line_data*)arg)->startLineNum;
    long int last_line   = ((line_data*)arg)->endLineNum;
    long int position = 0;
    long int position2 = 0;
    
    fseek(f, start_line_num, SEEK_SET);
    if(thread_num != 0){
        fgetpos(f, (fpos_t*)&position);
        
        while(getc(f) != '\n');                                                       //moves to next new line
        fgetpos(f, (fpos_t*)&position2);
        //printf("T%da    %d->%d\n", thread_num, position, position2);
    }


    char max_char;
    for(int line_num = 0;    !feof(f) && (position <= last_line);    line_num++){ 
        if( fscanf( f, "%[^\n]\n", line) == EOF ) break;

        max_char = getLargestCharInLine(line);
        printf("T%d L%d:   %c \n", thread_num, line_num, max_char);
        fgetpos(f, (fpos_t*)&position);
        //printf("T%d L%d:   %d    %s       fp:%d\n", thread_num, line_num, max_char, line, position);
        //printf("T%d L%d:   %s      %d       fp:%d\n", thread_num, line_num, line, max_char, position);
    }
    fclose( f );

    return NULL;
}

int main() {
    FILE* f = fopen(fileName, "r");
    if(f == NULL)                                                       //checks if file opens correctly
        return -1;

    pthread_t newthread[NUM_THREADS];


    long int start_position, end_position;
    fgetpos(f, (fpos_t*)&start_position);
    fseek(f, 0, SEEK_END);
    fgetpos(f, (fpos_t*)&end_position);

    long int line_step = (end_position - start_position) / NUM_THREADS;
    
    printf("start:       %d\n", start_position);
    printf("end:         %d\n", end_position);
    printf("step size:   %d\n\n\n", line_step);

    fclose( f );

    line_data args[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; i++) {
        args[i].threadNum = i;
        args[i].startLineNum = start_position + i*line_step;
        args[i].endLineNum = (i == NUM_THREADS-1) ? end_position : args[i].startLineNum+line_step-1;
        
        printf("start:  %d   ", args[i].startLineNum);
        printf("end:    %d\n", args[i].endLineNum);
        
        pthread_create(&newthread[i%NUM_THREADS], NULL, readLines, &args[i]);
    }
    printf("\n\n\n");

    for(int i = 0; i < NUM_THREADS; i++)
        pthread_join(newthread[i], NULL);
}
