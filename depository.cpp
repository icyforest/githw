#include<cstdio>
#include<Windows.h>
#include<conio.h>
#include<cstring>


const int MAX = 100;


void menu();
void display();
void warehouse();
void outbound();


int main() {
	menu();
	return 0;
}



void display() {
	system("cls");
	char** name = (char**)malloc(MAX * sizeof(char*));
	int* num = (int*)malloc(MAX * sizeof(int));
	for (int i = 0; i < MAX; i++) {
		name[i] = (char*)calloc(MAX, sizeof(char));
	}

	FILE* fp;
	fopen_s(&fp, "..\\depository.txt", "r");

	int i = 0;
	while (fscanf_s(fp, "%s", name[i], MAX) != EOF) {
		fscanf_s(fp, "%d", &num[i]);
		getc(fp);
		printf("%s %d\n", name[i], num[i]);
		i++;
	}

/**/
	fclose(fp);
	Sleep(2000);
	for (i = 0; i < MAX; i++) {
		free(name[i]);
	}
	free(name);
	free(num);
	return;
}

void warehouse() {
	system("cls");
	printf("input name and number\n");

	char tool_name[MAX];
	int tool_number;
	bool judge = 1;
	scanf_s("%s%d", tool_name, MAX, &tool_number);
//	printf("%s%d", tool_name, tool_number);

	char** name = (char**)malloc(MAX * sizeof(char*));
	int* num = (int*)calloc(MAX, sizeof(int));
	for (int i = 0; i < MAX; i++) {
		name[i] = (char*)calloc(MAX, sizeof(char));
	}

	FILE* fp;
	fopen_s(&fp, "..\\depository.txt", "r");

	int i = 0;
//	printf(")))))");
	while (fscanf_s(fp, "%s", name[i], MAX) != EOF) {
		fscanf_s(fp, "%d", &num[i]);
		getc(fp);
//		printf("%s %d\n", name[i], num[i]);
		i++;
	}

//	printf("%d", i);
	for (int j = 0; j < i; j++) {
		if (!strcmp(tool_name, name[j])) {
			judge = 0;
			num[j] += tool_number;
		}
	}
//	printf("%d", i);
	if (judge) {
		strcpy_s(name[i], MAX, tool_name);
		num[i++] = tool_number;
	}

	fclose(fp);

	fopen_s(&fp, "..\\depository.txt", "w");

	for (int j = 0; j < i; j++) {
		fprintf(fp, "%s %d\n", name[j],num[j]);
	}/**/

	fclose(fp);

	for (i = 0; i < MAX; i++) {
		free(name[i]);
	}
	free(name);
	free(num);

	printf("that's all");
	Sleep(1500);
	return;
}

void outbound() {
	system("cls");
	printf("input name and number\n");

	char tool_name[MAX];
	int tool_number;
	bool judge = 1;
	scanf_s("%s%d", tool_name, MAX, &tool_number);

	char** name = (char**)malloc(MAX * sizeof(char*));
	int* num = (int*)malloc(MAX * sizeof(int));
	for (int i = 0; i < MAX; i++) {
		name[i] = (char*)calloc(MAX, sizeof(char));
	}

	FILE* fp;
	fopen_s(&fp, "..\\depository.txt", "r");

	int i = 0;
	while (fscanf_s(fp, "%s", name[i], MAX) != EOF) {
		fscanf_s(fp, "%d", &num[i]);
		getc(fp);
		//		printf("%s %d\n", name[i], num[i]);
		i++;
	}

	for (int j = 0; j < i; j++) {
		if (!strcmp(tool_name, name[j])) {
			judge = 0;
			num[j] -= tool_number;
			if (num[j] < 0) {
				printf("there's no that much\n");
				num[j] = 0;
			}
		}
	}
	if (judge) {
		printf("sorry you don't have...\n");
	}

	fclose(fp);

	fopen_s(&fp, "..\\depository.txt", "w");

	for (int j = 0; j < i; j++) {
		fprintf(fp, "%s %d\n", name[j], num[j]);
	}

	fclose(fp);

	for (i = 0; i < MAX; i++) {
		free(name[i]);
	}
	free(name);
	free(num);

	Sleep(1500);

	printf("that's all");
	return;
}

void menu() {
	printf("a menu of a fake depository\n");
	Sleep(1500);
	while (1) {
		system("cls");
		printf("1.display the list\n");
		printf("2.warehouse\n");
		printf("3.outbound\n");
		printf("4.exit\n");
		printf("press esc to return or exit\n");
		printf("special thanks to baidu,which provides with ");
		printf("english supporting");
		char menu_ch = _getch();
		switch (menu_ch) {
		case '1':
			display();
			break;
		case '2':
			warehouse();
			break;
		case '3':
			outbound();
			break;
		case '4':
		case 27:
			system("cls");
			printf("thanks!");
			return;
		default:
			break;
		}
	}
	return;
}
