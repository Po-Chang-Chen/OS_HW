#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int sudoku[9][9] = {
        {1,9,3,2,6,5,4,7,8},
	{7,8,2,3,1,4,9,5,6},
	{4,5,6,9,7,8,1,3,2},
	{2,3,4,8,5,1,6,9,7},
	{9,6,5,4,3,7,2,8,1},
	{8,7,1,6,9,2,3,4,5},
	{3,1,9,5,8,6,7,2,4},
	{5,2,7,1,4,3,8,6,9},
	{6,4,8,7,2,9,5,1,3}
};

int invalidSudoku[9][9] = {
        {5, 1, 4, 5, 3, 9, 1, 8, 7},
        {6, 1, 9, 7, 2, 8, 6, 3, 4},
        {9, 3, 7, 8, 1, 4, 2, 9, 5},
        {2, 4, 3, 8, 6, 5, 7, 2, 9},
        {7, 5, 8, 2, 4, 7, 3, 6, 1},
        {8, 6, 2, 3, 9, 1, 4, 5, 8},
        {4, 7, 1, 9, 5, 4, 8, 4, 2},
        {3, 9, 6, 1, 8, 2, 5, 7, 3},
        {1, 8, 5, 4, 7, 3, 9, 1, 9}
};

bool verification[11];
int checkGrids = 2;

typedef struct {
    int row;
    int column;
} parameter;

pthread_t cols_thread, rows_thread, first_thread, second_thread, third_thread,
        fourth_thread, fifth_thread, sixth_thread, seventh_thread, eighth_thread, ninth_thread;

void *colCheck(void *parametros) {
    parameter *column = (parameter *) parametros;
    int columnInitial = column->column;
    int rowInitial = column->row;
	int i ,j;
    for (i = columnInitial; i < 9; i++) {
        int col[9] = {0};
        for (j = rowInitial; j < 9; j ++) {
            int aux = sudoku[i][j];
            if (col[aux - 1] == 0 && aux > 0) {
                col[aux - 1] = aux;
            } else if (aux <= 0) {
                verification[0] = 0;
                printf("col [%d] has an invalid number\n", j + 1);
            } else {
                verification[0] = 0;
                printf("col [%d] has an repeated number\n", j + 1);
            }
        }
    }
    verification[0] = 1;
    pthread_exit(0);
}

void *rowCheck(void *parametros) {
    parameter *row = (parameter *) parametros;
    int columnInitial = row->column;
    int rowInitial = row->row;
	int i,j;
    for (i = columnInitial; i < 9; i++) {
        int fil[9] = {0};
        for (j = rowInitial; j < 9; j++) {
            int aux = sudoku[i][j];
            if (fil[aux - 1] == 0 && aux > 0) {
                fil[aux - 1] = aux;
            } else if (aux <= 0) {
                verification[0] = 0;
                printf("row [%d] has an invalid number\n", i + 1);
            } else {
                verification[0] = 0;
                printf("row [%d] has an repeated number\n", i + 1);

            }
        }
    }
    verification[1] = 1;
    pthread_exit(0);
}

void *gridCheck(void *parametros) {
    parameter *Square_row = (parameter *) parametros;
    int rowInitial = Square_row->row;
    int columnInitial = Square_row->column;
    int square[9] = {0};
	int i,j;
    for (i = rowInitial; i < rowInitial + 3; ++i) {
        for (j = columnInitial; j < columnInitial + 3; ++j) {
            int aux = sudoku[i][j];
            if (square[aux - 1] == 0 && aux > 0) {
                square[aux - 1] = aux;
            } else {
                verification[checkGrids] = 0;
                checkGrids++;
                pthread_exit(0);
            }
        }
    }
    verification[checkGrids] = 1;
    checkGrids++;
    pthread_exit(0);
}

void printSudoku(int arr[9][9]) {
	int i,j;
    for(i =0;i<9;i++){
        for(j=0;j<9;j++){
            printf("%d ",arr[i][j]);
            if (j == 8) {}
            else if (j % 3 == 2) printf("| ");
        }
        if (i == 8) {}
        else if (i % 3 == 2) printf("\n---------------------------------- ");
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
	int i,j;
    if (argc == 2 && !(strcmp(argv[1], "invalidSudoku"))) {
        for (i = 0; i < 9; ++i) {
            for (j = 0; j < 9; ++j) {
                sudoku[i][j] = invalidSudoku[i][j];
            }
        }
    }

    parameter *verificarrows = (parameter *) malloc(sizeof(parameter));
    verificarrows->row = 0;
    verificarrows->column = 0;

    parameter *verificarcolumns = (parameter *) malloc(sizeof(parameter));
    verificarcolumns->row = 0;
    verificarcolumns->column = 0;

    parameter *grid1  = (parameter *) malloc(sizeof(parameter));
    grid1->row = 0;
    grid1->column = 0;

    parameter *grid2  = (parameter *) malloc(sizeof(parameter));
    grid2->row = 0;
    grid2->column = 3;

    parameter *grid3  = (parameter *) malloc(sizeof(parameter));
    grid3->row = 0;
    grid3->column = 6;

    parameter *grid4  = (parameter *) malloc(sizeof(parameter));
    grid4->row = 3;
    grid4->column = 0;

    parameter *grid5  = (parameter *) malloc(sizeof(parameter));
    grid5->row = 3;
    grid5->column = 3;

    parameter *grid6  = (parameter *) malloc(sizeof(parameter));
    grid6->row = 3;
    grid6->column = 6;

    parameter *grid7  = (parameter *) malloc(sizeof(parameter));
    grid7->row = 6;
    grid7->column = 0;

    parameter *grid8  = (parameter *) malloc(sizeof(parameter));
    grid8->row = 6;
    grid8->column = 3;

    parameter *grid9  = (parameter *) malloc(sizeof(parameter));
    grid9->row = 6;
    grid9->column = 6;

    pthread_create(&cols_thread, NULL, colCheck, (void *) verificarcolumns);
    pthread_create(&rows_thread, NULL, rowCheck, (void *) verificarrows);
    pthread_create(&first_thread, NULL, gridCheck, (void *) grid1);
    pthread_create(&second_thread, NULL, gridCheck, (void *) grid2);
    pthread_create(&third_thread, NULL, gridCheck, (void *) grid3);
    pthread_create(&fourth_thread, NULL, gridCheck, (void *) grid4);
    pthread_create(&fifth_thread, NULL, gridCheck, (void *) grid5);
    pthread_create(&sixth_thread, NULL, gridCheck, (void *) grid6);
    pthread_create(&seventh_thread, NULL, gridCheck, (void *) grid7);
    pthread_create(&eighth_thread, NULL, gridCheck, (void *) grid8);
    pthread_create(&ninth_thread, NULL, gridCheck, (void *) grid9);

    pthread_join(cols_thread, NULL);
    pthread_join(rows_thread, NULL);
    pthread_join(first_thread, NULL);
    pthread_join(second_thread, NULL);
    pthread_join(third_thread, NULL);
    pthread_join(fourth_thread, NULL);
    pthread_join(fifth_thread, NULL);
    pthread_join(sixth_thread, NULL);
    pthread_join(seventh_thread, NULL);
    pthread_join(eighth_thread, NULL);
    pthread_join(ninth_thread, NULL);
    printf("The Sudoku is: \n");
    printSudoku(sudoku);
	int k;
    for (k = 0; k < 11; ++k) {
        if (!verification[k]) {
            printf("\nThe Sudoku was not solved.\n");
            exit(0);
        }
    }
    printf("\nThe Sudoku was solved.\n");
    return 0;
}
