/* 最小2乗法によるフィッティング */

#include <stdio.h>
#include <math.h>     /* 数学関数のヘッダファイルの読み込み */
#include <GL/freeglut.h>  /* OpenGL/freeGLUTのヘッダファイルの読み込み */

#define N  2    /* フィッティングパラメータの個数 = 係数行列の次元 */

#define W_WIDTH  600  /* 画面の幅(width)[ピクセル] */
#define W_HEIGHT 400  /* 画面の高さ(height)[ピクセル] */

double x[100], y[100];     /* グローバル変数(どの関数の中でも使用可能): ファイルから読み込んだデータ(x,y)を格納 */
int n_data;                /* グローバル変数(どの関数の中でも使用可能): ファイルから読み込んだデータの個数 */
double a, b;               /* グローバル変数(どの関数の中でも使用可能): 最小2乗法で決めたパラメータの値 */
double gx0, gx1, gy0, gy1; /* グローバル変数(どの関数の中でも使用可能): グラフ描画の範囲(gx0,gy0)～(gx1,gy1)の値 */

/* フィッティング関数f(x,a,b)の定義 */
double f( double arg_x, double arg_a, double arg_b )
{
  double r;

  r = arg_a * arg_x + arg_b;

  return r;
}

/*==========================================================*/
/*  連立1次方程式の数値解法：ガウス消去法(ピボット選択あり) */
/*==========================================================*/
void gauss_elimination_pivot( double arg_a[][N], double arg_b[], double arg_x[] )
{
  int i, j, k, m;
  double p_max, w;

  for( k = 0; k < N; k++ ) {

    /* ピボット選択 */
    /* 対角要素の絶対値が最大となるもの(m)を探す */
    m = k;
    p_max = fabs( arg_a[k][k] );
    for( i = k+1; i < N; i++ ) { 
      if( fabs( arg_a[i][k] ) > p_max ) {
        m = i;
        p_max = fabs( arg_a[i][k] );
      }
    }

    /* 第k行(k番目の方程式)と第m行(m番目の方程式)を入れ換える */
    for( i = k; i < N; i++ ) {
      w = arg_a[k][i];
      arg_a[k][i] = arg_a[m][i];
      arg_a[m][i] = w;
    }
    w = arg_b[k];
    arg_b[k] = arg_b[m];
    arg_b[m] = w;

    /* 係数行列aと係数ベクトルbの置き換え */
    for( j = k+1; j < N; j++ ) {
      arg_a[k][j] /= arg_a[k][k];
    }
    arg_b[k] /= arg_a[k][k];

    for( i = k+1; i < N; i++ ) {
      for( j = k+1; j < N; j++ ) {
        arg_a[i][j] -= arg_a[k][j] * arg_a[i][k];
      }
      arg_b[i] -= arg_b[k] * arg_a[i][k];
    }

  }

  /* 変数xの決定 */
  for( i = N-1; i >= 0; i-- ) {
    arg_x[i] = arg_b[i];
    for( j = i+1; j < N; j++ ) {
      arg_x[i] -= arg_a[i][j] * arg_x[j];
    }
  }

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

/* グラフを描画する関数 */
void plot_graph( void )
{
  int i;
  double gx, gy, dx;

  /* データ(x[i], y[i])を大きな点で描画 */
  glColor3f( 1.0, 0.0, 0.0 );  /* 点の色を赤に設定 */
  glPointSize( 10 );           /* 点の大きさを10×10ピクセルに設定 */

  glBegin( GL_POINTS );   /* 図形描画タイプの設定開始: 点で描画 */

    for( i = 0; i < n_data; i++ ) {
      glVertex2d( x[i], y[i] );     /* 各データ点の座標を設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */

  /* フィッティング曲線を折れ線で描画 */
  glColor3f( 0.0, 0.0, 1.0 );  /* 線の色を青に設定 */
  glLineWidth( 3 );            /* 線の太さを3ピクセルに設定 */
  dx = 0.1;   /* フィッティング曲線をプロットする刻み幅 */

  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( gx = gx0; gx <= gx1; gx += dx ) {  /* gxの値をdx刻みでgx0からgx1まで変化 */
      gy = f( gx, a, b );       /* y座標の値を計算 */
      glVertex2d( gx, gy );     /* フィッティング曲線上の頂点座標を設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */
}

void display( void )
{
  glViewport( 0, 0, W_WIDTH, W_HEIGHT ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(全画面表示) */

  display_xy_axis( );  /* xy軸と目盛線を描画  */
  plot_graph( );       /* グラフを描画 */

  glFlush( );          /* コマンドバッファにたまっている未実行の命令を実行 */
}

int main( int argc, char *argv[] )
{
  int i;
  double p[N][N];   /* 係数行列p */
  double q[N], x_sol[N];  /* 係数ベクトルq, 解ベクトルx_sol */
  double x_min, x_max, y_min, y_max;
  FILE *fp;

  /* ファイルからデータ(x,y)を読む込む */
  fp = fopen( "comp05aData.txt", "r" );

  if( fp == NULL ) {  /* 安全対策：入力ファイルのオープンに失敗した場合 */
    printf( "入力ファイルのオープンに失敗しました\n" );
    return 0;
  }

  /* データを配列x[i], y[i]に格納しながら読み込む */
  i = 0;
  while( fscanf( fp, "%lf %lf", &x[i], &y[i] ) != EOF ) {
    i++;
  }

  fclose( fp );

  n_data = i;  /* データの個数をn_dataに保存 */

  /* 連立1次方程式の係数行列p[N][N]と係数ベクトルq[N]の計算 */
  p[0][0] = 0.0;
  p[0][1] = 0.0;
  q[0] = 0.0;
  q[1] = 0.0;
  for( i = 0; i < n_data; i++ ) {
    p[0][0] += x[i]*x[i];
    p[0][1] += x[i];
    q[0] += x[i]*y[i];
    q[1] += y[i];
  }
  p[1][0] = p[0][1];
  p[1][1] = ( double ) n_data;

  /* 連立1次方程式の数値解法をガウス消去法(ピボット選択あり)で解く */
  gauss_elimination_pivot( p, q, x_sol );

  /* 最小2乗法での結果 */
  a = x_sol[0];
  b = x_sol[1];
  printf( "%d個のデータに対する最小2乗法: y = a x + b\na = %f\nb = %f\n", n_data, a, b );

  /* データ(x[i], y[i])の最小値と最大値を求める */
  x_min = x[0];
  x_max = x[0];
  y_min = y[0];
  y_max = y[0];
  for( i = 1; i < n_data; i++ ) {
    if( x[i] < x_min )       x_min = x[i];
    else if( x[i] > x_max )  x_max = x[i];
    if( y[i] < y_min )       y_min = y[i];
    else if( y[i] > y_max )  y_max = y[i];
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
  glMatrixMode( GL_PROJECTION );       /* 投影変換モードに設定 */
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( gx0, gx1, gy0, gy1, -1.0, 1.0 );  /* 正射影変換の範囲設定(gx0<x<gx1, gy0<y<gy1) */

  glutDisplayFunc( display );

  glutMainLoop( );

  return 0;
}

