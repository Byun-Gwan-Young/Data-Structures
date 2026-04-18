#include <stdio.h>
#include <stdlib.h>

#include "sparseMatrix.h"

sparseMatrix* createSparseMatrix(int row, int col) {
	return createArrayList(row * col);
}

int addElementSparseMatrix(sparseMatrix* sm, int row, int col, int value) {
	int size;
	size = sizeArrayList(sm);

	insertArrayList(sm, size,
		(elementArrayList) {row, col, value});

	return 1; // [수정] return 문 추가
}

int printSparseMatrix(sparseMatrix* sm) {
	printf("희소행렬입니다\n");

	printArrayList(sm);

	return 1; // [수정] return 문 추가
}

sparseMatrix* addSparseMatrix(sparseMatrix* sm1, sparseMatrix* sm2) {
	sparseMatrix* smResult = createArrayList(100);

	// [수정] <= → < 로 변경 (off-by-one 오류 수정 / 핵심 크래시 원인)
	for (int i = 0; i < sizeArrayList(sm1); i++) {
		elementArrayList nonZeroOfSM1
			= getItemArrayList(sm1, i);

		int j;
		for (j = 0; j < sizeArrayList(sm2); j++) {
			elementArrayList nonZeroOfSM2
				= getItemArrayList(sm2, j);

			if (nonZeroOfSM1.col == nonZeroOfSM2.col &&
				nonZeroOfSM1.row == nonZeroOfSM2.row) {
				insertArrayList(smResult, sizeArrayList(smResult), (elementArrayList){
					nonZeroOfSM1.row,
					nonZeroOfSM1.col,
					nonZeroOfSM1.value + nonZeroOfSM2.value
				});

				break;
			}
		}

		if (j == sizeArrayList(sm2)) {
			insertArrayList(smResult, sizeArrayList(smResult),
				nonZeroOfSM1);
		}
	}

	// [수정] sm2에만 있는 원소 결과에 추가 (기존 코드에서 누락)
	for (int j = 0; j < sizeArrayList(sm2); j++) {
		elementArrayList nonZeroOfSM2 = getItemArrayList(sm2, j);

		int found = 0;
		for (int i = 0; i < sizeArrayList(sm1); i++) {
			elementArrayList nonZeroOfSM1 = getItemArrayList(sm1, i);
			if (nonZeroOfSM1.row == nonZeroOfSM2.row &&
				nonZeroOfSM1.col == nonZeroOfSM2.col) {
				found = 1;
				break;
			}
		}

		if (!found) {
			insertArrayList(smResult, sizeArrayList(smResult), nonZeroOfSM2);
		}
	}

	return smResult;
}
