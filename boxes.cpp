#include<cstdio>
#include<conio.h>
#include<iostream>
#include<windows.h>


const int L = 10;
const int MAX = 20;
const char ROAD = '0';
const char WALL = '1';
const char PL = '2';
const char BOX = '3';
const char PLACE = '4';
const char CMPLT = '5';
const char IMHRE = '6';


typedef struct data {
	int num;
	int pfm;
}data_mark;

void hide_cursor(void);
void towhere(void);
void menu(void);
int game_exe(void);
void file_write(int mark);
void map_setup(char** maze);
void map_create(char** maze);
int move_pl(char** maze, int mark,int* x,int* y,char key_game);
bool judge_win(char** maze);
bool box_move(char** maze, char key_game, int x, int y);

int main() {
	menu();
	return 0;
}


void hide_cursor(void) {
	CONSOLE_CURSOR_INFO my_cur = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &my_cur);
	return;
}

void towhere(void) {
	COORD loca;
	loca.X = 0;
	loca.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loca);
	return;
}

void map_create(char** maze) {
	hide_cursor();
	towhere();
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			switch (maze[i][j]) {
			case ROAD:
				printf("  ");
				break;
			case WALL:
				printf("回");
				break;
			case PL:
				printf("人");
				break;
			case BOX:
				printf("木");
				break;
			case PLACE:
				printf("门");
				break;
			case CMPLT:
				printf("闲");//箱子进去了
				break;
			case IMHRE:
				printf("闪");//人进去了
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
	return;
}

void map_setup(char** maze) {
	map_create(maze);
	/*
	hide_cursor();
	towhere();
	for (int i = 0; i < L ; i++) {
		for (int j = 0; j < L ; j++) {
			switch (maze[i][j]) {
			case '0':
				printf("  ");
				break;
			case '1':
				printf("回");
				break;
			case '2':
				printf("人");
				break;
			case '3':
				printf("木");
				break;
			case '4':
				printf("门");
				break;
			case '5':
				printf("闲");//箱子进去了
				break;
			case '6':
				printf("闪");//人进去了
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
*/
	FILE* fp;
	fopen_s(&fp, "..\\map1_mark.txt", "r");
  	for (int j = 1;j <= 10; j++) {
		int to;
		fscanf_s(fp, "%d", &to);
	}/**/
	int* tool_ir = (int*)malloc(100 * sizeof(int));
	int i = 0;
	while (fscanf_s(fp, "%d", &tool_ir[i]) != EOF) {
		printf("the mark of the %dth gaming is %d\n", i, tool_ir[i++]);
	}
	printf("my english is really bad");
	free(tool_ir);
	fclose(fp);
	return;
}

bool box_move(char** maze, char key_game, int x, int y) {
	int i = x, j = y;
	switch (key_game) {
	case 'w':
		x--;
		break;
	case 'a':
		y--;
		break;
	case 's':
		x++;
		break;
	case 'd':
		y++;
		break;
	}
	if (x < 0 || y < 0 || x > L - 1 || y > L - 1
		|| maze[x][y] == WALL || maze[x][y] == CMPLT) {
		return 0;
	}
	if (maze[x][y] == ROAD) {
		maze[i][j] = PL;
		maze[x][y] = BOX;
		return 1;
	}
	if (maze[x][y] == PLACE) {
		maze[i][j] = PL;
		maze[x][y] = CMPLT;
		return 1;
	}
}

int move_pl(char** maze, int mark, int* x, int* y,char key_game) {
	int i = *x, j = *y;
	switch (key_game) {
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
	if (*x < 0 || *y < 0 || *x > L - 1 || *y > L - 1 
		|| maze[*x][*y] == WALL || maze[*x][*y] == CMPLT) {
		*x = i;
		*y = j;
		return mark;
	}
	if (maze[*x][*y] == ROAD) {
		if (maze[i][j] == IMHRE)
			maze[i][j] = PLACE;

		else if (maze[i][j] == PL)
			maze[i][j] = ROAD;
		maze[*x][*y] = PL;
		return mark - 10;
	}
	if (maze[*x][*y] == PLACE) {
		maze[i][j] = ROAD;
		maze[*x][*y] = IMHRE;
		return mark - 10;
	}
	if (maze[*x][*y] == BOX) {
		bool ju = box_move(maze, key_game, *x, *y);
		if (ju) {
			if (maze[i][j] == IMHRE)
				maze[i][j] = PLACE;
			if (maze[i][j] == PL)
				maze[i][j] = ROAD;
			return mark - 10;
		}
		*x = i;
		*y = j;
		return mark;
	}
}

void menu(void) {
	while (1) {
		system("cls");
		printf("a simple pushboxes-like game");
		printf(" using maps read from files\n");
		printf("i think it's no use to make so much so i just make one\n");
		printf("but there's a need to display a selecting menu\n");
		printf("so you can pretend there are lots of levels");
		Sleep(1200);
		system("cls");
		printf("this is a simple selecting menu\n");
		printf("please choose from level 1 and level 1 and so on\n");
		printf("1.level 1\n");
		printf("press any key to start and press esc to exit");
		char st_c = _getch();

		if (st_c == 27)
			return;

		else {
			int mark = game_exe();
			if (mark > 0)
				file_write(mark);
		}
	}
	return;
}

int game_exe(void) {
	char** maze = (char**)malloc(MAX * sizeof(char*));
	for (int i = 0; i < MAX; i++) {
		maze[i] = (char*)calloc(MAX, sizeof(char));
	}

	FILE* f_p;
	fopen_s(&f_p, "..\\map1_mark.txt", "r");
	for (int i = 0; i < MAX; i++) {
		fgets(maze[i], MAX, f_p);
	}
	fclose(f_p);

	system("cls");
//	for(int i = 0;i < L - 1;i ++)
//		printf("%s%d\n",maze[i],i);
//	Sleep(2000);
	map_setup(maze);
	int mark = 10000,x = 2,y = 7,pler = 0;
/**/
	while (1) {
		if (_kbhit()) {
			int key_game = _getch();
			if (key_game == 27) {
				pler = 1;
				break;
			}

			mark = move_pl(maze, mark, &x, &y, key_game);

			map_create(maze);

//			printf("ooo");
			if (judge_win(maze)) {
				system("cls");
				printf("win,i guess");
				Sleep(1500);
				break;
			}
		}
	}
	for (int i = 0; i < MAX; i++)
		free(maze[i]);
	free(maze);
	if(pler)
		return 0;
	return mark;
}

bool judge_win(char** maze) {
	int num = 0;

	for (int i = 0; i < L - 1; i++) {
		for(int j = 0;j < L - 1;j ++){
			if (maze[i][j] == '5')
				num++;
		}
	}

	if (num < 5)
		return 0;
	else
		return 1;
}

void file_write(int mark) {
	FILE* fp;
	fopen_s(&fp, "..\\map1_mark.txt", "a");
	fprintf_s(fp, "\n%d", mark);
	fclose(fp);
	return;
}
