#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "BigInteger.c"
#include "PriorityQueue.c"
#include "BigInteger.h"


FILE *fin;
FILE *fout;

// Given the probaility of event, generates a random outcome. If event happens, returns true, else false.
bool probability_check(double probability){
    if(probability * RAND_MAX > rand())
        return true;
    return false;
}


int main(){
    srand(time(NULL));
    PriorityQueue *planes = NULL;

    fin = fopen("duomenys.txt", "r");
    fout = fopen("protokolas.txt", "w");

    fprintf(fout, "Antanas Vasiliauskas 3 grupe, 2 pogrupis, 3 uzduotis, 4 variantas.\n\n");
    char *strbfr1 =
    "SALYGA\n" 
    "------------------------------------------------------------------------------\n"
    "Aerouostas (ADT: prioritetinė eilė, ilgas sveikas skaičius). Aerouostas turi 1\n"
    "pakilimo/nusileidimo taką, besileidžiantys lėktuvai turi prioritetą, t.y. jei\n"
    "takas laisvas, tai pirmiausia priimamas besileidžiantis lėktuvas, bet jei\n"
    "kažkuris lėktuvas pradėjo pakilimą, tai visi kiti, tame tarpe ir norintys\n"
    "nusileist, lėktuvai turi laukti; lėktuvas, norintis nusileisti, negali laukti\n"
    "labai ilgai, nes jam baigsis degalai. Tikslas: patyrinėti prie kokio apkrovimo\n"
    "aerouostui pakanka vieno tako. Pradiniai duomenys: nusileidimo laikas (trukmė),\n"
    "pakilimo laikas, kurį norintis leistis lėktuvas, dar gali išbūti ore, lėktuvo\n"
    "panorusio kilti/leistis einamuoju momentu tikimybė (galima realizacija: generuojamas\n"
    "atsitiktinis skaičius ir tikrinama, ar jis tenkina tam tikrą sąlygą), besileidžiantys\n"
    "ir kylantys lėktuvai pasirodo su vienoda tikimybe. Rezultatai: nukritęs lėktuvas\n"
    "(modeliavimas iš karto beigiamas), maksimalus ir vidutinis norinčio nusileisti\n"
    "lėktuvo laukimo laikas, maksimalus ir vidutinis norinčio pakilti lėktuvo laukimo laikas.\n"
    "------------------------------------------------------------------------------\n\n";
    fprintf(fout, strbfr1);

    
    // Data
    int up_time;
    int down_time;
    int maximum_wait_time;
    double probability;

    // Read data
    fscanf(fin, "%d%d%d%lf", &up_time, &down_time, &maximum_wait_time, &probability);

        
    
    fwrite("I DALIS - DUOMENYS\n\n", 1, strlen("I DALIS - DUOMENYS\n\n"), fout);
    fprintf(fout, "Nusileidimo laikas: %d\n", down_time);
    fprintf(fout, "Pakilimo laikas: %d\n", up_time);
    fprintf(fout, "Laikas, kuri lektuvas dar gali isbuti ore: %d\n", maximum_wait_time);
    fprintf(fout, "Tikimybe, kad bet kuriuo laiko momentu pasirodys lektuvas: %.2lf%%\n\n", probability*100);


    
    // Results
    int crashed_plane_id = 0;
    int max_up_wait_time = 0;
    int max_down_wait_time = 0;

    int current_id = -1;
    int current_priority = -1;
    int current_left = -1;
    int total_count = 0;
    BigInteger total_time_up = bigIntegerCreateFromString("0");
    BigInteger total_time_down = createBigInteger("0");
    double up_average_wait_time = 0;
    double down_average_wait_time = 0;
    int up_count = 0;
    int down_count = 0;
    
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

   fprintf(fout, "II DALIS - VYKDYMAS\n\n");
   
   for(int t = 0; t < 1000 ; t++){

    fprintf(fout ,"Momentas T=%d.\n", t);

        // 1.
        if(probability_check(probability)){
            int priority = rand() % 2;
            if(planes == NULL){
                planes = create(0, priority, ++total_count);
            }
            else{
                push(&planes, 0, priority, ++total_count);
            }
            fprintf(fout, "              Naujas lektuvas %d nori %s\n", total_count, priority == 0 ? "leistis." : "kilti.");
        }

    

        PriorityQueue *tmp_planes = planes;
        fprintf(fout, "              Leisis lektuvai: ");
        char is_empty = 1;
        while(tmp_planes != NULL){
            if(tmp_planes->priority == 0){
                fprintf(fout, "%d%s", tmp_planes->id, tmp_planes->next == NULL ? ".": tmp_planes->next->priority == 1 ? "." : ", ");
                is_empty = 0;
            }
            tmp_planes = tmp_planes->next;
        }
        if(is_empty) fprintf(fout, "-");

        is_empty = 1;
        tmp_planes = planes;
        
        fprintf(fout, "\n              Kils lektuvai: ");
        while(tmp_planes != NULL){
            if(tmp_planes->priority == 1){
                fprintf(fout, "%d%s", tmp_planes->id, tmp_planes->next == NULL ? ".": ", ");
                is_empty = 0;
            }
            tmp_planes = tmp_planes->next;
        }
        if(is_empty) fprintf(fout, "-");
        fprintf(fout, "\n");


        // 2.

        current_left--;
        
        // Initialization after there were 0 elements 
        if(current_id == -1 && planes != NULL){
            current_id = planes->id;
            current_priority = planes->priority;
            if(planes->priority == 0){
                current_left = down_time;
                fprintf(fout, "              Pradeda leidimasi lektuvas %d.\n", current_id);
            }
                
            else{
                current_left = up_time;
                fprintf(fout, "              Pradeda kilima lektuvas %d.\n", current_id);
            }
                
        }
        else if(current_left <= 0 && planes != NULL){
            PriorityQueue *current_plane = planes;
            while(current_plane->id != current_id){
                current_plane = current_plane->next;
            }
            if(current_plane->priority == 0){
                // going down
                if(current_plane->data > max_down_wait_time)
                    max_down_wait_time = current_plane->data;
                down_average_wait_time += (current_plane->data - down_average_wait_time) / (++down_count);
            }

            else {
                // going up
                if(current_plane->data > max_up_wait_time)
                    max_up_wait_time = current_plane->data;
                up_average_wait_time += (current_plane->data - up_average_wait_time) / (++up_count);
            }
            fprintf(fout, "              Lektuvas %d %s\n", current_id, current_priority == 0 ? "nusileido." : "pakilo.");
            if(planes->id == current_id){
                pop(&planes);
            }
            else{
                PriorityQueue *previous = planes;
                PriorityQueue *tmp = planes->next;
                while(tmp != NULL){
                    if(tmp->id == current_id){
                        previous->next = tmp->next;
                        break;
                    }
                    previous = tmp;
                    tmp = tmp->next;
                }
            }
            
            
            if(planes != NULL){
                current_id = planes->id;
                current_priority = planes->priority;
                if(current_priority == 0){
                    fprintf(fout, "              Pradeda leidimasi lektuvas %d.\n", current_id);
                    current_left = down_time;
                }
                else{
                    fprintf(fout, "              Pradeda kilima lektuvas %d.\n", current_id);
                    current_left = up_time;
                }
            }
            else{
                current_id = -1;
                current_priority = -1;
            }

        }else{
            if(current_id != -1){
                fprintf(fout, "              Lektuvas %d vis dar %s.\n", current_id, current_priority == 0 ? "leidziasi" : "kyla");
            }
        }
        
        

        // 3.
        
        tmp_planes = planes;
        while(tmp_planes != NULL){
            tmp_planes->data++;
            if(tmp_planes->data >= maximum_wait_time && tmp_planes->priority == 0){
                // 4. Crash
                crashed_plane_id = current_id;
                goto CrashCase;
            }
            tmp_planes = tmp_planes->next;
        }
        fprintf(fout, "\n");
   }
   CrashCase:
    ;
    fprintf(fout, "              Lektuvui %d baigesi degalai.\n              Lektuvas %d suduzo.\n\n", crashed_plane_id, crashed_plane_id);

    fprintf(fout, "III DALIS - REZULTATAI\n\n");

    fprintf(fout, "Suduzes lektuvas: %d\n", crashed_plane_id);
    fprintf(fout, "Maksimalus nusileisti norincio lektuvo laukimo laikas: %d\n", max_down_wait_time);
    fprintf(fout, "Vidutinis nusileisti norincio lektuvo laukimo laikas: %.2lf\n", down_average_wait_time);
    fprintf(fout, "Maksimalus pakilti norincio lektuvo laikas: %d\n", max_up_wait_time);
    fprintf(fout, "Vidutinis pakilti norincio lektuvo laikas: %.2lf\n", up_average_wait_time);
    fclose(fin);
    fclose(fout);
}
