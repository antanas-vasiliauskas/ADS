// Sustatyti šachmatu lentoje 8 rikius, kad kiekviena langelį kirstų bent vienas rikis.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 8

void recursion(int *arr, int n);
char allFieldsAttacked(int *arr);
char isInSameDiagonal(int a, int b);
void print_board(int board[N][N]);

char getRow(int cell);
char getColumn(int cell);

int count = 0;
int count_2 = 0;
int board[N][N] = {0};
FILE *f1;


int main(){
    f1 = fopen("protokolas1.txt", "w");

    char *str1 = "Antanas Vasiliauskas 3 grupe 2 pogrupis\nSALYGA.\nPastatyti 8x8 lentoje 8 rikius, kad kiekvienas lentos langelis butu kertamas bent 1 karta.\nSPRENDIMO IDEJA.\nStatome rikius per eilutes per stulpelius i dar neuzimtas istrizaines pradedant nuo X=1 Y=1\nir tikriname ar visi lentos langeliai yra kertami.\n1 DALIS. Duomenys\n1) Lenta: 8x8, Rikiu skaicius: 8\n2) Lentos zymejimas:\n";
    fwrite(str1, 1, strlen(str1), f1);
    printf("%s", str1);
    print_board(board);
    char *str2 = "2 DALIS. Vykdymas\n";
    fwrite(str2, 1, strlen(str2), f1);
    int arr[N] = {0};
    for(int i = 1; i <= 64; i++){
        arr[0] = i;
        recursion(arr, 1);
    }
    char str3[100];
    sprintf(str3, "\n3 DALIS. Rezultatai:\nBandymu skaicius: %d\nIsvada: egzistuoja bent %d budas sustatyti 8 rikius taip, kad kiekvienas langelis butu kertamas bent viena karta.\nSprendimo variantas grafiškai:\n", count_2, count);
    fwrite(str3, 1, strlen(str3), f1);
    printf("%s", str3);
    print_board(board);
    fclose(f1);
}

// (derinys) 64C8 = 64!/ (56! * 8!) = 4426165368 // possible variations to place 8 bishops
//                                    5130659560 // total possible variations to place at least 1 bishop
//                                    22522960   // number of ways to place 8 bishops in different diagonals.

int prev_n = -1;
void recursion(int *arr, int n){

    if(prev_n != -1 && count < 1){
        if(prev_n == n){
            fwrite(" Toliau.\n", 1, strlen(" Toliau.\n"), f1);
        }
        else if(prev_n > n){
            fwrite(" Backtrack.\n", 1, strlen(" Backtrack.\n"), f1);
        }
        else if (prev_n < n){
            fwrite(" Gilyn.\n", 1, strlen(" Gilyn.\n"), f1);
        }
    }
    prev_n = n;

    if(count > 0)
        return;
    char str[100] = {0};
    sprintf(str, "%6d) ", count_2+1);
    fwrite(str, 1, strlen(str), f1);

    char str2[10] = {0};
    for(int i = 0; i < n-1; i++){
        str2[i] = '-';
    }
    fwrite(str2, 1, strlen(str2), f1);

    char str10[100];
    sprintf(str10, "Statomas rikis %d i X=%c, Y=%c. ", n, getColumn(arr[n-1]),  getRow(arr[n-1]));
    fwrite(str10, 1, strlen(str10), f1);


    char *str3 = "Rikiu busena: {";
    fwrite(str3, 1, strlen(str3), f1);

    

    for(int i = 0; i < n; i++){
        char str1[10] = {0};
        sprintf(str1, "(X=%c Y=%c)", getColumn(arr[i]), getRow(arr[i]));
        fwrite(str1, 1, strlen(str1), f1);
        if(i != n-1)
            fwrite(" ", 1, 1, f1);
    }
    
    count_2++;
    if(n == 8){
        if(allFieldsAttacked(arr)){
            count++;
            fwrite("}. Pozicija tinkama.\n", 1, strlen("}. Pozicija tinkama.\n"), f1);
            for(int i = 0; i < 8; i++)
                for(int j = 0; j < 8; j++)
                    board[i][j] = 0;
            for(int i = 0; i < 8; i++){
                int x = (arr[i] - 1) / 8;
                int y = (arr[i] - 1) % 8;
                board[x][y] = 1;
            }
            return;
        }    
    }
    fwrite("}. Ne visi langeliai kertami.", 1, strlen("}. Ne visi langeliai kertami."), f1);

    if(n >= 8 || arr[n-1] >= 64)
        return;

    char written = 0;

    for(int i = arr[n-1] + 1; i <= 64; i++){
        for(int j = 0; j < n; j++){
            if(isInSameDiagonal(arr[j], i)){
                goto sameDiagonal;
            }
        }
        int odd = 0;
        int even = 0;
        for(int j = 0; j < n; j++){
            if(arr[j] % 2 == 0) even++;
            else odd++;
        }
        if(i % 2 == 0) even++;
        else odd++;

        if(odd > 4 || even > 4)
            goto sameDiagonal;

        arr[n] = i;
        recursion(arr, n + 1);
        arr[n] = 0;
        sameDiagonal:;
    }

}

char isInSameDiagonal(int a, int b){
    int x1 = (a - 1) % 8;
    int y1 = (a - 1) / 8;
    int x2 = (b - 1) % 8;
    int y2 = (b - 1) / 8;
    if(abs(x1 - x2) == abs(y1 - y2))
        return 1;
    else
        return 0;
}

char getRow(int cell){
    return (cell - 1) / 8 + 1 + '0';
}
char getColumn(int cell){
    return (cell - 1) % 8 + '1';
}

char allFieldsAttacked(int *arr){
    

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] = -1;
        }
    }

    for(int i = 0; i < N; i++){
        int x = (arr[i] - 1) % 8;
        int y = (arr[i] - 1) / 8;
        // Check upper left diagonal
        for (int q = x, z = y; q >= 0 && z >= 0; q--, z--) {
            board[q][z] = 0;
        }
        // Check upper right diagonal
        for (int q = x, z = y; q >= 0 && z < N; q--, z++) {
            board[q][z] = 0;
        }

        // Check lower left diagonal
        for (int q = x, z = y; q < N && z >= 0; q++, z--) {
            board[q][z] = 0;
        }

        // Check lower right diagonal
        for (int q = x, z = y; q < N && z < N; q++, z++) {
            board[q][z] = 0;
        }
    }
    for(int i = 0; i < N; i++){
        int x = (arr[i] - 1) % 8;
        int y = (arr[i] - 1) / 8;
        board[x][y] = 1;
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] == -1)
                return 0;
        }
    }
    /*
    printf("Solution %d:\n", count+1);
    print_board(board);
    */
    
    return 1;


}

void print_board(int board[N][N]) {
    char str0[50] = "Y, V ^\n";
    printf("%s", str0);
    fwrite(str0, 1, strlen(str0), f1);

    for (int i = 0; i < N; i++){
        char str1[100];
        sprintf(str1, "   %d | ", 8-i);\
        fwrite(str1, 1, strlen(str1), f1);
        printf("%s", str1);
        for (int j = 0; j < N; j++){
            char str2[100];
            sprintf(str2, "%d ", board[i][j]);
            fwrite(str2, 1, strlen(str2), f1);
            printf("%s", str2);
        }
        fwrite("\n", 1, strlen("\n"), f1);
        printf("\n");
    }
    printf("      ------------------> X, U");
    fwrite("      ------------------> X, U", 1, strlen("      ------------------> X, U"), f1);
    fwrite("\n", 1, strlen("\n"), f1);
    printf("\n");
    fwrite("       ", 1, strlen("       "), f1);
    printf("       ");
    for (int i = 0; i < N; i++){
        char str3[100];
        sprintf(str3, "%d ", i+1);
        fwrite(str3, 1, strlen(str3), f1);
        printf("%s", str3);
    }
    fwrite("\n", 1, strlen("\n"), f1);
    printf("\n");
}