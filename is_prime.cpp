#include<iostream>
const int max_l = 100000;
int number[max_l];
int main() {
	long long a;
	bool b = false;
	std::cin >> a;
	for (int i = 2; i * i < a; i++) {
		if (a % i == 0) {
			b = true;
			break;
		}
	}
	if (b == true)
		printf("n");
	else
		printf("y");
	return 0;
}