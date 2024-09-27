#include<cstdio>
#include<ctime>//���������
#include<cstring>
#include<windows.h>
#include<conio.h>//��_getch()������_kbhit()
#include<cmath>//����ֵ����
#include<algorithm>
#include<iostream>

const int MAX = 24;
const int road = 1;//��const�����Ķ��ͱ��,,,������
const int wall = 0;//��ʼ��Ϊ0
const int pl = 2;


void swap_my(int* a, int* b) {
	*a = *a - *b;
	*b = *b + *a;
	*a = *b - *a;
	return;
}
//���еĹ�괦������������������ѧ��

void hide_cursor() {//���ع��

	CONSOLE_CURSOR_INFO my_cur = { 1,0 };

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &my_cur);
}
/* typedef struct _CONSOLE_CURSOR_INFO{ 
		DWORD dwSize;(����С0 ~ 100)(������丳ֵ��
		BOOL bVsible;(�Ƿ�ɼ���true�ɣ�)
	}CONSOLE_CURSOR_INFO,*PCONSOLE_CURSOR_INFO;
   HANDLE:������ָ�룬�������Ľӿڣ���װ��
   GetStdHandle:��ȡָ����׼�豸���
   STD_INPUT_HANDLE   ��׼�����������̣�
   STD_OUTPUT_HANDLE  ��׼����������ʾ����
   STD_ERROR_HANDLE   ��׼����������ʾ����
   SetConsoleCursorInfo(HANDLE, CONSOLE_CURSOR_INFO *) ���ÿ���̨�����Ϣ
*/
void towhere(int a,int b) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD loca;
	loca.X = a;
	loca.Y = b;
	SetConsoleCursorPosition(handle, loca);
	return;
	/*
	 typedef struct _COORD{
		SHORT X;
		SHORT Y;
	 }COORD,*PCOORD;
	 ���ڱ�ʾ�������
	 SetConsoleCursorPosition(HANDLE, COORD):���ÿ���̨���λ��
	*/
}
//part of random maze
void setup_maze(int ** maze,int x,int y) {//������Թ�
	maze[x][y] = road;
	int direct[4][2] = { { 1, 0},{-1, 0},{ 0, -1},{ 0, 1} };
	//���������
	for (int i = 0; i < 4; i++) {
		int c = rand() % 4;/*
		swap_my(&direct[c][0], &direct[0][0]);
		swap_my(&direct[c][1], &direct[0][1]);*/
		int t = direct[c][0];
		direct[c][0] = direct[0][0];
		direct[0][0] = t; 
		t = direct[c][1];
		direct[c][1] = direct[0][1];
		direct[0][1] = t;
	}
	for (int i = 0; i < 4; i++) {
		int tx = x, ty = y;
		int shrt_dis = rand() % 6 + 1;//˳��һ��������
		while (shrt_dis > 0) {
			tx += direct[i][0];
			ty += direct[i][1];
			if (maze[tx][ty] == road) //����ͷ
				break;
			int jud = 0;
			for (int j = tx - 1; j <= tx + 1; j++) {
				for (int k = ty - 1; k <= ty + 1; k++) {
					//��������ĸ�����
					if (abs(k - ty) + abs(j - tx) == 1 && maze[j][k] == road)
						jud += 1;
				}
			}
			if (jud > 1)//�жϹ���ͷ·��Ҫ�����������еĻ���Ҫ���ڴ��ˡ�����
				break;
			shrt_dis -= 1;
			maze[tx][ty] = road;
		}
		if (shrt_dis <= 0) {
			setup_maze(maze, tx, ty);//�ݹ�����ߣ�
		}
	}
	return;
}
int originize_maze(int ** maze,int st,int ed) {
	//�����Թ���ʱ���ڳ���(���Ƿ����ж�)
	for (int i = 0; i < MAX; i++) {
		maze[i][0] = road;
		maze[0][i] = road;
		maze[i][MAX - 1] = road;
		maze[MAX - 1][i] = road;
	}
	setup_maze(maze, st, ed + 1);
//	CreateMaze(maze, st, ed + 1);
	maze[st][ed] = pl;
	for (int i = MAX - 3; i > 0; i--) {
		if (maze[i][MAX - 3] == road) {
			maze[i][MAX - 2] = road;
			return i;
		}
	}
}
void picture_maze(int** maze,int mark) {
	hide_cursor();
	towhere(0, 0);
	//���ǲ���cls
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j <= MAX;j ++) {
			if (maze[i][j] == road)
				printf("  ");//�������룬С�ӣ�
			if (maze[i][j] == wall)
				printf("��");
			if (maze[i][j] == pl)
				printf("��");
		}
		printf("\n");
	}
	printf("now mark:");
	printf("%05d", mark);
	return;
}
int move_pl(int** maze, char tool, int* x, int* y,int mark) {
	int a = *x, b = *y;
	switch (tool) {
	case 'w':
		*x -= 1;
		break;
	case 'a':
		*y -= 1;
		break;
	case 's':
		*x += 1;
		break;
	case 'd':
		*y += 1;
		break;
	default:
		return mark;
	}
	if (*x > 0 && *y > 0 && *x < MAX - 1&& *y < MAX - 1&& maze[*x][*y] != wall) {
		maze[a][b] = road;
		maze[*x][*y] = pl;
		mark -= 10;
		picture_maze(maze, mark);
		return mark;
	}
	*x = a;
	*y = b;
	return mark;
}
int game_exe(void) {
	srand((unsigned)time(NULL));
	int mark = 10000;
	int x = rand() % (MAX - 4) + 2, y = 1;
	int** maze = (int**)malloc(MAX * sizeof(int*));//������*������
	for (int i = 0; i < MAX; i++) {
		maze[i] = (int*)calloc(MAX, sizeof(int));//��ʼ����
	}
	int ed = originize_maze(maze,x,y),pler = 1;
	system("cls");
	picture_maze(maze,mark);
	while (1) {
		if (_kbhit()) {//�ж��Ƿ�����
			char tool_game = _getch();
			if (tool_game == 27) {
				pler = 0;
				break;
			}
			mark = move_pl(maze, tool_game, &x, &y, mark);
		}
		if (x == ed && y == MAX - 2) {
			system("cls");
			printf("win,i guess");
			Sleep(1500);
			break;
		}
	}
	for (int i = 0; i < MAX; i++)
		free(maze[i]);
	free(maze);
	if (pler)
		return mark;
	else
		return 0;
}
void start(void) {
	int mark_max = 0;
	while (1) {
		system("cls");
		printf("press any key to start...");
		printf("\nand use esc to exit");
		printf("\nnow the largest mark is %d",mark_max);
		char jud = _getch();//�޻��Զ���
		if (jud == 27)
			break;
		else {
			int ed_mark = game_exe();
			if (ed_mark > mark_max)
				mark_max = ed_mark;
		}
	}
	return;
}
int main() {
	start();
	return 0;
}