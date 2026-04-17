#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> //방향키 입력
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>

int arr[17][17] = { 0 };
int len = 0;
int point = 0;
int max_point = 0;

int re() {
    Sleep(1);
    srand((unsigned int)time(NULL));
    int ranx = rand() % len;
    int rany = rand() % len;
    if (arr[rany][ranx] != 0) return re();

    arr[rany][ranx] = 2;
    check();

    print();
    return 0;
}

int print() {
    system("cls");

    printf("\n\n");
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (arr[i][j] == 0) {
                if (len > 10) printf("%3c ", '-');
                else printf("%5c ", '-');
            }

            else {
                if (len > 10) printf("%3d ", arr[i][j]);
                else printf("%5d ", arr[i][j]);
            }
        }
        if (len > 10) printf("\n");
        else printf("\n\n");
    }
    printf("\n\nyour point : %d\n", point);

    push();
    return 0;
}


int check() {
    int full = 1;
    int end = 0;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (arr[i][j] == 0) {
                full = 0;
                break;
            }
            else if (arr[i][j] >= 2048) {
                full = 2;
                break;
            }
        }
    }

    if (full==1) {
        printf("\n\n==============Game Over!!==============\n");
        end = 1;
        
    }

    else if (full == 2) {
        printf("\n\n==============You Win!!==============\n");
        end = 1;
    }

    if (end) {
        if (max_point < point) {
            printf("!!!!!New record!!!!!");
            max_point = point;
        }
        printf("your point : %d\n", point);
        printf("max point : %d\n", max_point);

        printf("play again???\n y/n : ");


        char answer[2]={'\0'};
        gets(answer);

        if (answer[0] == 'y') {
            for (int i = 0; i < len; i++) {
                for (int j = 0; j < len; j++) arr[i][j] = 0;
            }
            point = 0;

            start();
        }

        else if (answer[0] == 'n') exit(0);
    }

    return 0;

}

int start() {
    printf("원하는 칸 수를 입력하시오(3~16) : ");
    scanf_s("%d", &len);

    if (len < 3 || len>16) return start();
    re();
}

int push() {
    int way;
    way=_getch();

    //왼쪽으로 밀기
    if (way == 75) {
        for (int i = 0; i < len; i++) {
            int k = 0;

            for (int j = 0; j < len; j++) {
                if (arr[i][j] != 0) {
                    arr[i][k] = arr[i][j];
                    if (j != k) arr[i][j] = 0;
                    k++;
                }

                for (int j = k-1; j >= 0; j--) {
                    if (arr[i][j] == arr[i][j - 1]) {
                        point += arr[i][j - 1];
                        arr[i][j - 1] *= 2;
                        arr[i][j] = 0;

                        for (int n = j; n < k - 1; n++) {;
                            arr[i][n] = arr[i][n + 1];
                            arr[i][n + 1] = 0;
                        }
                        j++;
                        k--;
                    }
                }

            }
        }

    }


    //오른쪽으로 밀기
    else if (way == 77) {
        for (int i = 0; i < len; i++) {
            int k = 0;

            for (int j = 0; j < len; j++) {
            if (arr[i][len-1 - j] != 0) {
                arr[i][len-1 - k] = arr[i][len - 1 - j];
                if (j != k) arr[i][len - 1 - j] = 0;
                    k++;
                }

                for (int j = k-1; j >= 0; j--) {
                    if (arr[i][len - 1 - j] == arr[i][len - 1 - (j - 1)]) {
                        point += arr[i][len - 1 - (j - 1)];
                        arr[i][len - 1 - (j - 1)] *= 2;
                        arr[i][len - 1 - j] = 0;

                        for (int n = j; n < k - 1; n++) {
                            arr[i][len - 1 - n] = arr[i][len - 1 - (n + 1)];
                            arr[i][len - 1 - (n + 1)] = 0;
                        }
                        j++;
                        k--;
                     }
                }

            }
        }
        
    }

    //아래로 밀기
    else if (way == 80) {
        for (int i = 0; i < len; i++) {
            int k = 0;
            for (int j = 0; j < len; j++) {
                if (arr[len-1 - j][i] != 0) {
                    arr[len-1 - k][i] = arr[len - 1 - j][i];
                    if (j != k) arr[len - 1 - j][i] = 0;
                    k++;
                }

                for (int j = k-1; j >= 0; j--) {
                    if (arr[len - 1 - j][i] == arr[len - 1 - (j - 1)][i]) {
                        point += arr[len - 1 - (j - 1)][i];
                        arr[len - 1 - (j - 1)][i] *= 2;
                        arr[len - 1 - j][i] = 0;

                        for (int n = j; n < k - 1; n++) {
                            arr[len - 1 - n][i] = arr[len - 1 - (n + 1)][i];
                            arr[len - 1 - (n + 1)][i] = 0;
                        }
                        j++;
                        k--;
                    }
                }

            }
        }
        
    }

    //위로 밀기
    else if (way == 72) {
        for (int i = 0; i < len; i++) {
            int k = 0;
            for (int j = 0; j < len; j++) {
                if (arr[j][i] != 0) {
                    arr[k][i] = arr[j][i];
                    if (j != k) arr[j][i] = 0;
                    k++;
                }
            }

            for (int j = k-1; j >= 0; j--) {
                if (arr[j][i] == arr[j - 1][i]) {
                    point += arr[j - 1][i];
                    arr[j - 1][i] *= 2;
                    arr[j][i] = 0;

                    for (int n = j; n < k - 1; n++) {
                        arr[n][i] = arr[n + 1][i];
                        arr[n + 1][i] = 0;
                    }
                    j++;
                    k--;
                }
            }

        }

    }

    else return push();

    re();
    return 0;
}

int main() {
    start();
    return 0;
}
