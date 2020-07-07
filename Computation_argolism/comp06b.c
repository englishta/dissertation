/* オイラー法による1階常微分方程式の数値解法の計算精度 */
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

  r = c*x0/(x0 +(c-x0)*exp(-a*c*t));

  return r;
}

int main ( void )
{
  double t, dt, x, x0, t0, t_end, dx;
  double a, c;

  a = 7.0;  /* パラメータの設定 */
  c = 1.0;  /* パラメータの設定 */
  x0 = 0.1;  /* 初期値の設定 */

  printf( "パラメータ： a = %f\n", a );
  printf( "パラメータ： c = %f\n", c );
  printf( "初期値： x0 = %f\n", x0 );

  /* オイラー法による1階常微分方程式の数値解法 */
  dt = 1.0e-10;  /* 時間のきざみ幅の設定*/
  t0 = 0.0;     /* シミュレーションの初期時刻の設定 */
  t_end = 1.0;  /* シミュレーションの終了時刻の設定 */

  x = x0;  /* 初期値の設定 */
  for( t = t0; t <= t_end; t += dt ) {  /* 時間tの値をdt刻みでt0からt_endまで変化 */
    x += f( a, c, t, x ) * dt;  /* オイラー法 */
  }

  dx = fabs( f_exact( a, c, t, x0 ) - x );  /* 計算誤差 */
  printf( "時間のきざみ幅： dt = %e  log10(dt) = %f\n", dt, log10( dt ) );
  printf( "計算誤差： dx = %e  log10(dx) = %f\n", dx, log10( dx ) );

  return 0;
}

