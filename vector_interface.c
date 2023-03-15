#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(){
    printf("Si programa leidzia kurti vektoriu.\n");
    char option = ' ';
    Vector *vec[3] = {NULL};
    int error_code = 0;
    char *errors[] = {"", "Perzengti vektoriaus didzio reziai." , "Vektorius dar nesukurtas.", "Vektorius su tokiu id neegzistuoja."};
    while(option != '0'){
        error_code = 0;
        printf("Dabartine vektoriu busena: ");
        if(vec[0] != NULL || vec[1] != NULL || vec[2] != NULL){
            for(int i = 0; i < 3 && vec[i] != NULL; i++){
                printf("vektorius #%d - ", vec[i]->id);
                print_vector(vec[i], &error_code);
                printf(", ");
            }
            printf("\n");
        }
        else{
            printf("Nera sukurtas nei vienas vektorius.\n");
        }
        printf("Operacijos su vektoriumi: \n");
        printf("    1 - Sukurti vektoriu.\n");
        printf("    2 - Prideti elementa i gala.\n");
        printf("    3 - Prideti elementa i nurodyta pozicija.\n");
        printf("    4 - Istrinti elementa nurodytoje pozicijoje.\n");
        printf("    5 - Pakeisti elementa nurodytoje pozicijoje.\n");
        printf("    6 - Gauti elementa nurodytoje pozicijoje.\n");
        printf("    7 - Paziureti, ar vektorius tuscias.\n");
        printf("    8 - Gauti vektoriaus elementu skaiciu.\n");
        printf("    9 - Sunaikinti vektoriu.\n");
        printf("    0 - Baigti darba.\n");
        scanf("%1s", &option);
        fflush(stdin);
        if(option == '1'){
            // 0 - Sukurti vektoriu
            int id = 0;
            while(1){
                char term;
                printf("Iveskite kuriamo vektoriaus id: \n");
                int check = scanf("%d%c", &id, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            char id_exists = 0;
            char array_index = -1;
            for(int i = 0; i < 3; i++){
                if(array_index == -1 && vec[i] == NULL)
                    array_index = i;
                if(vec[i] != NULL && vec[i]->id == id)
                    id_exists = 1;
            }
            if(array_index == -1){
                printf("Vektorius nesukurtas, nes vektoriu limitas (3) jau pasiektas.\n");
            }
            else if(id_exists){
                printf("Vektorius nesukurtas, nes vektorius su tokiu id jau egzistuoja.\n");
            }
            else{
                vec[array_index] = create_vector(id);
                printf("Vektorius sukurtas sekmingai.\n");
            }
            
        }
        else if(option == '2'){
            // 1 - Prideti elementa i gala.
            int element = 0;
            char term;
            int id = 0;
            int index = -1;
            while(1){
                printf("Iveskite vektoriaus, su kuriuo norite atlikti operacija, id: \n");
                int check = scanf("%d%c", &id, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            for(int i = 0; i < 3; i++){
                if(vec[i] != NULL && vec[i]->id == id)
                    index = i;
            }
            if(index == -1){
                printf("Klaida #3. %s\n", errors[3]);
                continue;
            }
            while(1){
                printf("Iveskite elementa (skaiciu): \n");
                int check = scanf("%d%c", &element, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }

            
            add_element(vec[index], element, &error_code);
            if(error_code == 2){
                printf("Klaida #2. %s\n", errors[2]);
            }
            else{
                printf("Elementas sekmingai pridetas i vektoriaus gala.\n");
            }
        }
        else if(option == '3'){
            // 2 - Prideti elementa i nurodyta pozicija.
            int element = 0;
            int position = 0;
            char term = 0;
            int id = 0;
            int index = -1;
            while(1){
                printf("Iveskite vektoriaus, su kuriuo norite atlikti operacija, id: \n");
                int check = scanf("%d%c", &id, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            for(int i = 0; i < 3; i++){
                if(vec[i] != NULL && vec[i]->id == id)
                    index = i;
            }
            if(index == -1){
                printf("Klaida #3. %s\n", errors[3]);
                continue;
            }
            while(1){
                printf("Iveskite elementa (skaiciu): \n");
                int check = scanf("%d%c", &element, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            while(1){
                printf("Iveskite pozicija i kuria ideti elementa: \n");
                int check = scanf("%d%c", &position, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            insert_element_at(vec[index], element, position-1, &error_code);
            if(error_code == 2){
                printf("Klaida #2. %s\n", errors[2]);
            }
            else if(error_code == 1){
                printf("Klaida #1. %s [1, %d]\n", errors[1], vec[index]->size+1);
            }
            else{
                printf("Elementas sekmingai pridetas i %d pozicija.\n", position);
            }
        }
        else if(option == '4'){
            // 3 - Istrinti elementa nurodytoje pozicijoje.
            int position = 0;
            char term = 0;
            int id = 0;
            int index = -1;
            while(1){
                printf("Iveskite vektoriaus, su kuriuo norite atlikti operacija, id: \n");
                int check = scanf("%d%c", &id, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            for(int i = 0; i < 3; i++){
                if(vec[i] != NULL && vec[i]->id == id)
                    index = i;
            }
            if(index == -1){
                printf("Klaida #3. %s\n", errors[3]);
                continue;
            }
            while(1){
                printf("Iveskite pozicija elemento, kuri norite istrinti: \n");
                int check = scanf("%d%c", &position, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            remove_element_at(vec[index], position-1, &error_code);
            if(error_code == 2){
                printf("Klaida #2. %s\n", errors[2]);
            }
            else if(error_code == 1){
                printf("Klaida #1. %s [1, %d]\n", errors[1], vec[index]->size);
            }
            else{
                printf("Elementas sekmingai istrintas is %d pozicijos.\n", position);
            }
        }
        
        else if(option == '5'){
            // 4 - Pakeisti elementa nurodytoje pozicijoje.
            int element = 0;
            int position = 0;
            char term = 0;
            int id = 0;
            int index = -1;
            while(1){
                printf("Iveskite vektoriaus, su kuriuo norite atlikti operacija, id: \n");
                int check = scanf("%d%c", &id, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            for(int i = 0; i < 3; i++){
                if(vec[i] != NULL && vec[i]->id == id)
                    index = i;
            }
            if(index == -1){
                printf("Klaida #3. %s\n", errors[3]);
                continue;
            }
            while(1){
                printf("Iveskite pozicija elemento, kuri norite pakeisti: \n");
                int check = scanf("%d%c", &position, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            while(1){
                printf("Iveskite nauja elemento reiksme: \n");
                int check = scanf("%d%c", &element, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            set_element_at(vec[index], element, position-1, &error_code);
            if(error_code == 2){
                printf("Klaida #2. %s\n", errors[2]);
            }
            else if(error_code == 1){
                printf("Klaida #1. %s [1, %d]\n", errors[1], vec[index]->size);
            }
            else{
                printf("Elementas pozicijoje %d sekmingai pakeistas.\n", position);
            }
        }
        else if(option == '6'){
            // 5 - Gauti elementa nurodytoje pozicijoje.
            int position = 0;
            char term = 0;
            int id = 0;
            int index = -1;
            while(1){
                printf("Iveskite vektoriaus, su kuriuo norite atlikti operacija, id: \n");
                int check = scanf("%d%c", &id, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            for(int i = 0; i < 3; i++){
                if(vec[i] != NULL && vec[i]->id == id)
                    index = i;
            }
            if(index == -1){
                printf("Klaida #2. %s\n", errors[2]);
                continue;
            }
            while(1){
                printf("Iveskite pozicija elemento, kuri norite gauti: \n");
                int check = scanf("%d%c", &position, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            int value = get_element_at(vec[index], position-1, &error_code);
            if(error_code == 2){
                printf("Klaida #2. %s\n", errors[2]);
            }
            else if(error_code == 1){
                printf("Klaida #1. %s [1, %d]\n", errors[1], vec[index]->size);
            }
            else{
                printf("Elementas %d pozicijoje yra lygus %d.\n", position, value);
            }
        }
        else if(option == '7'){
            // 6 - Paziureti ar vektorius tuscias.
            int id = 0;
            int index = -1;
            char term;
            while(1){
                printf("Iveskite vektoriaus, su kuriuo norite atlikti operacija, id: \n");
                int check = scanf("%d%c", &id, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            for(int i = 0; i < 3; i++){
                if(vec[i] != NULL && vec[i]->id == id)
                    index = i;
            }
            if(index == -1){
                printf("Klaida #3. %s\n", errors[3]);
                continue;
            }
            char value = is_empty(vec[index], &error_code);
            if(error_code == 2){
                printf("Klaida #2. %s\n", errors[2]);
            }else{
                printf("Vektorius %s tuscias.\n", value == 1 ? "yra": "nera");
            }
        }
        else if(option == '8'){
            // 7 - Gauti vektoriaus elementu skaiciu.
            int id = 0;
            int index = -1;
            char term;
            while(1){
                printf("Iveskite vektoriaus, su kuriuo norite atlikti operacija, id: \n");
                int check = scanf("%d%c", &id, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            for(int i = 0; i < 3; i++){
                if(vec[i] != NULL && vec[i]->id == id)
                    index = i;
            }
            if(index == -1){
                printf("Klaida #3. %s\n", errors[3]);
                continue;
            }
            int value = get_size(vec[index], &error_code);
            if(error_code == 2){
                printf("Klaida #2. %s\n", errors[2]);
            }else{
                printf("Vektoriaus dydis: %d\n", value);
            }

        }
        else if(option == '9'){
            // 8 - Sunaikinti vektoriu.
            int id = 0;
            int index = -1;
            char term;
            while(1){
                printf("Iveskite vektoriaus, su kuriuo norite atlikti operacija, id: \n");
                int check = scanf("%d%c", &id, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            for(int i = 0; i < 3; i++){
                if(vec[i] != NULL && vec[i]->id == id)
                    index = i;
            }
            if(index == -1){
                printf("Klaida #3. %s\n", errors[3]);
                continue;
            }
            delete_vector(&(vec[index]), &error_code);
            if(error_code == 2){
                printf("Klaida #2. %s\n", errors[2]);
            }else{
                printf("Vektorius sekmingai istrintas.\n");
                for(int i = index; i < 2; i++){
                    vec[i] = vec[i+1];
                    vec[i+1] = NULL;
                }
            }
        }
        else if(option != '0'){
            printf("Neteisingas veiksmo kodas. Bandykite dar karta.\n");
        }
    }
}