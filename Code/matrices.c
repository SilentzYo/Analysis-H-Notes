#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    int rows;
    int cols;
    double** data;
} Matrix;

Matrix* createMatrix(int rows, int cols) {
    Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
    if (mat == NULL) {
        printf("Memory allocation failed for matrix structure\n");
        return NULL;
    }
    
    mat->rows = rows;
    mat->cols = cols;
    
    mat->data = (double**)malloc(rows * sizeof(double*));
    if (mat->data == NULL) {
        printf("Memory allocation failed for matrix rows\n");
        free(mat);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        mat->data[i] = (double*)malloc(cols * sizeof(double));
        if (mat->data[i] == NULL) {
            printf("Memory allocation failed for matrix columns\n");
            for (int j = 0; j < i; j++) {
                free(mat->data[j]);
            }
            free(mat->data);
            free(mat);
            return NULL;
        }
        
        for (int j = 0; j < cols; j++) {
            mat->data[i][j] = 0.0;
        }
    }
    
    return mat;
}

void freeMatrix(Matrix* mat) {
    if (mat == NULL) return;
    
    if (mat->data != NULL) {
        for (int i = 0; i < mat->rows; i++) {
            if (mat->data[i] != NULL) {
                free(mat->data[i]);
            }
        }
        free(mat->data);
    }
    
    free(mat);
}

void inputMatrix(Matrix* mat) {
    if (mat == NULL) return;
    
    printf("Enter the elements of the %dx%d matrix row by row:\n", mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            scanf("%lf", &mat->data[i][j]);
        }
    }
}

void randomMatrix(Matrix* mat) {
    if (mat == NULL) return;
    
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            mat->data[i][j] = (double)(rand() % 101);
        }
    }
}

void printMatrix(Matrix* mat) {
    if (mat == NULL) {
        printf("Matrix is NULL\n");
        return;
    }
    
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%7.2f ", mat->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

Matrix* addMatrices(Matrix* mat1, Matrix* mat2, bool add) {
    if (mat1 == NULL || mat2 == NULL) {
        printf("One or both matrices are NULL\n");
        return NULL;
    }
    
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        printf("Matrices are not same dimension\n");
        return NULL;
    }
    
    Matrix* result = createMatrix(mat1->rows, mat1->cols);
    if (result == NULL) return NULL;
    
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            if (add) {
                result->data[i][j] = mat1->data[i][j] + mat2->data[i][j];
            } else {
                result->data[i][j] = mat1->data[i][j] - mat2->data[i][j];
            }
        }
    }
    
    return result;
}

Matrix* multiplyMatrices(Matrix* mat1, Matrix* mat2) {
    if (mat1 == NULL || mat2 == NULL) {
        printf("One or both matrices are NULL\n");
        return NULL;
    }
    
    if (mat1->cols != mat2->rows) {
        printf("Matrix dimensions do not match for multiplication\n");
        return NULL;
    }
    
    Matrix* result = createMatrix(mat1->rows, mat2->cols);
    if (result == NULL) return NULL;
    
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat2->cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < mat1->cols; k++) {
                sum += mat1->data[i][k] * mat2->data[k][j];
            }
            result->data[i][j] = sum;
        }
    }
    
    return result;
}

Matrix* transposeMatrix(Matrix* mat) {
    if (mat == NULL) {
        printf("Matrix is NULL\n");
        return NULL;
    }
    
    Matrix* result = createMatrix(mat->cols, mat->rows);
    if (result == NULL) return NULL;
    
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            result->data[j][i] = mat->data[i][j];
        }
    }
    
    return result;
}

double determinant2x2(Matrix* mat) {
    if (mat == NULL || mat->rows != 2 || mat->cols != 2) {
        printf("Matrix must be 2x2 for this determinant function\n");
        return 0.0;
    }
    
    return (mat->data[0][0] * mat->data[1][1]) - (mat->data[0][1] * mat->data[1][0]);
}

int main() {
    srand(time(NULL));

    Matrix* matA = createMatrix(2, 3);
    Matrix* matB = createMatrix(3, 2);
    
    randomizeMatrix(matA);
    randomizeMatrix(matB);
    
    printf("Matrix A:\n");
    printMatrix(matA);
    
    printf("Matrix B:\n");
    printMatrix(matB);
    
    Matrix* matC = multiplyMatrices(matA, matB);
    printf("Matrix A * B:\n");
    printMatrix(matC);
    
    Matrix* matD = createMatrix(2, 2);
    matD->data[0][0] = 4.0;
    matD->data[0][1] = 7.0;
    matD->data[1][0] = 2.0;
    matD->data[1][1] = 6.0;
    
    printf("Matrix D:\n");
    printMatrix(matD);

    double det = determinant2x2(matD);
    printf("Determinant of Matrix D: %.2f\n", det);

    Matrix* matE = transposeMatrix(matA);
    printf("Transpose of Matrix A:\n");
    printMatrix(matE);
   
    freeMatrix(matA);
    freeMatrix(matB);
    freeMatrix(matC);
    freeMatrix(matD);
    freeMatrix(matE);
    
    return 0;
}