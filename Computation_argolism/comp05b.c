/* 最急降下法による最適化 */

#include <stdio.h>
#include <math.h>     /* 数学関数のヘッダファイルの読み込み */
#include <GL/freeglut.h>  /* OpenGL/freeGLUTのヘッダファイルの読み込み */

#define W_WIDTH  600  /* 画面の幅(width)[ピクセル] */
#define W_HEIGHT 400  /* 画面の高さ(height)[ピクセル] */

double gx[500], gy[500];   /* グローバル変数(どの関数の中でも使用可能): グラフ描画のためのデータ保存用変数 */
int n_step;                /* グローバル変数(どの関数の中でも使用可能): 最急降下法の繰り返し回数 */
double gx0, gx1, gy0, gy1; /* グローバル変数(どの関数の中でも使用可能): グラフ描画の範囲(gx0,gy0)～(gx1,gy1)の値 */

/* 評価関数f(x[])の定義 */
double f( double x[] )
{
  double r;

  r = x[0]*x[0] +x[0]*x[1] + 2*x[1]*x[1] - exp(-3*x[1]*x[1]);

  return r;
}

/* 評価関数fの点x[]における勾配ベクトルdx[]の計算 */
void df( double x[], double dx[] )
{
  dx[0] = 2*x[0] + x[1];  /* df(x[])/dx[0] */
  dx[1] = x[0] + 4*x[1] + 6 * x[1] * exp(-3*x[1]*x[1]);  /* df(x[])/dx[1] */

  return;
}

/* xy軸と目盛線を描画する関数 */
void display_xy_axis( void )
{
  int i;

  glColor3f( 0.0, 0.0, 0.0 );  /* 線の色を黒に設定 */

  glBegin( GL_LINES ); /* 図形描画タイプの設定開始: 線分で描画 */
    /* x軸 */
    glVertex2d( gx0, 0.0 );
    glVertex2d( gx1, 0.0 ); 

    /* y軸 */
    glVertex2d( 0.0, gy0 );
    glVertex2d( 0.0, gy1 );

    /* x軸の目盛線 */
    for( i = (int) gx0; i <= (int) gx1; i++ ) {  /* 1刻みでgx0からgx1まで */
      glVertex2d( i,  0.0 );
      glVertex2d( i,  0.5 );
    }

    /* y軸の目盛線 */
    for( i = (int) gy0; i <= (int) gy1; i++ ) {  /* 1刻みでgy0からgy1まで */
      glVertex2d( 0.0, i );
      glVertex2d( 0.1, i );
    }

  glEnd( );  /* 図形描画タイプの設定終了 */
}

void display( void )
{
  int k;

  glViewport( 0, 0, W_WIDTH, W_HEIGHT ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(全画面表示) */

  display_xy_axis( );  /* xy軸と目盛線を描画  */

  /* 最急降下法の初期値(gx[0], gy[0])を大きな点でプロット */
  glPointSize( 8 );            /* 点の大きさを8×8ピクセルに設定 */
  glColor3f( 0.0, 0.0, 1.0 );  /* 点の色を青に設定 */

  glBegin( GL_POINTS );   /* 図形描画タイプの設定開始: 点で描画 */
    glVertex2d( gx[0], gy[0] );     /* 初期値の座標を設定 */
  glEnd( );  /* 図形描画タイプの設定終了 */

  glColor3f( 1.0, 0.0, 0.0 );  /* 点の色を赤に設定 */

  glBegin( GL_POINTS );   /* 図形描画タイプの設定開始: 点で描画 */

    for( k = 1; k <= n_step; k++ ) {
      glVertex2d( gx[k], gy[k] );     /* 各ステップの値の座標を設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */

  /* 最急降下法の各ステップの値(gx[k], gy[k])を線で繋げる */
  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( k = 0; k <= n_step; k++ ) {
      glVertex2d( gx[k], gy[k] );     /* 各ステップの値の座標を設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */

  glFlush( );          /* コマンドバッファにたまっている未実行の命令を実行 */
}

int main( int argc, char *argv[] )
{
  int k, n_max;
  double x[2], dx[2];
  double alpha, delta;
  double x_min, x_max, y_min, y_max;

  delta = 1.0e-6;  /* 最急降下法の収束判定値 */
  alpha = 2.0e-1;  /* 最急降下法のステップ幅の調整値 */
  n_max = 300;     /* 繰り返しの最大回数(安全対策) */

  /* 初期値の設定 */
  k = 0;
  x[0] = 8.0;
  x[1] = -5.0;

  gx[k] = x[0];  /* グラフ描画のためのデータ保存 */
  gy[k] = x[1];  /* グラフ描画のためのデータ保存 */

  df( x, dx );  /* 勾配ベクトルdx[]の計算 */
  printf( "%d回目: F( %.15f, %.15f ) = %e\n", k, x[0], x[1], f(x) );

  while( sqrt( dx[0] * dx[0] + dx[1] * dx[1] ) > delta && k < n_max ) {

    k++;
    x[0] -= alpha * dx[0];  /* 次の点に移動 */
    x[1] -= alpha * dx[1];  /* 次の点に移動 */
    printf( "%d回目: F( %.15f, %.15f ) = %e\n", k, x[0], x[1], f(x) );

    gx[k] = x[0];  /* グラフ描画のためのデータ保存 */
    gy[k] = x[1];  /* グラフ描画のためのデータ保存 */

    df( x, dx );  /* 勾配ベクトルdx[]の計算 */
  }

  n_step = k;  /* 最急降下法の繰り返し回数をn_stepに保存 */

  /* 最急降下法の各ステップの値(gx[k], gy[k])の最小値と最大値を求める */
  x_min = gx[0];
  x_max = gx[0];
  y_min = gy[0];
  y_max = gy[0];
  for( k = 1; k <= n_step; k++ ) {
    if( gx[k] < x_min )       x_min = gx[k];
    else if( gx[k] > x_max )  x_max = gx[k];
    if( gy[k] < y_min )       y_min = gy[k];
    else if( gy[k] > y_max )  y_max = gy[k];
  }

  /* グラフ描画の範囲(gx0,gy0)～(gx1,gy1)の値を少し大きめに設定 */
  gx0 = x_min - ( x_max - x_min ) / 4.0; 
  gx1 = x_max + ( x_max - x_min ) / 4.0; 
  gy0 = y_min - ( y_max - y_min ) / 4.0; 
  gy1 = y_max + ( y_max - y_min ) / 4.0; 

  /* グラフと解の位置を描画 */
  glutInit( &argc, argv );             /* OpenGL/GLUT環境の初期化 */
  glutInitDisplayMode ( GLUT_RGBA );   /* ディスプレイモード(色の指定やその処理の方法)の設定 */
  glutInitWindowSize ( W_WIDTH, W_HEIGHT );  /* 画面サイズの設定 */
  glutInitWindowPosition( 100, 100 );  /* モニタ左上から(100,100)ピクセルの位置に表示 */
  glutCreateWindow( argv[0] );         /* main関数の引数で渡される実行ファイル名を画面の名前とする*/

  glClearColor ( 1.0, 1.0, 1.0, 0.0 );  /* 画面の背景色を白に設定 */
  glClear( GL_COLOR_BUFFER_BIT );       /* カラーバッファをクリア(背景を塗りつぶす) */

  /* ワールド座標系→正規化デバイス座標系への投影設定 */ 
  glMatrixMode( GL_PROJECTION );         /* 投影変換モードに設定 */
  glLoadIdentity( );                     /* 変換行列を単位行列で初期化 */
  glOrtho( gx0, gx1, gy0, gy1, -1.0, 1.0 );  /* 正射影変換の範囲設定(gx0<x<gx1, gy0<y<gy1) */

  glutDisplayFunc( display );

  glutMainLoop( );

  return 0;
}

