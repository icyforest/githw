#include<cstdio>
#include<cstdlib>
#include<ctime>
const int max_l = 1000;
int main() {
    clock_t start,end;
    double time_spent;
    start = clock();
    bool judge[max_l] = {0};
    int prime[max_l];
    int cnt = 0;
    for(int i = 2;i <= max_l;i ++) {
        if(!judge[i])
            prime[cnt++] = i;
        for(int j = 0;j < cnt && i * prime[j] <= max_l;j ++) {
            judge[i * prime[j]] = true;
            if(i % prime[j] == 0)
                break;
        }
    }
    end = clock();
    for(int i = 0;i < cnt;i ++) {
        printf("%d ",prime[i]);
    }
    printf("\n%.10lf",(double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}

