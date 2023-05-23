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
    //srand(time(NULL));
    PriorityQueue *planes = NULL;

    fin = fopen("duomenys.txt", "r");
    fout = fopen("protokolas.txt", "w");

    fprintf(fout, "3 uzduotis, 4 variantas. Antanas Vasiliauskas 3 grupe, 2 pogrupis.\n\n");
    char *strbfr1 =
    "SALYGA\n"
    "----------------------------------------------------------------------------------\n"
    "Aerouostas (ADT: prioritetinė eilė, ilgas sveikas skaičius).\n" 
    "Aerouostas turi 1 pakilimo/nusileidimo taką.\n"
    "Besileidžiantys lėktuvai turi prioritetą.\n"
    "T. y., jei takas laisvas, tai pirmiausia priimamas besileidžiantis lėktuvas.\n"
    "Jei kažkuris lėktuvas pradėjo pakilimą/nusileidimą, tai visi lėktuvai turi laukti.\n"
    "Lėktuvas, norintis nusileisti, negali laukti labai ilgai, nes jam baigsis degalai.\n"
    "Patyrinėti prie kokio apkrovimo aerouostui pakanka vieno tako.\n"
    "PRADINIAI DUOMENYS:\n"
    "1) Nusileidimo trukmė.\n"
    "2) Pakilimo trukmė.\n"
    "3) Trukmė kurį lėktuvas dar gali išbūti ore.\n" 
    "4) Tikimybė, kad einamuoju momentu atsiras naujas lėktuvas norintis kilti arba leistis P.\n"
    "5) Tikimybė, kad atsiradęs naujas lėktuvas norės leistis p1.\n"
    "6) Tikimybė, kad atsiradęs naujas lėktuvas norės kilti p2. (Pastaba: p1 + p2 = 100%%)\n"
    "REZULTATAI:\n"
    "1) Modeliavimas baigiamas, kai nukrinta lėktuvas.\n"
    "2) Maksimali norinčio nusileisti lėktuvo laukimo trukmė.\n"
    "3) Vidutinė norinčio nusileisti lėktuvo laukimo trukmė.\n"
    "4) Maksimali norinčio pakilti lėktuvo laukimo trukmė.\n"
    "5) Vidutinė norinčio pakilti lėktuvo laukimo trukmė.\n"
    "----------------------------------------------------------------------------------\n\n\n";

    fprintf(fout, strbfr1);

    
    // Data
    int up_time;
    int down_time;
    int maximum_wait_time;
    double probability;
    double probability_up;
    double probability_down;

    // Read data
    fscanf(fin, "%d%d%d%lf%lf%lf", &up_time, &down_time, &maximum_wait_time, &probability, &probability_up, &probability_down);

        
    
    fwrite("I DALIS - DUOMENYS\n\n", 1, strlen("I DALIS - DUOMENYS\n\n"), fout);
    fprintf(fout, "%-70s %-d min.\n", "1) Nusileidimo trukmė:", down_time);
    fprintf(fout, "%-70s %-d min.\n", "2) Pakilimo trukmė:" , up_time);
    fprintf(fout, "%-70s %-d min.\n", "3) Trukmė kurį lėktuvas dar gali išbūti ore:", maximum_wait_time);
    fprintf(fout, "%-70s %.0lf %%.\n", "4) Tikimybė, kad atsiras lėktuvas norintis kilti arba leistis P:", probability*100);
    fprintf(fout, "%-70s %.0lf %%.\n", "5) Tikimybė, kad atsiradęs lėktuvas norės leistis p1:", probability_down*100);
    fprintf(fout, "%-70s %.0lf %%.\n\n","6) Tikimybė, kad atsiradęs lėktuvas norės kilti p2:", probability_up*100);


    
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
   
   for(int t = 0; t < 100; t++){

    fprintf(fout ,"T=%d min.\n", t);

    if(current_id != -1 && current_left > 1){
        fprintf(fout, "    VEIKSMAS%02d: ", t);
        fprintf(fout, "Lėktuvas L%d jau %s %d min. Jam liko %s %d min.\n", current_id, current_priority == 0 ? "leidosi" : "kilo", current_priority == 0 ? down_time - current_left + 1 : up_time - current_left + 1, current_priority == 0 ? "leistis" : "kilti", current_left-1);
    }
    if(current_left == 1){
        fprintf(fout, "    VEIKSMAS%02d: ", t);
        fprintf(fout, "Lėktuvas L%d %s\n", current_id, current_priority == 0 ? "nusileido." : "pakilo.");
    }

    fprintf(fout, "    BUSENA%02d:   ", t);
    // 1.
    if(probability_check(probability)){
        int priority = probability_check(probability_up) == true ? 1 : 0;
        if(planes == NULL){
            planes = create(0, priority, ++total_count);
        }
        else{
            push(&planes, 0, priority, ++total_count);
        }
        fprintf(fout, "Lėktuvas L%d užsinori %s", total_count, priority == 0 ? "leistis. " : "kilti. ");
    }

        




    




        // 2.

        current_left--;
        
        

        // Initialization after there were 0 elements 
        if(current_id == -1 && planes != NULL){
            current_id = planes->id;
            current_priority = planes->priority;
            if(planes->priority == 0){
                current_left = down_time;
                fprintf(fout, "Lėktuvas L%d gauna leidimą leistis.\n", current_id);
            }   
            else{
                current_left = up_time;
                fprintf(fout, "Lėktuvas L%d gauna leidimą kilti.\n", current_id);
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
                fprintf(fout, "Lėktuvas L%d gauna leidimą leistis.\n", current_id);
                    current_left = down_time;
                }
                else{
                fprintf(fout, "Lėktuvas L%d gauna leidimą kilti.\n", current_id);
                    current_left = up_time;
                }
            }
            else{
                fprintf(fout, "\n");
                current_id = -1;
                current_priority = -1;
            }

        }
        else fprintf(fout, "\n");
        PriorityQueue *tmp_planes = planes;
        fprintf(fout, "    Lėktuvų, norinčių leistis, eilė: ");
        char is_empty = 1;
        while(tmp_planes != NULL){
            if(tmp_planes->priority == 0 && tmp_planes->id != current_id){
                fprintf(fout, "L%d%s", tmp_planes->id, tmp_planes->next == NULL ? ".": tmp_planes->next->priority == 1 ? "." : ", ");
                is_empty = 0;
            }
            tmp_planes = tmp_planes->next;
        }
        if(is_empty) fprintf(fout, "-.");

        is_empty = 1;
        tmp_planes = planes;
        
        fprintf(fout, "\n    Lėktuvų, norinčių kilti, eilė: ");
        while(tmp_planes != NULL){
            if(tmp_planes->priority == 1 && tmp_planes->id != current_id){
                fprintf(fout, "L%d%s", tmp_planes->id, tmp_planes->next == NULL ? ".": ", ");
                is_empty = 0;
            }
            tmp_planes = tmp_planes->next;
        }
        if(is_empty) fprintf(fout, "-.");
        fprintf(fout, "\n");        
        

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
    if(crashed_plane_id != 0){
        fprintf(fout, "    Lėktuvui L%d baigėsi degalai.\n    Lėktuvas L%d sudužo.\n\n", crashed_plane_id, crashed_plane_id);
    }

    fprintf(fout, "III DALIS - REZULTATAI\n\n");

    if(crashed_plane_id != 0){
        fprintf(fout, "1) Sudužo L%d lėktuvas.\n", crashed_plane_id);
    }
    else{
        fprintf(fout, "1) Joks lėktuvas nesudužo.\n");
    }
    fprintf(fout, "2) Maksimali norinčio nusileisti lėktuvo laukimo trukmė: %-5d min.\n", max_down_wait_time);
    fprintf(fout, "3) Vidutinė norinčio nusileisti lėktuvo laukimo trukmė:  %-5.2lf min.\n", down_average_wait_time);
    fprintf(fout, "4) Maksimali norinčio pakilti lėktuvo laukimo trukmė:    %-5d min.\n", max_up_wait_time);
    fprintf(fout, "5) Vidutinė norinčio pakilti lėktuvo laukimo trukmė:     %-5.2lf min.\n", up_average_wait_time);
    fclose(fin);
    fclose(fout);
}
