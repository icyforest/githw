#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
const int max = 1000;
const int key = 10;
char str[max];
using namespace std;
int main() {
    scanf("%s",str);
    int len = strlen(str);
    for(int i = 0;i < len;i ++) {
        str[i] += key;
    }
    printf("%s\n",str);
    for(int i = 0;i < len;i ++) {
        str[i] -= key;
    }
    printf("%s",str);
    return 0;
}