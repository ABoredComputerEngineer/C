#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RANGE 10
typedef struct Matrix {
     int **vals;
     size_t row;
     size_t col;
} Matrix;


Matrix *new_matrix( int row, int col ){
     Matrix *new = calloc( 1, sizeof(Matrix) );
     new->vals = calloc( row, sizeof(int *) );
     for ( int i = 0; i < row; i++ ){
          new->vals[i] = calloc( col, sizeof(int) );
     }
     new->row = row;
     new->col = col;
     return new;
}

Matrix *mat_mul( Matrix *matA, Matrix *matB ){
     // Calculates matA * matB 
     if ( matA->col != matB->row ){
          printf("Invalid dimensions for multiplication\n");
          return NULL;
     }
     Matrix *matC = new_matrix( matA->row, matB->col );
     for ( size_t i = 0; i < matA->row; i++ ){
          for( size_t j = 0; j < matB->col; j++ ){
               matC->vals[i][j] = 0;
               for ( size_t k = 0; k < matA->col; k++ ){
                    matC->vals[i][j] += matA->vals[i][k] * matB->vals[k][i];
               }
          }
     }
     return matC;
}

Matrix *mat_add(Matrix *matA, Matrix *matB ){
     if ( ( matA->row != matB->row ) || ( matA->col != matB->col ) ){
          printf("Invalid dimensions for matrix addition!\n");
          return NULL;
     }
     Matrix *matC = new_matrix( matA->row , matB->col );
     for ( size_t i = 0; i < matA->row; i++ ){
          for( size_t j = 0; j < matB->col; j++ ){
               matC->vals[i][j] = matA->vals[i][j] + matB->vals[i][j];
          }
     }
     return matC;
}

Matrix *rand_matrix( int row, int col ){
     Matrix *new = new_matrix( row , col );
     int **x = new->vals;
     for ( size_t i = 0; i < row; i++ ){
          for ( size_t j = 0; j < col ; j++ ){
               x[i][j] = rand() % RANGE;
          }
     }
     return new;
}

void display_matrix( Matrix *mat ){
     for ( size_t i = 0; i < mat->row ; i++ ){
          for ( size_t j = 0; j < mat->col; j++ ){
               printf("%5d ",mat->vals[i][j]);
          }
          printf("\n");
     }
}

int main(void){
     srand(time(NULL));
     Matrix *A = rand_matrix( 3 , 3 );
     Matrix *B = rand_matrix( 3 , 3 );
     Matrix *C = mat_mul( A , B );
     Matrix *D = mat_add( A, B );
     printf("Matrix A: \n" );
     display_matrix(A);
     printf("Matrix B: \n" );
     display_matrix(B);
     if ( C ){
          printf("Matrix C: \n" );
          display_matrix(C);
     }
     if ( D ){
          printf("Matrix D: \n" );
          display_matrix(D);
     }
     return 1;
}
