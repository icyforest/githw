//vector,启动します。(算了吧
//10000个以内/int限定
#include<cstdio>
#include<cstdlib>
const int max = 10000;
typedef struct dot_l {
	int num;
	struct dot_l * nex;
}dot;
dot lis[max];
//int cnt = 0;
bool jud_c = 0;
int read() {
	int jud = 1,num = 0;
	char ch = getchar();
	if (ch == 'e') {
		jud_c = 1;
		return 0;
	}
	if (ch == '-') {
		jud = -1;
		ch = getchar();
	}
	while (ch <= '9' && ch >= '0') {
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num;
}
void op(void) {
	printf("now you can input numbers,but the number must below 9999");
	printf(", the size must be below 2147483647");
	printf("and above -2147483648\n");
	printf("when there's no number to input,press e and enter\n");
	return;
}
void tip1(int c) {
	printf("now please input 2 words to operate the ll\n");
	printf("please remember the former should no less than 1 ");
	printf("and the latter should be no more than %d\n", c);
	return;
}
void tip2(void) {
	printf("so you wanna find a number\n");
	printf("remember the number should be no more than 2147483647 ");
	printf("and above -2147483648\n");
	return;
}
void ope1(dot *heat) {
	tip1(heat->num);
	int stt, edt, c_tt = 0;
	bool judd = 0;
	scanf_s("%d%d", &stt, &edt);
	for (dot* now = heat, *he_t = NULL, *he_t1 = NULL, *pre = NULL, *ne = NULL;
		c_tt <= heat->num;
		now = ne, c_tt++) {
		ne = now->nex;
		if (judd) {
			now->nex = pre;
			pre = now;
		}
		if (c_tt == edt) {
			he_t1->nex = ne;
			he_t->nex = now;
			break;
		}
		if (c_tt + 1 == stt) {
			he_t = now;
			he_t1 = now->nex;
			pre = now->nex;
		}
		if (c_tt == stt) {
			judd = 1;
		}
	}
	return;
}
void ope2(dot *heat) {
	tip2();
	int fi,c_tt = 1;
	scanf_s("%d", &fi); 
	for (dot* i = heat->nex; i != heat; i = i->nex,c_tt ++) {
		if(i->num == fi)
			printf("%d\n", c_tt);
	}
	printf("oops,there's no more %d\n",fi);
	return;
}
void ope3(dot* heat) {
	for (dot* i = heat->nex; i != heat; i = i->nex) {
		printf("%d ", i->num);
	}
	printf("\n");
	return;
}
int main() {
	dot* hea = &lis[0];
	int st, ed, c_t = 0;
	bool jud = 0;
	lis[0].num = 0;
	op();
	while (1) {
		int tojust = read();
		if (jud_c)
			break;
		lis[lis[0].num].nex = &lis[lis[0].num + 1];
		lis[++lis[0].num].num = tojust;
		lis[hea->num].nex = hea;
	}
	while (1) {
		printf("input 1 to reverse\ninput 2 to search\n");
		printf("input 3 to check the linklist\n");
		printf("input other letters to end the program\n");
		getchar();
		char ch = getchar();
		if (ch == '1') {
			ope1(hea);
		}
		else if (ch == '2') {
			ope2(hea);
		}
		else if (ch == '3') {
			ope3(hea);
		}
		else
			break;
	}
/*	
	tip1(hea->num);
	scanf_s("%d%d", &st, &ed);
	for (dot* now = hea, *he_t = NULL, *he_t1 = NULL, *pre = NULL, *ne = NULL;
		c_t <= hea->num ; 
		now = ne,c_t ++) {
			ne = now->nex;
		if (jud) {
			now->nex = pre;
			pre = now;
		}
		if (c_t == ed) {
			he_t1->nex = ne;
			he_t->nex = now;
			break;
		}
		if (c_t + 1 == st) {
			he_t = now;
			he_t1 = now->nex;
			pre = now->nex;
		}
		if (c_t == st) {
			jud = 1;
		}
	}*/
	/*
	for (dot* i = hea->nex; i != hea ; i = i->nex) {
		printf("%d ", i->num);
	}*/
	return 0;
}
