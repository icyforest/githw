#include<cstdio>
#include<cstdlib>
const int max_l = 1000;
bool judge_a[max_l] = {0};
int prime[max_l];
int main() {
    int cnt = 0;
    for (int i = 2; i <= max_l; i++) {
        if (!judge_a[i])
            prime[cnt++] = i;
        for (int j = 0; j < cnt && i * prime[j] <= max_l; j++) {
            judge_a[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 4; i <= 100; i += 2) {
        for (int j = 0; j < cnt && prime[j] * 2 < i; j++) {
            if (!judge_a[i - prime[j]])
                printf("%d + %d = %d\n", prime[j], i - prime[j], i);
        }
        printf("\n");
    }
    return 0;
}
