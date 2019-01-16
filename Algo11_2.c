#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS
void LCS_Length(char *X, char *Y);
void print_lcs(int i, int j);

int m, n; //각각 X,Y배열의 길이
char *X;
char *Y;
char **b; //대각선, 위, 아래 정보를 담을 배열

int main(void) {
	FILE* f; // 파일
	int startTime = 0, endTime = 0; //시간측정을 위한 변수
	float gap; //시간측정을 위한 변수

	f = fopen("simple_lcs2.txt", "rt"); //파일 열기

	if (f == NULL) {
		printf("파일이 열리지 않습니다.");
		exit(1);
	}

	if (feof(f) == 0) { //파일의 첫번째 값만 읽어온다
		fscanf(f, "%d", &m);
	}
	X = (int*)realloc(X, sizeof(int)*(m)); //m크기만큼 X realloc
	fscanf(f, "%s", X); //문자열을 X에 받아옴
	
	fscanf(f, "%d", &n);
	Y = (int*)realloc(Y, sizeof(int)*(n)); //n크기만큼 Y realloc
	fscanf(f, "%s", Y); //문자열을 Y에 받아옴

	startTime = clock();

	printf("X = <%s>\nY = <%s>\n", X,Y); //X와 Y출력
	LCS_Length(X, Y); //LCS알고리즘 실행

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("측정 시간 : %f\n", gap);

	fclose(f); //파일 닫기

	system("pause"); // 테스트 보기 위해.
}

void LCS_Length(char *X, char *Y) {
	char **c; 
	int i, j; //반복문을 위한 변수

	/*c, b배열 각각 가로세로 m+1, n+1만큼 할당해준다*/
	c = (char**)malloc(sizeof(char*)*(m+1));
	b = (char**)malloc(sizeof(char*)*(m + 1));
	for (int i = 0; i <= m; i++) {
		c[i] = (char*)malloc(sizeof(char) * (n+1));
		b[i] = (char*)malloc(sizeof(char) * (n + 1));
	}

	/*가로세로의 첫줄은 모두 0으로 초기화해준다.*/
	for (i = 0; i <= m;i++) {
		c[i][0] = 0;
		b[i][0] = 0;
	}
	for (i = 0; i <= n;i++) {
		c[0][i] = 0;
		b[0][i] = 0;
	}

	/*반복문을 돌며 경우에 따라 알맞게 처리*/
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (X[i - 1] == Y[j - 1]) { //문자가 같을 경우
				//LCS는 마지막 문자를 하나 줄인 수열 X와, Y간의 LCS에 공통 문자길이 1을 추가한것과 같다.
				c[i][j] = c[i - 1][j - 1] + 1; 
				b[i][j] = 'c'; //corss
			}
			else if (c[i - 1][j] >= c[i][j - 1]) { //c[i - 1][j]값이 클 경우
				//LCS는 마지막 문자를 하나 줄인 수열 X와 수열 Y간의 LSC와 동일
				c[i][j] = c[i - 1][j]; 
				b[i][j] = 'u'; //up
			}
			else {
				//LCS는 수열 X와 마지막 문자를 하나 줄인 수열 Y간의 LCS와 동일
				c[i][j] = c[i][j - 1]; 
				b[i][j] = 'd'; //down
			}
		}
	}

	/*LCS 출력*/
	printf("LCS = <");
	print_lcs(m, n);
	printf(">\n");
}

/*LCS출력 함수*/
void print_lcs(int i, int j) {
	if (i == 0 || j == 0) //i와 j가 같으면 리턴
		return;
	if (b[i][j] == 'c') { //대각선일 경우
		print_lcs(i - 1, j - 1); //두 인자값 모두 마지막 문자를 하나 줄인 값을 재귀로 돌림
		printf("%c", X[i - 1]); //X[i-1]값 출력
	}
	else if (b[i][j] == 'u') { //up일 경우
		print_lcs(i - 1, j); //마지막 문자를 하나 줄인 수열 X와 수열Y
	}
	else {
		print_lcs(i, j - 1); //수열 X와 마지막 문자를 하나 줄인 수열 Y
	}
}