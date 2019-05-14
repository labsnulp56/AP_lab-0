#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define R 4
#define S 4

void getMatrix(double matrix[][S]);
void printMatrix(double matrix[][S], int deletedRows);
int checkMatrixIteration(double matrix[][S]);
int checkMatrixRecursion(double matrix[][S], int beginIndex, int deletedRows);
int checkMatrixRecursionCount(double matrix[][S], int beginIndex, int deletedRows, int counter);
int checkRow(double row[S]);
void copy(double row1[], double row2[]);

int main(int argc, const char * argv[]) {
	double matrix[R][S];
	getMatrix(matrix);
	//int deletedRows = checkMatrixIteration(matrix);
	int deletedRows = checkMatrixRecursion(matrix, 0, 0);
	//puts("Count of recursions:");
	//int deletedRows = checkMatrixRecursionCount(matrix, 0, 0, 1);
	printMatrix(matrix, deletedRows);
	printf("%d deleted row(s)", deletedRows);
	getchar(); getchar();
	return 0;
}


int checkMatrixIteration(double matrix[][S]) {
	int deletedRows = 0;
	for (int i = 0; i < R - deletedRows; ) {
		if (!checkRow(matrix[i])) {
			for (int j = i; j < R - deletedRows; j++) {
				copy(matrix[j], matrix[j + 1]);
			}
			deletedRows++;
		}
		else i++;
	}
	return deletedRows;
}

int checkRow(double row[S]) {
	double min = row[0];
	for (int i = 1; i < S; i++)
		if (row[i] < min)
			min = row[i];
	if (row[0] == min)
		return 1;
	return 0;
}

int checkMatrixRecursion(double matrix[][S], int beginIndex, int deletedRows) {
	if (R - deletedRows == beginIndex)
		return deletedRows;
	if (!checkRow(*matrix)) {
		for (int j = 0; j < R - deletedRows - beginIndex; j++) {
			copy(matrix[j], matrix[j + 1]);
		}
		deletedRows++;
		return checkMatrixRecursion(matrix, beginIndex, deletedRows);
	}
	else
		return checkMatrixRecursion(matrix + 1, beginIndex + 1, deletedRows);
}

int checkMatrixRecursionCount(double matrix[][S], int beginIndex, int deletedRows, int counter) {
	if (R - deletedRows == beginIndex)
		return deletedRows;
	if (!checkRow(*matrix)) {
		for (int j = 0; j < R - deletedRows - beginIndex; j++) {
			copy(matrix[j], matrix[j + 1]);
		}
		deletedRows++;
		printf("%d ", counter);
		counter++;
		return checkMatrixRecursionCount(matrix, beginIndex, deletedRows, counter);
	}
	else {
		printf("%d ", counter);
		counter++;
		return checkMatrixRecursionCount(matrix + 1, beginIndex + 1, deletedRows, counter);
	}

}

void copy(double row1[], double row2[]) {
	for (int i = 0; i < S; i++) {
		row1[i] = row2[i];
	}
}

void getMatrix(double matrix[][S]) {
	printf("Enter your matrix:\n");
	for (int i = 0; i < R; i++)
		for (int j = 0; j < S; j++) {
			scanf("%lf", &matrix[i][j]);
		}
}

void printMatrix(double matrix[][S], int deletedRows) {
	printf("\nYour matrix:\n");
	for (int i = 0; i < R - deletedRows; i++) {
		for (int j = 0; j < S; j++) {
			printf("%.3lf ", matrix[i][j]);
		}
		puts("");
	}
}