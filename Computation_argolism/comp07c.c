/* ルンゲ・クッタ法による1階常微分方程式の数値解法 */
/* 外力項のある人口増加モデルのシミュレーション */

#include <stdio.h>
#include <math.h>     /* 数学関数のヘッダファイルの読み込み */
#include <GL/freeglut.h>  /* OpenGL/freeGLUTのヘッダファイルの読み込み */

#define W_WIDTH  800  /* 画面の幅(width)[ピクセル] */
#define W_HEIGHT 400  /* 画面の高さ(height)[ピクセル] */

#define X0  -1.0  /* x軸の左端(最小値) */
#define X1  31.0  /* x軸の右端(最大値) */
#define Y0  -0.5  /* y軸の下端(最小値) */
#define Y1   2.0  /* y軸の上端(最大値) */

/* 微分方程式f(t, x)の定義 */
double f( double a, double c, double u0, double w, double t, double x )
{
  double r;

  r = a * ( c - x ) * x + u0 * sin( w * t );

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
      glVertex2d( i,  0.1 );
    }

    /* y軸の目盛線 */
    for( i = (int) Y0; i <= (int) Y1; i++ ) {  /* 1刻みでY0からY1まで */
      glVertex2d( 0.0, i );
      glVertex2d( 0.3, i );  /* 画面の縦横比に応じて長さを調節 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */
}

/* 微分方程式の数値解のグラフを描画する関数 */
void display( void )
{
  double t, dt, x, x0, t0, t_end;
  double k1, k2, k3, k4;
  double a, c, u0, w;

  glViewport( 0, 0, W_WIDTH, W_HEIGHT ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(全画面表示) */

  display_xy_axis( );  /* xy軸と目盛線を描画  */

  /* 微分方程式の数値解のグラフを描画 */
  a = 1.0;  /* パラメータの設定 */
  c = 1.0;  /* パラメータの設定 */
  u0 = 0.3; /* 外力項のパラメータ(大きさ)設定 */
  w = 1.5;  /* 外力項のパラメータ(周波数)設定 */
  x0 = 0.1;  /* 初期値の設定 */

  printf( "パラメータ： a = %f\n", a );
  printf( "パラメータ： c = %f\n", c );
  printf( "外力項のパラメータ(大きさ)： u0 = %f\n", u0 );
  printf( "外力項のパラメータ(周波数)：  w = %f\n", w );
  printf( "初期値： x0 = %f\n", x0 );

  dt = 1.0e-3;   /* 時間のきざみ幅の設定*/
  t0 = 0.0;      /* シミュレーションの初期時刻の設定 */
  t_end = 30.0;  /* シミュレーションの終了時刻の設定 */

  /* 微分方程式の数値解を計算しながら折れ線で描画 */
  glColor3f( 1.0, 0.0, 0.0 );  /* 線の色を赤に設定 */
  glLineWidth( 2 );            /* 線の太さを2ピクセルに設定 */

  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    x = x0;  /* 初期値の設定 */

    for( t = t0; t <= t_end; t += dt ) { /* 時間tの値をdt刻みで0からt_endまで変化 */
      glVertex2d( t, x );         /* 数値解を頂点座標として設定 */

      k1 = f( a, c, u0, w, t, x ) * dt;                        /* 1段目(開始点での傾きを利用) */
      k2 = f( a, c, u0, w, t + 0.5 * dt, x + 0.5 * k1 ) * dt;  /* 2段目(中点1での傾きを利用) */
      k3 = f( a, c, u0, w, t + 0.5 * dt, x + 0.5 * k2 ) * dt;  /* 3段目(中点2での傾きを利用) */
      k4 = f( a, c, u0, w, t + dt, x + k3 ) * dt;              /* 4段目(終点での傾きを利用) */
      x += ( k1 + 2.0 * k2 + 2.0 * k3 + k4 ) / 6.0;  /* ルンゲ・クッタ法 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */


  glFlush( );          /* コマンドバッファにたまっている未実行の命令を実行 */
}

int main( int argc, char *argv[] )
{

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

