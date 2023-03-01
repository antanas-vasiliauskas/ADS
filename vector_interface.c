#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(){
    printf("Si programa leidzia kurti vektoriu.\n");
    char option = ' ';
    Vector *vec[1000] = {NULL};
    int error_code = 0;
    while(option != '9'){
        error_code = 0;
        printf("Dabartine vektoriaus busena: ");
        if(vec != NULL){    
            print_vector(vec, &error_code);
        }
        else{
            printf("Vektorius neegzistuoja.\n");
        }
        printf("Pasirinkite veiksma: \n");
        printf("    0 - Sukurti vektoriu.\n");
        printf("    1 - Prideti elementa i gala.\n");
        printf("    2 - Prideti elementa i nurodyta pozicija.\n");
        printf("    3 - Istrinti elementa nurodytoje pozicijoje.\n");
        printf("    4 - Pakeisti elementa nurodytoje pozicijoje.\n");
        printf("    5 - Gauti elementa nurodytoje pozicijoje.\n");
        printf("    6 - Paziureti ar vektorius tuscias.\n");
        printf("    7 - Gauti vektoriaus elementu skaiciu.\n");
        printf("    8 - Sunaikinti vektoriu.\n");
        printf("    9 - Baigti darba.\n");
        scanf("%1s", &option);
        fflush(stdin);
        if(option == '0'){
            // 0 - Sukurti vektoriu
            if(vec != NULL)
                delete_vector(&vec, &error_code);
            vec = create_vector();
            printf("Vektorius sukurtas sekmingai.\n");
        }
        else if(option == '1'){
            // 1 - Prideti elementa i gala.
            int element = 0;
            char term;
            while(1){
                printf("Iveskite elementa (skaiciu): \n");
                int check = scanf("%d%c", &element, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            add_element(vec, element, &error_code);
            if(error_code == 2){
                printf("Klaida!. Vektorius dar nesukurtas.\n");
            }
            else{
                printf("Elementas sekmingai pridetas i vektoriaus gala.\n");
            }
        }
        else if(option == '2'){
            // 2 - Prideti elementa i nurodyta pozicija.
            int element = 0;
            int position = 0;
            char term = 0;
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
            insert_element_at(vec, element, position, &error_code);
            if(error_code == 2){
                printf("Klaida! Vektorius dar nesukurtas.\n");
            }
            else if(error_code == 1){
                printf("Klaida! Perzengti vektoriaus didzio reziai [0, %d]\n", vec->size);
            }
            else{
                printf("Elementas sekmingai pridetas i %d pozicija.\n", position);
            }
        }
        else if(option == '3'){
            // 3 - Istrinti elementa nurodytoje pozicijoje.
            int position = 0;
            char term = 0;
            while(1){
                printf("Iveskite pozicija elemento, kuri norite istrinti: \n");
                int check = scanf("%d%c", &position, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            remove_element_at(vec, position, &error_code);
            if(error_code == 2){
                printf("Klaida! Vektorius dar nesukurtas.\n");
            }
            else if(error_code == 1){
                printf("Klaida! Perzengti vektoriaus didzio reziai [0, %d]\n", vec->size);
            }
            else{
                printf("Elementas sekmingai istrintas is %d pozicijos.\n", position);
            }
        }
        
        else if(option == '4'){
            // 4 - Pakeisti elementa nurodytoje pozicijoje.
            int element = 0;
            int position = 0;
            char term = 0;
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
            set_element_at(vec, element, position, &error_code);
            if(error_code == 2){
                printf("Klaida! Vektorius dar nesukurtas.\n");
            }
            else if(error_code == 1){
                printf("Klaida! Perzengti vektoriaus didzio reziai [0, %d]\n", vec->size-1);
            }
            else{
                printf("Elementas pozicijoje %d sekmingai pakeistas.\n", position);
            }
        }
        else if(option == '5'){
            // 5 - Gauti elementa nurodytoje pozicijoje.
            int position = 0;
            char term = 0;
            while(1){
                printf("Iveskite pozicija elemento, kuri norite gauti: \n");
                int check = scanf("%d%c", &position, &term);
                if(check != 2 || term != '\n')
                    printf("Ivestas neskaicius. Bandykite dar karta.\n");
                else
                    break;
                fflush(stdin);
            }
            int value = get_element_at(vec, position, &error_code);
            if(error_code == 2){
                printf("Klaida! Vektorius dar nesukurtas.\n");
            }
            else if(error_code == 1){
                printf("Klaida! Perzengti vektoriaus didzio reziai [0, %d]\n", vec->size);
            }
            else{
                printf("Elementas %d pozicijoje yra lygus %d.\n", position, value);
            }
        }
        else if(option == '6'){
            // 6 - Paziureti ar vektorius tuscias.
            char value = is_empty(vec, &error_code);
            if(error_code == 2){
                printf("Klaida! Vektorius dar nesukurtas.\n");
            }else{
                printf("Vektorius %s tuscias.\n", value == 1 ? "yra": "nera");
            }
        }
        else if(option == '7'){
            // 7 - Gauti vektoriaus elementu skaiciu.
            int value = get_size(vec, &error_code);
            if(error_code == 2){
                printf("Klaida! Vektorius dar nesukurtas.\n");
            }else{
                printf("Vektoriaus dydis: %d\n", value);
            }

        }
        else if(option == '8'){
            // 8 - Sunaikinti vektoriu.
            delete_vector(&vec, &error_code);
            if(error_code == 2){
                printf("Klaida! Vektorius dar nesukurtas.\n");
            }else{
                printf("Vektorius sekmingai istrintas.\n");
            }
        }
        else if(option != '9'){
            printf("Neteisingas veiksmo kodas. Bandykite dar karta.\n");
        }
    }
}