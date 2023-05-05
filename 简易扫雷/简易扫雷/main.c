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

	//��ʼ������
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	system("cls");
	DisPlayBoard(show, ROW, COL);
	//������
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
		printf("������:>");
		scanf("%d", &input);

		switch (input)
		{
		case 1:
			PlayGame();
			break;
		case 0:
			printf("�˳��ɹ�\n");
			break;
		default:
			printf("�����������������\n");
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}