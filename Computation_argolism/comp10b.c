/* シンプソン公式による数値積分の計算精度 */
#include <stdio.h>
#include <math.h>

/* 被積分関数f(x)の定義 */
double f( double x )
{
  double r;

  r = exp( x ); /* 被積分関数f(x)の式 */

  return r;
}

int main ( void )
{
  int k, N;
  double s, s_odd, s_even, x, dx, a, b, error, s_exact;

  a = 0.0;  /* 積分範囲[a,b]の始点の設定 */
  b = 1.0;  /* 積分範囲[a,b]の終点の設定 */
  N = 100;  /* 積分区間の分割数(偶数)の設定 */

  dx = ( b - a ) / (double) N;  /* 積分区間のきざみ幅 */

  printf( "積分区間： [a,b] = [%f, %f]\n", a, b );
  printf( "分割数： N = %d\n", N );
  printf( "きざみ幅： dx = %e  log10(dx) = %f\n", dx, log10( dx ) );

  /* 奇数番目の分点の値の和の計算 */
  s_odd = 0.0;  /* 奇数番目の分点の値の和の初期値 */
  for( k = 0; k <=  N/2-1; k++ ) {
    x = a + ( 2 * k + 1 ) * dx;  /* 奇数番目の分点 */
    s_odd += f( x );             /* 奇数番目の分点の値の和 */
  }

  /* 端点を除く偶数番目の分点の値の和の計算 */
  s_even = 0.0;  /* 端点を除く偶数番目の分点の値の和の初期値 */
  for( k = 1; k <= N/2-1 ; k++ ) {
    x = a + 2 * k * dx;     /* 偶数番目の分点 */
    s_even += f( x );       /* 端点を除く偶数番目の分点の値の和 */
  }

  /* シンプソン公式による数値積分 */
  s = ( f( a ) + f( b ) + 4.0 * s_odd + 2.0 * s_even ) * dx / 3.0;

  s_exact = M_E - 1.0; /* 定積分の正確な値 */
  printf( "積分値： シンプソ\ン公式 = %.15e\n               正確な値 = %.15e\n", s, s_exact );
  error = fabs( s - s_exact );  /* 計算誤差 */
  printf( "計算誤差： ΔS = %e  log10(ΔS) = %f\n", error, log10( error ) );

  return 0;
}

