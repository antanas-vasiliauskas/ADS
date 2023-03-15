#include <stdio.h>

void print_attacked_squares(int bishops[][2], int num_bishops) {
    // initialize the chess board as empty
    char board[8][8] = { 0 };
    
    // mark the squares attacked by each bishop
    for (int i = 0; i < num_bishops; i++) {
        int row = bishops[i][0];
        int col = bishops[i][1];
        int r, c;
        
        // mark the diagonal going up and right
        r = row - 1;
        c = col + 1;
        while (r >= 0 && c < 8) {
            board[r][c] = 1;
            r--;
            c++;
        }
        
        // mark the diagonal going up and left
        r = row - 1;
        c = col - 1;
        while (r >= 0 && c >= 0) {
            board[r][c] = 1;
            r--;
            c--;
        }
        
        // mark the diagonal going down and right
        r = row + 1;
        c = col + 1;
        while (r < 8 && c < 8) {
            board[r][c] = 1;
            r++;
            c++;
        }
        
        // mark the diagonal going down and left
        r = row + 1;
        c = col - 1;
        while (r < 8 && c >= 0) {
            board[r][c] = 1;
            r++;
            c--;
        }
    }
    for(int i = 0; i < num_bishops; i++){
        int row = bishops[i][0];
        int col = bishops[i][1];
        board[row][col] = 2;
    }
    
    // print the chess board with the attacked squares marked as "X"
    printf("   a b c d e f g h\n");
    for (int row = 0; row < 8; row++) {
        printf("%d ", 8 - row);
        for (int col = 0; col < 8; col++) {
            if (board[row][col] == 1) {
                printf("X ");
            } 
            else if(board[row][col] == 2){
                printf("Y ");
            }
            else {
                printf(". ");
            }
        }
        printf("%d\n", 8 - row);
    }
    printf("   a b c d e f g h\n");
}

int main() {
    int bishops[][2] = { {0, 0}, {2, 2}, {3, 5} };
    int num_bishops = 3;
    print_attacked_squares(bishops, num_bishops);
    return 0;
}