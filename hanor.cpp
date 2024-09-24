#include<cstdio>
#include<cstdlib>
void hanor_move(char a, char b) {
	printf("%c -> %c\n", a, b);
	return;
}
void hanor_main(int num, char st, char md, char ed) {
	if (num == 1) {
		hanor_move(st, ed);
		return;
	}
	hanor_main(num - 1, st, ed, md);
	hanor_move(st, ed);
	hanor_main(num - 1, md, st, ed);
	return;
}
int main() {
	int n;
	scanf_s("%d", &n);
	int A = 'A', B = 'B', C = 'C';
	hanor_main(n, A, B, C);
	return 0;
}