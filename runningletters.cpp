#include<cstdio>
#include<cstdlib>
#include<windows.h>
const int max_l = 120;
int main() {
    char ch[max_l];
    int i = 0;
    ch[i] = getchar();
    i ++;
    while((ch[i] = getchar()) != EOF) {
        if(ch[i] == '\n')
            break;
        i += 1;
    }
    ch[i] = '\0';
    printf("%s",ch);
    int j = i;
    while(1) {
        for(;j <= max_l;j ++) {
            system("cls");
            //			printf("7");
            for(int k = 0;k < j - i;k ++)
                printf(" ");
            printf("%s",ch);
            Sleep(10);
        }
        for(;j > i;j --) {
            system("cls");
            for(int k = 0;k < j - i - 1;k ++)
                printf(" ");
            printf("%s",ch);
            Sleep(10);
        }
    }/**/
    return 0;
}

