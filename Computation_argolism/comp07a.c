/* 修正オイラー法による1階常微分方程式の数値解法の計算精度 */
#include <stdio.h>
#include <math.h>

/* 微分方程式f(t, x)の定義 */
double f( double a, double c, double t, double x )
{
  double r;

  r = a * ( c - x ) * x;

  return r;
}

/* 微分方程式の厳密解の定義 */
double f_exact( double a, double c, double t, double x0 )
{
  double r;

  r =  c * x0 / ( x0 + ( c - x0 ) * exp( - a * c * t ) );

  return r;
}

int main ( void )
{
  double t, dt, x, x0, t0, t_end, dx;
  double k1, k2;
  double a, c;

  a = 7.0;  /* パラメータの設定 */
  c = 1.0;  /* パラメータの設定 */
  x0 = 0.1;  /* xの初期値の設定 */

  printf( "パラメータ： a = %f\n", a );
  printf( "パラメータ： c = %f\n", c );
  printf( "初期値： x0 = %f\n", x0 );

  /* 修正オイラー法による1階常微分方程式の数値解法 */
  dt = 1.0e-8;  /* 時間のきざみ幅の設定*/
  t0 = 0.0;     /* シミュレーションの初期時刻の設定 */
  t_end = 1.0;  /* シミュレーションの終了時刻の設定 */

  x = x0;  /* 初期値の設定 */
  for( t = t0; t <= t_end; t += dt ) {
    k1 = f( a, c, t, x ) * dt;                        /* 1段目(開始点での傾きを利用) */
    k2 = f( a, c, t + 0.5 * dt, x + 0.5 * k1 ) * dt;  /* 2段目(中点での傾きを利用) */
    x += k2;  /* 修正オイラー法 */
  }

  dx = fabs( f_exact( a, c, t, x0 ) - x );  /* 計算誤差 */
  printf( "時間のきざみ幅： dt = %e  log10(dt) = %f\n", dt, log10( dt ) );
  printf( "計算誤差： dx = %e  log10(dx) = %f\n", dx, log10( dx ) );

  return 0;
}

