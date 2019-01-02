/*
    lifegame_cycle.c
    saku
*/

#include <stdio.h>
#include <stdlib.h>

#define H_MAX 50
#define W_MAX 100 

int main(void) {
    char filename1[80] = "input.txt";
    char filename2[80] = "output_cycle.txt";
    FILE *fp1, *fp2;

    int num;
    char currentboard[H_MAX][W_MAX], nextboard[H_MAX][W_MAX];
    int dx[8] = {0,0,-1,1,-1,-1,1,1};
    int dy[8] = {-1,1,0,0,-1,1,-1,1};
    int i, j, k;

    if((fp1 = fopen(filename1, "r")) == NULL){
        fprintf(stderr, "%s: file cannot open.\n", filename1);
        return 1;
    }

    if((fp2 = fopen(filename2, "w")) == NULL){
        fprintf(stderr, "%s: file cannot open.\n", filename2);
        return 1;
    }

    for (i = 0; i < H_MAX; i++) {
        for (j = 0; j < W_MAX; j++) {
            fscanf(fp1, " %c", &currentboard[i][j]);  //空白、改行を読み飛ばして入力
            nextboard[i][j] = currentboard[i][j];
        }
    }
    scanf("%d", &num); 

    while (num--) {
        for (i = 0; i < H_MAX; i++) {
            for (j = 0; j < W_MAX; j++) {
                int count = 0;
                for (k = 0; k < 8; k++) {
                    if (currentboard[ (i + dx[k] + H_MAX) % H_MAX ][ (j + dy[k] + W_MAX) % W_MAX ] == '1') count++;
                }

                if (currentboard[i][j] == '0') {
                    if (count == 3) nextboard[i][j] = '1'; 
                } else if (currentboard[i][j] == '1') {
                    if (count <= 1) nextboard[i][j] = '0';
                    else if (count >= 4) nextboard[i][j] = '0';
                    else nextboard[i][j] = '1';
                }
            }
        }

        for (i = 0; i < H_MAX; i++) {
            for (j = 0; j < W_MAX; j++) {
                currentboard[i][j] = nextboard[i][j];
            }
        }        
    }

    for (i = 0; i < H_MAX; i++) {
        for (j = 0; j < W_MAX; j++) {
            fprintf(fp2, "%c", currentboard[i][j]);
        }
        fprintf(fp2, "\n");
    }

    fclose(fp1);
    fclose(fp2);
    return 0;

}
