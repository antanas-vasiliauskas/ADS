#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// PATIKRINTI AR DUOTI TRYS TASKAI, TRIKAMPIO VIRSUNES, YRA STATUS TRIKAMPIS

int main(){
    double x[3] = {0,0,0}, y[3] = {0,0,0};
    printf("Si programa nurodo ar try taskai is jusu ivestu koordinaciu sudaro statu trikampi.\n");
    
    for(int i = 0; i < 3; i++){
        while(1){
            char *msg = i == 0 ? "pirmo" : i == 1 ? "antro" : "trecio";
            char tmp;
            printf("Iveskite %s tasko koordinates x reiksme ir spauskite ENTER:\n", msg);
            int a = scanf("%lf%c", &x[i], &tmp);

            if(a != 2 || tmp != '\n'){
                printf("Ivestis neteisinga. Bandykite dar karta.\n");
                fflush(stdin);
                continue;
            }
            break;
        }
        while(1){
            char *msg = i == 0 ? "pirmo" : i == 1 ? "antro" : "trecio";
            char tmp;
            printf("Iveskite %s tasko koordinates y reiksme ir spauskite ENTER:\n", msg);
            int a = scanf("%lf%c", &y[i], &tmp);
            if(a != 2 || tmp != '\n'){
                printf("Ivestis neteisinga. Bandykite dar karta.\n");
                fflush(stdin);
                continue;
            }

            break;
        }
    }

    double len[3] = {0,0,0};
    len[0] = sqrt(pow(x[0] - x[1], 2) + pow(y[0] - y[1], 2));
    len[1] = sqrt(pow(x[1] - x[2], 2) + pow(y[1] - y[2], 2));
    len[2] = sqrt(pow(x[2] - x[0], 2) + pow(y[2] - y[0], 2));
    
    if(len[1] >= len[0] && len[1] >= len[2]){
        double tmp = len[0];
        len[0] = len[1];
        len[1] = tmp;
    }
    else if(len[2] >= len[0] && len[2] >= len[1]){
        double tmp = len[0];
        len[0] = len[2];
        len[2] = tmp;
    }

    char sudaro = len[0]*len[0] == len[1]*len[1] + len[2]*len[2];

    /*
    printf("Koordinates\n");
    for(int i = 0; i < 3; i++){
        printf("x: %lf, y: %lf\n", x[i], y[i]);
        //printf("len: %lf\n", len[i]);
    }
    */
    if(sudaro){
        if(len[0] == 0 || len[1] == 0 || len[2] == 0){
            printf("NESUDARO jokio trikampio.\n");
            printf("Nes yra sutampanciu tasku.\n");
        }else{
            printf("SUDARO statu trikampi.\n");
            printf("Nes atstumams tarp tasku: %.2lf, %.2lf, %.2lf galioja lygybe: a^2 = b^2 + c^2\n", len[0], len[1], len[2]);
        }
    }
    else{
        if(len[0] >= len[1] + len[2]){
            printf("NESUDARO jokio trikampio.\n");
            printf("Nes ilgiausias atstumas tarp koordinaciu yra didesnis nei kitu dvieju atstumu suma.\n");
        }
        else{
            printf("NESUDARO stataus trikampio.\n");
            printf("Nes atstumams tarp tasku: %.2lf, %.2lf, %.2lf negalioja lygybe: a^2 = b^2 + c^2\n", len[0], len[1], len[2]);
        }
    }

}