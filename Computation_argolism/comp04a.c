/* ニュートン・ラフソン法によるf(x)=0の解 */

#include <stdio.h>
#include <math.h>     /* 数学関数のヘッダファイルの読み込み */
#include <GL/freeglut.h>  /* OpenGL/freeGLUTのヘッダファイルの読み込み */

#define W_WIDTH  600  /* 画面の幅(width)[ピクセル] */
#define W_HEIGHT 400  /* 画面の高さ(height)[ピクセル] */

#define X0  -3  /* x軸の左端(最小値) */
#define X1   6  /* x軸の右端(最大値) */
#define Y0  -5  /* y軸の下端(最小値) */
#define Y1  20  /* y軸の上端(最大値) */

double x_solution;  /* グローバル変数(どの関数の中でも使用可能): main関数の中で求めた解の値を保存 */

/* 関数f(x)の定義 */
double f( double x )
{
  double r;

  r = exp(0.5*x) - 2.0*x;

  return r;
}

/* f(x)をxで微分した関数の定義 */
double df( double x )
{
  double r;

  r = 0.5 * exp(0.5*x) - 2.0;

  return r;
}

/* xy軸と目盛線を描画する関数 */
void display_xy_axis( void )
{
  int i;

  glColor3f( 0.0, 0.0, 0.0 );  /* 線の色を黒に設定 */

  glBegin( GL_LINES ); /* 図形描画タイプの設定開始: 線分で描画 */
    /* x軸 */
    glVertex2d( X0, 0.0 );
    glVertex2d( X1, 0.0 ); 

    /* y軸 */
    glVertex2d( 0.0, Y0 );
    glVertex2d( 0.0, Y1 );

    /* x軸の目盛線 */
    for( i = (int) X0; i <= (int) X1; i++ ) {  /* 1刻みでX0からX1まで */
      glVertex2d( i,  0.0 );
      glVertex2d( i,  0.5 );
    }

    /* y軸の目盛線 */
    for( i = (int) Y0; i <= (int) Y1; i++ ) {  /* 1刻みでY0からY1まで */
      glVertex2d( 0.0, i );
      glVertex2d( 0.1, i );  /* 画面の縦横比に応じて長さを調節 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */
}

/* 関数f(x)のグラフを描画する関数 */
void plot_f( void )
{
  double x, y, dx;

  dx = 0.1;   /* 曲線をプロットする刻み幅 */

  /* f(x)の曲線を折れ線で描画 */
  glColor3f( 1.0, 0.0, 0.0 );  /* 線の色を赤に設定 */
  glLineWidth( 3 );            /* 線の太さを3ピクセルに設定 */

  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( x = X0; x <= X1; x += dx ) {  /* xの値をdx刻みでX0からX1まで変化 */
      y = f( x );
      glVertex2d( x, y );     /* f(x)上の頂点座標を設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */
}

void display( void )
{
  glViewport( 0, 0, W_WIDTH, W_HEIGHT ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(全画面表示) */

  display_xy_axis( );  /* xy軸と目盛線を描画  */

  plot_f( );           /* 関数f(x)のグラフを描画 */

  /* f(x)=0の解の位置を大きな点で描画 */
  glColor3f( 0.0, 0.0, 1.0 );  /* 点の色を青に設定 */
  glPointSize( 15 );           /* 点の大きさを15×15ピクセルに設定 */

  glBegin( GL_POINTS );   /* 図形描画タイプの設定開始: 点で描画 */
    glVertex2d( x_solution, f( x_solution ) );     /* 点の座標を設定 */
  glEnd( );  /* 図形描画タイプの設定終了 */

  glFlush( );          /* コマンドバッファにたまっている未実行の命令を実行 */
}

int main( int argc, char *argv[] )
{
  int n;
  double x, dx, eps;

  eps = 1.0e-10; /* 終了判定値 */
  dx = 1.0;

  n = 0;
  x = 2;  /* 解の初期値 */
  printf( "初期値: x = %.15e f(x) = %.15e\n", x, f(x) );
  while( fabs(dx) > eps) {  /* 終了判定条件(条件式が満たされる限りwhile文を継続) */
    dx = f( x ) / df( x );
    x -= dx;  /* 解の補正 */
    n++;
    printf( "%d回目: x = %.15e  dx = %.15e  f(x) = %.15e\n", n, x, dx, f(x) );
  }
  x_solution = x;    /* 最終的な解の値をグローバル変数に代入 */
  printf( "\n最終的なf(x)=0の解\n" );
  printf( "x = %.15e  f(x) = %.15e\n", x_solution, f( x_solution ) );

  /* グラフと解の位置を描画 */
  glutInit( &argc, argv );             /* OpenGL/GLUT環境の初期化 */
  glutInitDisplayMode ( GLUT_RGBA );   /* ディスプレイモード(色の指定やその処理の方法)の設定 */
  glutInitWindowSize ( W_WIDTH, W_HEIGHT );  /* 画面サイズの設定 */
  glutInitWindowPosition( 100, 100 );  /* モニタ左上から(100,100)ピクセルの位置に表示 */
  glutCreateWindow( argv[0] );         /* main関数の引数で渡される実行ファイル名を画面の名前とする*/

  glClearColor ( 1.0, 1.0, 1.0, 0.0 );  /* 画面の背景色を白に設定 */
  glClear( GL_COLOR_BUFFER_BIT ); /* カラーバッファをクリア(背景を塗りつぶす) */

  /* ワールド座標系→正規化デバイス座標系への投影設定 */ 
  glMatrixMode( GL_PROJECTION );       /* 投影変換モードに設定 */
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* 正射影変換の範囲設定(X0<x<X1, Y0<y<Y1) */

  glutDisplayFunc( display );

  glutMainLoop( );

  return 0;
}

