#include <stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define NUM_THREADS 15
struct thread_data{
   int  thread_id;
   int  sum;
   char *message;
};

struct thread_data thread_data_array[NUM_THREADS];

void *PrintHello(void *threadarg)
{
    int taskid, sum;
    char *hello_msg;
   struct thread_data *my_data;
   my_data = (struct thread_data *) threadarg;
   taskid = my_data->thread_id;
   sum = my_data->sum;
   printf("\n I got %d   %d   ", taskid, sum);
}

int main (int argc, char *argv[])
{
    int t, sum= 100, rc;
    char messages[15];
    pthread_t threads[15];
    
    for(t=0;t<15;t++)
    {
        messages[t] = 65+'a';
        thread_data_array[t].thread_id = t;
        thread_data_array[t].sum = sum;
        //printf("\n Created %d\t %d", thread_data_array[t].thread_id, thread_data_array[t].sum);
        //thread_data_array[t].message = messages[t];
        rc = pthread_create(&threads[t], NULL, PrintHello, 
             (void *) &thread_data_array[t]);
        if(rc)
        {
            printf("\n Error");
            exit(-1);
        }
    }
    pthread_exit(NULL);
    return 0;
}
