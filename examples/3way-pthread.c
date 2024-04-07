#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define NUM_THREADS 4


typedef struct line_data_struct {
    char* lineStr;
    int lineNum;
}line_data;

struct time_counter begin, end;


long recored_time;

pthread_mutex_t mutexTotal;  // For the char count

void*  getLargestChar(void *arg){
    char* str     = ((line_data*)arg)->lineStr;
    int line_num  = ((line_data*)arg)->lineNum;
    char max_char = 0;

    for(int i = 0; str[i] != '\0' && str[i] != '\n'; i++)                                          //finds the max char
        max_char = (str[i]  > max_char) ? str[i]  : max_char;
    
    printf("%d: %d\n", line_num, max_char);
    return NULL;
}


int main() {
    int err;
    char *line = (char*) malloc( 2001 ); // no lines larger than 2000 chars

    // Initalize mutex
    pthread_mutex_init(&total_mutex, NULL)
    
    // Start recording amont of time it takes to open file and go through for loop/
    gettimeofday(&begin, NULL);
   
//    FILE* f = fopen(/homes/dan/625/wiki_dump.txt, r);   file directory for file we need for checkpoint
    FILE* f = fopen("test.txt", "r");
    if(f == NULL)                                                       //checks if file opens correctly
        return -1;

    pthread_t newthread[NUM_THREADS];

    int char_value;
    line_data args;
    for (int i = 0; !feof(f); i++ )  {
        err = fscanf( f, "%[^\n]\n", line);

        //if( err == EOF ) break;
        args.lineStr = line;
        args.lineNum = i;
        pthread_create(&newthread[i%NUM_THREADS], NULL, getLargestChar, &args);
        pthread_join(newthread[i%NUM_THREADS], NULL);
    }
    fclose( f );

    gettimefday(&end, NULL);



    // Still have to print the time it took to rad the file. - Tyler


    pthread_mutext_destroy(&mutexTotal, NULL);


}

