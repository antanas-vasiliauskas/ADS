#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "BigInteger.c"
#include "PriorityQueue.c"
#include "BigInteger.h"


// Given the probaility of event, generates a random outcome. If event happens, returns true, else false.
bool probability_check(double probability){    
    if(probability * RAND_MAX > rand())
        return true;
    
    return false;
     
}


int main(){
    srand(time(NULL));
    PriorityQueue *planes = NULL;
    
    // Data
    long long operation_time = 5;
    long long maximum_wait_time = 10;
    double probability = 0.5;

    // simulation runs until the plane crashes.
    
    // Results
    int crashed_plane_id = 0;
    long long max_up_wait_time = 0;
    long long average_up_wait_time = 0;
    long long max_down_wait_time = 0;
    long long average_down_wait_time = 0;

    int current_id = -1;
    long long current_left = -1;
    int total_count = 0;
    BigInteger total_time_up = bigIntegerCreateFromString("0");
    BigInteger total_time_down = createBigInteger("0");
    
    /*
    Time loop:
        1. Probability check to add new plane to the queue.
        2. Check if it is rotation for new plane. If so:
            2.1. Remove old from queue
            2.2. Update max time if needed.
            2.3. Add total time as Big Integer (sprintf long long and create Big Integer from string)  
            2.4. Change current id
        3. Increment time for every plane in queue.
        4. Check if any crashed. 
    */
   
   for(int t = 0; t<1000 ; t++){
   
        // 1.
        if(probability_check(probability)){
            if(planes == NULL){
                planes = create(0, rand() % 2, ++total_count);
            }
            else{
                push(&planes, 0, rand() % 2, ++total_count);
            }
            printf("Plane %d added\n", total_count);
        }
        // 2.

        current_left--;
        
        // Initialization after there were 0 elements 
        if(current_id == -1 && planes != NULL){
            current_id = planes->id;
            current_left = operation_time;
        }

        if(current_left <= 0 && planes != NULL){
            char tmp[50] = {0};
            sprintf(tmp, "%lld", planes->data);
            BigInteger bi = bigIntegerCreateFromString(tmp);

            if(planes->priority == 0){
                // going down
                if(planes->data > max_down_wait_time)
                    max_down_wait_time = planes->data;
                total_time_down = bigIntegerAdd(total_time_down, bi);
            }

            else {
                // going up
                if(planes->data > max_up_wait_time)
                    max_up_wait_time = planes->data;
                total_time_up = bigIntegerAdd(total_time_up, bi);
            }
            printf("Plane %d removed\n", planes->id);
            pop(&planes);
            if(planes != NULL)
                current_id = planes->id;
            else
                current_id = -1;
        }
        
        

        // 3.
        PriorityQueue *tmp_planes = planes;
        while(tmp_planes != NULL){
            tmp_planes->data++;
            if(tmp_planes->data >= operation_time && tmp_planes->priority == 0){
                // 4. Crash
                crashed_plane_id = current_id;
                goto CrashCase;
            }
            tmp_planes = tmp_planes->next;
        }
   }
   CrashCase:
    ;

    printf("Crashed Id: %d\nMax Up Time: %lld\nMax Down Time: %lld\nTotal Up Time: %s\nTotal Down Time: %s\n" ,crashed_plane_id, max_up_wait_time, max_down_wait_time, total_time_up->str, total_time_down->str);
}