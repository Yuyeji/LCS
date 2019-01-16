#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS
void LCS_Length(char *X, char *Y);
void print_lcs(int i, int j);

int m, n; //���� X,Y�迭�� ����
char *X;
char *Y;
char **b; //�밢��, ��, �Ʒ� ������ ���� �迭

int main(void) {
	FILE* f; // ����
	int startTime = 0, endTime = 0; //�ð������� ���� ����
	float gap; //�ð������� ���� ����

	f = fopen("simple_lcs2.txt", "rt"); //���� ����

	if (f == NULL) {
		printf("������ ������ �ʽ��ϴ�.");
		exit(1);
	}

	if (feof(f) == 0) { //������ ù��° ���� �о�´�
		fscanf(f, "%d", &m);
	}
	X = (int*)realloc(X, sizeof(int)*(m)); //mũ�⸸ŭ X realloc
	fscanf(f, "%s", X); //���ڿ��� X�� �޾ƿ�
	
	fscanf(f, "%d", &n);
	Y = (int*)realloc(Y, sizeof(int)*(n)); //nũ�⸸ŭ Y realloc
	fscanf(f, "%s", Y); //���ڿ��� Y�� �޾ƿ�

	startTime = clock();

	printf("X = <%s>\nY = <%s>\n", X,Y); //X�� Y���
	LCS_Length(X, Y); //LCS�˰��� ����

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("���� �ð� : %f\n", gap);

	fclose(f); //���� �ݱ�

	system("pause"); // �׽�Ʈ ���� ����.
}

void LCS_Length(char *X, char *Y) {
	char **c; 
	int i, j; //�ݺ����� ���� ����

	/*c, b�迭 ���� ���μ��� m+1, n+1��ŭ �Ҵ����ش�*/
	c = (char**)malloc(sizeof(char*)*(m+1));
	b = (char**)malloc(sizeof(char*)*(m + 1));
	for (int i = 0; i <= m; i++) {
		c[i] = (char*)malloc(sizeof(char) * (n+1));
		b[i] = (char*)malloc(sizeof(char) * (n + 1));
	}

	/*���μ����� ù���� ��� 0���� �ʱ�ȭ���ش�.*/
	for (i = 0; i <= m;i++) {
		c[i][0] = 0;
		b[i][0] = 0;
	}
	for (i = 0; i <= n;i++) {
		c[0][i] = 0;
		b[0][i] = 0;
	}

	/*�ݺ����� ���� ��쿡 ���� �˸°� ó��*/
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (X[i - 1] == Y[j - 1]) { //���ڰ� ���� ���
				//LCS�� ������ ���ڸ� �ϳ� ���� ���� X��, Y���� LCS�� ���� ���ڱ��� 1�� �߰��ѰͰ� ����.
				c[i][j] = c[i - 1][j - 1] + 1; 
				b[i][j] = 'c'; //corss
			}
			else if (c[i - 1][j] >= c[i][j - 1]) { //c[i - 1][j]���� Ŭ ���
				//LCS�� ������ ���ڸ� �ϳ� ���� ���� X�� ���� Y���� LSC�� ����
				c[i][j] = c[i - 1][j]; 
				b[i][j] = 'u'; //up
			}
			else {
				//LCS�� ���� X�� ������ ���ڸ� �ϳ� ���� ���� Y���� LCS�� ����
				c[i][j] = c[i][j - 1]; 
				b[i][j] = 'd'; //down
			}
		}
	}

	/*LCS ���*/
	printf("LCS = <");
	print_lcs(m, n);
	printf(">\n");
}

/*LCS��� �Լ�*/
void print_lcs(int i, int j) {
	if (i == 0 || j == 0) //i�� j�� ������ ����
		return;
	if (b[i][j] == 'c') { //�밢���� ���
		print_lcs(i - 1, j - 1); //�� ���ڰ� ��� ������ ���ڸ� �ϳ� ���� ���� ��ͷ� ����
		printf("%c", X[i - 1]); //X[i-1]�� ���
	}
	else if (b[i][j] == 'u') { //up�� ���
		print_lcs(i - 1, j); //������ ���ڸ� �ϳ� ���� ���� X�� ����Y
	}
	else {
		print_lcs(i, j - 1); //���� X�� ������ ���ڸ� �ϳ� ���� ���� Y
	}
}