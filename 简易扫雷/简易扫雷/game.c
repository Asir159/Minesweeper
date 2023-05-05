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

	printf("------扫雷游戏------\n");
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
	printf("------扫雷游戏------\n");
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

//标记雷
void MarkMine(char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;

	while (1)
	{
		printf("请输入需要标记的坐标:>");
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
				printf("该位置不能被标记,请重新输入\n");
			}
		}
		else
		{
			printf("坐标输入错误,请从新输入\n");
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
		printf("请输入坐标:>");
		scanf("%d %d", &x, &y);
		//检查坐标是否合法
		if ((x >= 1 && x <= row) && (y >= 1 && y <= col))
		{
			if (mine[x][y] == '1')		//是雷
			{
				system("cls");
				printf("您被炸死了\n");
				DisPlayBoard(mine, ROW, COL);
				break;
			}
			else						//不是雷
			{
				if (show[x][y] != '*')				//判断是否被重复排查
				{
					printf("改位置已经排查过了\n");
					continue;
				}
				else
				{
					FineZero(mine, show, row, col, x, y, p);
					system("cls");
					DisPlayBoard(show, ROW, COL);
					printf("如果需要标记请输入y/Y，否则请按任意键:> ");
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
			printf("坐标输入错误,请重新输入\n");
		}
	}
	if (win >= row * col - EASY_COUNT)
	{
		printf("恭喜你获胜了\n");
		DisPlayBoard(mine, ROW, COL);
	}
}

//获取周围雷的个数
int get_mine_cnt(char mine[ROWS][COLS], int x, int y)
{
	/*return  mine[x - 1][y] + mine[x - 1][y - 1] +
			mine[x][y - 1] + mine[x + 1][y - 1] +
			mine[x + 1][y] + mine[x + 1][y + 1] +
			mine[x][y + 1] + mine[x - 1][y + 1] - 8 * '0';*/

	int i , j ;
	int count = 0;

	for (i = x - 1; i <= x + 1; i++)				//从坐标行减一开始 例如(2,2) x-1 从1行开始扫描
	{												//扫描到x+1行,列也同理,这样就可以获取周围雷的个数				
		for (j = y - 1; j <= y + 1; j++)
		{
			if (mine[i][j] == '1')					//周围扫描到就计数器+1
			{
				count++; 
			}
		}
	} 
	return count;									//返回扫描到的结果
}


//递归爆炸式展开
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