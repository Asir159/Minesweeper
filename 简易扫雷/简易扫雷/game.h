#ifndef _GAME_H
#define _GAME_H

#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2

#define EASY_COUNT 10

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void PlayGame();

void SetMine(char board[ROWS][COLS], int row, int col);
void DisPlayBoard(char board[ROWS][COLS], int row, int col);
void InitBoard(char board[ROWS][COLS], int row, int col, char set);
void FineZero(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int x, int y, int* pw);
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);


#endif