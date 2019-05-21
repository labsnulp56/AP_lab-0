#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define R 4
#define S 4

void getMatrix(double matrix[][S]);
void printMatrix(double matrix[][S], int deletedRows);
int checkMatrixIteration(double matrix[][S]);
int checkMatrixRecursion(double matrix[][S], int beginIndex, int deletedRows);
int checkMatrixRecursionCount(double matrix[][S], int beginIndex, int deletedRows, int counter);
//int checkRow(double row[S]);
int checkRow(double * row, size_t size);
void copy(double row1[], double row2[]);

int main(int argc, const char * argv[]) {
	system("color F1");
	double matrix[R][S];
	getMatrix(matrix);
	int deletedRows = checkMatrixIteration(matrix);
	//int deletedRows = checkMatrixRecursion(matrix, 0, 0);
	//puts("Count of recursions:");
	//int deletedRows = checkMatrixRecursionCount(matrix, 0, 0, 1);
	printMatrix(matrix, deletedRows);
	printf("%d deleted row(s)", deletedRows);
	getchar(); getchar();
	return 0;
}
/*
1 2 3 4 
5 4 3 2
8 7 6 5
5 6 8 9
*/

/*
к-сть рядків матриці обчислюється як частка від ділення
кількості даних у списку ініціалізації на відому к-сть
елементів в одному рядку матриці
*/
int checkMatrixIteration(double matrix[][S]) {									 																	
	int deletedRows = 0;
	for (int i = 0; i < R - deletedRows; ) {
		if (!checkRow(matrix[i], S)) {
			for (int j = i; j < R - deletedRows; j++) {
				copy(matrix[j], matrix[j + 1]);
			}
			deletedRows++;
		}
		else i++;
	}
	return deletedRows;
}

//int checkRow(double row[S]) {
//	double min = row[0];
//	for (int i = 1; i < S; i++)
//		if (row[i] < min)
//			min = row[i];
//	if (row[0] == min)
//		return 1;
//	return 0;
//}

int checkRow(double * row, size_t size) {
	return (size < 2) ? 1 : (row[size - 1] < row[0]) ? 0 : checkRow(row, size - 1);									
}

int checkMatrixRecursion(double matrix[][S], int beginIndex, int deletedRows) {
	if (R - deletedRows == beginIndex)
		return deletedRows;
	if (!checkRow(*matrix, S)) {												 // logical NOT. True only if the operand is 0
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
	if (!checkRow(*matrix, S)) {
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
