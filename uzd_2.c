#include <stdio.h>
#include <stdlib.h>
#define N 8

void recursion(int *arr, int n);
char allFieldsAttacked(int *arr);
char isInSameDiagonal(int a, int b);
void print_board(int board[N][N]);

int count = 0;
int board[N][N];

int main(){
    int arr[N] = {0};
    int board[N*N] = {0};
    for(int i = 1; i <= 64; i++){
        arr[0] = i;
        recursion(arr, 1);
    }
    
    printf("%lld\n", count); 
}

// (derinys) 64C8 = 64!/ (56! * 8!) = 4426165368 // possible variations to place 8 bishops
//                                    5130659560 // total possible variations to place at least 1 bishop
//                                    22522960   // number of ways to place 8 bishops so all squares are attacked
void recursion(int *arr, int n){
    if(n == 8){
        if(allFieldsAttacked(arr)){
            count++;
        }
    }

    if(n >= 8 || arr[n-1] >= 64)
        return;

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

    printf("Solution %d:\n", count+1);
    print_board(board);
    
    return 1;


}

void print_board(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}