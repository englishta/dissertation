/* 台形公式による数値積分の計算精度 */
#include <stdio.h>
#include <math.h>

/* 被積分関数f(x)の定義 */
double f( double x )
{
  double r;

  r = exp(x); /* 被積分関数f(x)の式 */

  return r;
}


int main ( void )
{
  int n, N;
  double s, dx, x, a, b, error, s_exact;

  a = 0.0;  /* 積分範囲[a,b]の始点の設定 */
  b = 1.0;  /* 積分範囲[a,b]の終点の設定 */
  N = 100;  /* 積分区間の分割数の設定 */

  dx = ( b - a ) / (double) N;  /* 積分区間のきざみ幅 */

  printf( "積分区間： [a,b] = [%f, %f]\n", a, b );
  printf( "分割数： N = %d\n", N );
  printf( "きざみ幅： dx = %e  log10(dx) = %f\n", dx, log10( dx ) );

  /* 台形公式による数値積分(配布資料の式(7.5)) */
  s = ( f( a ) + f ( b ) ) / 2.0;  /* 積分区間の両端での値をsに代入 */
  for( n = 1; n < N; n++ ) {       /* n=1～N-1番目の微小区間に関して */
    x = a + n * dx;     /* n番目の微小区間のxの値 */
    s += f( x );        /* 各微小区間での関数f(x)の値をsに加算 */
  }
  s *= dx;       /* 関数f(x)の各点での和に微小区間の幅dxを掛ける */

  s_exact = M_E - 1.0; /* 定積分の正確な値 */
  printf( "積分値： 台形公式 = %.15e\n         正確な値 = %.15e\n", s, s_exact );
  error = fabs( s - s_exact );  /* 計算誤差 */
  printf( "計算誤差： ΔS = %e  log10(ΔS) = %f\n", error, log10( error ) );

  return 0;
}

