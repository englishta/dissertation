/*==================================================================*/
/*  連立1次方程式の数値解法：ガウス・ジョルダン法(ピボット選択あり) */
/*==================================================================*/
#include <stdio.h>
#include <math.h>

#define N  3	/* dimension of matrix */

/*===================================================*/
/*  ガウス・ジョルダン法(ピボット選択あり)           */
/*===================================================*/
void gauss_jordan_pivot( double a[][N], double b[], double x[] )
{
  int i, j, k, m;
  double p, p_max, w;

  for( k = 0; k < N; k++ ) {

    /* ピボット選択 */
    /* 対角要素の絶対値が最大となるもの(m)を探す */
    m = k;
    p_max = fabs( a[k][k] );
    for( i = k+1; i < N; i++ ) { 
      if( fabs( a[i][k] ) > p_max ) {
	m = i;
        p_max = fabs( a[i][k] );
      }
    }

    /* 第k行(k番目の方程式)と第m行(m番目の方程式)を入れ換える */
    for( i = k; i < N; i++ ) {
      w = a[k][i];
      a[k][i] = a[m][i];
      a[m][i] = w;
    }
    w = b[k];
    b[k] = b[m];
    b[m] = w;

    /* ピボット行kの処理(対角成分を1にする) */
    p = a[k][k];
    for( j = 0; j < N; j++ ) {
      a[k][j] /= p;
    }
    b[k] /= p;

    /* ピボット行以外の処理 */
    for( i = 0; i < N; i++ ) {
      if( i != k ) {
	p = a[i][k];
        for( j = 0; j < N; j++ ) {
          a[i][j] -= a[k][j] * p;
        }
        b[i] -= b[k] * p;
      }
    }

  }

  /* 変数xの決定 */
  for( i = 0; i < N; i++ ) {
    x[i] = b[i];
  }

  return;
}

/* main関数 */
int main( void )
{
  int i, j;
  double x[N];
  double a[N][N] = { { 2.0, 4.0, 3.0 },
                     { 3.0, 6.0, 5.0 },
                     { 2.0, 7.0, 6.0 } };
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

  /* ガウス・ジョルダン法(ピボット選択あり) */
  gauss_jordan_pivot( a, b, x );

  printf( "--- x ---\n" );
  for( i = 0; i < N; i++ ) {
    printf( "x[%d] = %f\n", i, x[i] );
  }

  return 0;
}

