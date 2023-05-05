#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"


void menu()
{
	printf("************************************\n");
	printf("*******1. Play     0. Exit *********\n");
	printf("************************************\n");
}

void PlayGame()
{
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };

	//初始化棋盘
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	system("cls");
	DisPlayBoard(show, ROW, COL);
	//布置雷
	SetMine(mine, ROW, COL);
	/*DisPlayBoard(mine, ROW, COL);*/
	FindMine(mine, show, ROW, COL);
}

void test()
{
	int input = 0;

	srand((unsigned int)time(NULL));

	do {
		menu();
		printf("请输入:>");
		scanf("%d", &input);

		switch (input)
		{
		case 1:
			PlayGame();
			break;
		case 0:
			printf("退出成功\n");
			break;
		default:
			printf("输入错误，请重新输入\n");
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}