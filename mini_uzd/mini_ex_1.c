#include <stdio.h>
#include <stdlib.h>

void get_quotent_and_remainder(int first, int second, int *dalmuo, int *liekana);
int get_sum(int first, int second);

int main(){
    printf("Si programa atspausdina dvieju ivestu skaiciu suma, dalmeni ir liekana.\n");
    int quotent = 0;
    int remainder = 0;
    int sum = 0;
    int first = 0;
    int second = 0;
    char end = 'n';

    while(end != 'y' && end != 'Y'){
        printf("Iveskite pirma skaiciu:\n");
        scanf("%d", &first);
        printf("Iveskite antra skaiciu:\n");
        scanf("%d", &second);
        
        sum = get_sum(first, second);
        get_quotent_and_remainder(first, second, &quotent, &remainder);
        printf("Suma: %d, dalmuo: %d, liekana: %d\n", sum, quotent, remainder);
        fflush(stdin);
        printf("Ar norite baigti? y/N\n");
        scanf("%1s", &end);
        fflush(stdin);
    }
    
}

int get_sum(int first, int second){
    return first + second;
}


void get_quotent_and_remainder(int first, int second, int *quotent, int *remainder){
    *quotent = 0;
    char quotent_negative = 0;
    char remainder_negative = 0;
    if(second == 0){
        printf("Dalyba is nulio negalima!");
        return;
    }

    if(first < 0){
        first = -first;
        remainder_negative = 1;
    }

    if(second < 0){
        second = -second;
        quotent_negative = 1;
    }

    while(first - second >= 0){
        first -= second;
        (*quotent)++;
    }

    (*remainder) = first;

    if(quotent_negative){
        (*quotent) = -(*quotent);
    }

    if(remainder_negative){
        (*remainder) = -(*remainder);
        (*quotent) = -(*quotent);
    }

    
}