/*==========================================================*/
/*  �A��1���������̐��l��@�F�K�E�X�����@(�s�{�b�g�I������) */
/*==========================================================*/
#include <stdio.h>
#include <math.h>

#define N  3	/* dimension of matrix */

/*===================================================*/
/*  �K�E�X�����@(�s�{�b�g�I������)                   */
/*===================================================*/
void gauss_elimination_pivot( double a[][N], double b[], double x[] )
{
  int i, j, k, m;
  double p_max, w;

  for( k = 0; k < N; k++ ) {

    /* �s�{�b�g�I�� */
    /* �Ίp�v�f�̐�Βl���ő�ƂȂ����(m)��T�� */
    m = k;
    p_max = fabs( a[k][k] );
    for( i = k+1; i < N; i++ ) { 
      if( fabs( a[i][k] ) > p_max ) {
	      m = i;
        p_max = fabs( a[i][k] );
      }
    }

    /* ��k�s(k�Ԗڂ̕�����)�Ƒ�m�s(m�Ԗڂ̕�����)����ꊷ���� */
    for( i = k; i < N; i++ ) {
      w = a[k][i];
      a[k][i] = a[m][i];
      a[m][i] = w;
    }
    w = b[k];
    b[k] = b[m];
    b[m] = w;

    /* �W���s��a�ƌW���x�N�g��b�̒u������ */
    for( j = k+1; j < N; j++ ) {
      a[k][j] /= a[k][k];
    }
    b[k] /= a[k][k];

    for( i = k+1; i < N; i++ ) {
      for( j = k+1; j < N; j++ ) {
        a[i][j] -= a[k][j] * a[i][k];
      }
      b[i] -= b[k] * a[i][k];
    }

  }

  /* �ϐ�x�̌��� */
  for( i = N-1; i >= 0; i-- ) {
    x[i] = b[i];
    for( j = i+1; j < N; j++ ) {
      x[i] -= a[i][j] *x [j];
    }
  }

  return;
}

/* main�֐� */
int main( void )
{
  int i, j;
  double x[N];
  double a[N][N] = { { 2.0, 4.0, 2.0 },
                     { 3.0, 3.0, 5.0 },
                     { 2.0, 7.0, 1000.0 } };
  double b[N] = { 4.0, 7.0, 7.0 };

  printf( "--- A ---\n" );
  for( i = 0; i < N; i++ ) {
    for( j = 0; j < N; j++ ) {
      printf( "a[%d][%d] = %f\n", i, j, a[i][j] );
    }
  }

  printf( "--- b ---\n" );
  for( i = 0; i < N; i++ ) {
    printf( "b[%d] = %f\n", i, b[i] );
  }

  /* �K�E�X�����@(�s�{�b�g�I������) */
  gauss_elimination_pivot( a, b, x );

  printf( "--- x ---\n" );
  for( i = 0; i < N; i++ ) {
    printf( "x[%d] = %f\n", i, x[i] );
  }

  return 0;
}

