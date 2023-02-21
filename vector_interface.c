#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(){
    printf("Si programa leidzia kurti vektoriu.\n");
    char option = ' ';
    Vector *vec = NULL;
    int error_code = 0;
    while(option != '9'){
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
            if(vec != NULL)
                delete_vector(vec, &error_code);
            vec = create_vector();
            printf("Vektorius sukurtas sekmingai.\n");
        }
        else if(option == '1'){
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
            
        }
        else if(option == '3'){
            
        }
        else if(option == '4'){
            
        }
        else if(option == '5'){
            
        }
        else if(option == '6'){
            
        }
        else if(option == '7'){
            
        }
        else if(option == '8'){
            
        }
        else{
            printf("Neteisingas veiksmo kodas. Bandykite dar karta.\n");
        }
    }
    
    
}