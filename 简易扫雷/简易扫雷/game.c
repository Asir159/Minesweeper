#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"


void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	int i, j;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}

void DisPlayBoard(char board[ROWS][COLS], int row, int col)
{
	int i, j;

	printf("------ɨ����Ϸ------\n");
	for (i = 0; i <= row; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("------ɨ����Ϸ------\n");
}

void SetMine(char board[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int count = EASY_COUNT;

	while (count)
	{
		x = rand() % row + 1;
		y = rand() % col + 1;

		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}

}

//�����
void MarkMine(char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;

	while (1)
	{
		printf("��������Ҫ��ǵ�����:>");
		scanf("%d %d", &x, &y);
		if ((x >= 1 && x <= row) && (y >= 1 && y <= col))
		{
			if (show[x][y] == '*')
			{
				show[x][y] = '!';
				break;
			}
			else
			{
				printf("��λ�ò��ܱ����,����������\n");
			}
		}
		else
		{
			printf("�����������,���������\n");
		}
	}
}

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int count = 0;
	int win = 0;
	int* p = &win;
	char ch = 0;

	while (win<row * col - EASY_COUNT)
	{
		printf("����������:>");
		scanf("%d %d", &x, &y);
		//��������Ƿ�Ϸ�
		if ((x >= 1 && x <= row) && (y >= 1 && y <= col))
		{
			if (mine[x][y] == '1')		//����
			{
				system("cls");
				printf("����ը����\n");
				DisPlayBoard(mine, ROW, COL);
				break;
			}
			else						//������
			{
				if (show[x][y] != '*')				//�ж��Ƿ��ظ��Ų�
				{
					printf("��λ���Ѿ��Ų����\n");
					continue;
				}
				else
				{
					FineZero(mine, show, row, col, x, y, p);
					system("cls");
					DisPlayBoard(show, ROW, COL);
					printf("�����Ҫ���������y/Y�������밴�����:> ");
					while ((ch = getchar()) != '\n');
					scanf("%c",&ch);
					if (ch == 'y' || ch == 'Y')
					{
						MarkMine(show, row, col);
						system("cls");
						DisPlayBoard(show, ROW, COL);
					}
					else
					{
						continue;
					}
				}
			}
		}
		else
		{
			printf("�����������,����������\n");
		}
	}
	if (win >= row * col - EASY_COUNT)
	{
		printf("��ϲ���ʤ��\n");
		DisPlayBoard(mine, ROW, COL);
	}
}

//��ȡ��Χ�׵ĸ���
int get_mine_cnt(char mine[ROWS][COLS], int x, int y)
{
	/*return  mine[x - 1][y] + mine[x - 1][y - 1] +
			mine[x][y - 1] + mine[x + 1][y - 1] +
			mine[x + 1][y] + mine[x + 1][y + 1] +
			mine[x][y + 1] + mine[x - 1][y + 1] - 8 * '0';*/

	int i , j ;
	int count = 0;

	for (i = x - 1; i <= x + 1; i++)				//�������м�һ��ʼ ����(2,2) x-1 ��1�п�ʼɨ��
	{												//ɨ�赽x+1��,��Ҳͬ��,�����Ϳ��Ի�ȡ��Χ�׵ĸ���				
		for (j = y - 1; j <= y + 1; j++)
		{
			if (mine[i][j] == '1')					//��Χɨ�赽�ͼ�����+1
			{
				count++; 
			}
		}
	} 
	return count;									//����ɨ�赽�Ľ��
}


//�ݹ鱬ըʽչ��
void FineZero(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col , int x, int y, int *p)
{
	int i, j;
	int count = 0;


	if ((x >= 1 && x <= row) && (y >= 1 && y <= col))
	{
		count = get_mine_cnt(mine, x, y);

		if (count != 0)
		{
			(*p)++;
			show[x][y] = count + '0';
		}
		else
		{
			(*p)++;
			show[x][y] = ' ';						
			for (i = x - 1; i <= x + 1; i++)
			{
				for (j = y - 1; j <= y + 1; j++)
				{
					if (show[i][j] == '*')
					{
						FineZero(mine, show, row, col, i, j, p);
					}
				}
			}

		}
	}
}