/* 擬似乱数を用いた数値積分法 */
#include <stdio.h>
#include <math.h>     /* 数学関数のヘッダファイルの読み込み */
#include <stdlib.h>   /* 乱数を発生させる関数rand、srandを利用するために必要なヘッダファイル */
#include <GL/freeglut.h>  /* OpenGL/freeGLUTのヘッダファイルの読み込み */
 
#define N  10000 /* サンプル数(的当ての回数) */

#define W_WIDTH   800  /* 画面の幅(width)[ピクセル] */
#define W_HEIGHT  600  /* 画面の高さ(height)[ピクセル] */

#define X0  -1.0  /* x軸の左端(最小値) */
#define X1   7.0  /* x軸の右端(最大値) */
#define Y0  -0.5  /* y軸の下端(最小値) */
#define Y1   5.0  /* y軸の上端(最大値) */

/* 被積分関数f(x)の定義 */
double f( double x )
{
  double r;

  r = 4.0 * exp( - x / 5.0 );  /* 被積分関数f(x)の式 */

  return r;
}

/* 文字列を描画する関数 */
void drawString2D( double x, double y, char *str )
{
  glRasterPos2d( x, y );   /* 文字列の先頭の描画位置を(x,y)に設定 */

  while( *str != '\0' ) {  /* 文字が終了コードでなければ */
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *str );  /* 24ポイントのTimes Romanビットマップフォントで1文字ずつ描画 */
    str++;  /* 1文字分先に進める */
  }
}

/* xy軸と目盛線を描画する関数 */
void display_xy_axis( double x0, double x1, double y0, double y1, double dx, double dy )
{
  double r, s;

  glColor3f( 0.0, 0.0, 0.0 );  /* 線の色を黒に設定 */

  glBegin( GL_LINES ); /* 図形描画タイプの設定開始: 線分で描画 */
    /* x軸 */
    glVertex2d( x0, 0.0 );
    glVertex2d( x1, 0.0 ); 

    /* y軸 */
    glVertex2d( 0.0, y0 );
    glVertex2d( 0.0, y1 );

    /* x軸の目盛線 */
    for( r = (int) x0; r <= (int) x1; r += dx ) {  /* dx刻みでx0からx1まで */
      glVertex2d( r,  0.0 );
      glVertex2d( r,  0.1 );
    }

    /* y軸の目盛線 */
    s = ( x1 - x0 ) / ( y1 - y0 ); /* 画面の縦横比の計算 */
    for( r = (int) y0; r <= (int) y1; r += dy ) {  /* dy刻みでy0からy1まで */
      glVertex2d( 0.0, r );
      glVertex2d( 0.1 * s, r );  /* 画面の縦横比に応じて長さを調節 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */
}

void display( void )
{
  double x;

  /* グラフ(x軸にx、y軸にyの値)の投影設定 */ 
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* 正射影変換の範囲設定 */
  glViewport( 20, 20, W_WIDTH-40, W_HEIGHT-40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  display_xy_axis( X0, X1, Y0, Y1, 1.0, 1.0 );         /* xy軸と目盛線を描画  */
  drawString2D( X1/2, Y0/2, "x" );           /* x軸にxとラベルを描画 */
  drawString2D( X0/2, Y1/2, "y" );           /* y軸にyと描画 */
  drawString2D( X0/2, Y0/2, "0" );           /* 原点(0,0)に0と描画 */

  glColor3f( 0.0, 0.0, 0.0 );  /* 線の色を黒に設定 */
  glBegin( GL_LINE_STRIP ); /* 図形描画タイプの設定開始: 線分で描画 */
    for( x = X0; x <= X1; x += 0.05 )  {  /* 関数y=f(x)の描画 */
      glVertex2d( x, f(x) );
    }
  glEnd( );  /* 図形描画タイプの設定終了 */

  glFlush( );          /* コマンドバッファにたまっている未実行の命令を実行 */
}

/* main関数 */
int main( int argc, char *argv[] )
{
  int m, n;
  double a, b, x, y, ymax, s;

  /* グラフィックスの初期設定 */
  glutInit( &argc, argv );             /* OpenGL/GLUT環境の初期化 */
  glutInitDisplayMode ( GLUT_RGBA );   /* ディスプレイモード(色の指定やその処理の方法)の設定 */
  glutInitWindowSize ( W_WIDTH, W_HEIGHT );  /* 画面サイズの設定 */
  glutInitWindowPosition( 100, 100 );  /* モニタ左上から(100,100)ピクセルの位置に表示 */
  glutCreateWindow( argv[0] );         /* main関数の引数で渡される実行ファイル名を画面の名前とする*/

  glClearColor ( 1.0, 1.0, 1.0, 0.0 );  /* 画面の背景色を白に設定 */
  glClear( GL_COLOR_BUFFER_BIT ); /* カラーバッファをクリア(背景を塗りつぶす) */

  /* ワールド座標系→正規化デバイス座標系への投影設定 */ 
  glMatrixMode( GL_PROJECTION );       /* 投影変換モードに設定 */

  /* グラフ(x軸にx、y軸にy)の投影設定 */ 
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* 正射影変換の範囲設定 */
  glViewport( 20, 20, W_WIDTH-40, W_HEIGHT-40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  glPointSize( 3 );       /* 点の大きさを3×3ピクセルに設定 */
  glBegin( GL_POINTS );   /* 図形描画タイプの設定開始: 点で描画 */

  a = 1.0;     /* 積分区間[a,b]の始点の設定 */
  b = 5.0;     /* 積分区間[a,b]の終点の設定 */
  ymax = 4.0;  /* 的当ての高さ方向の範囲は[0,ymax] */

  printf( "---<< 擬似乱数を用いた数値積分法 >>---\n" );
  printf( "積分範囲：[a, b] = [%f, %f]\n", a, b );
  printf( "ymax = %f\n\n", ymax );

  srand(1);  /* 整数値乱数の初期値(初項)を設定 */
  m = 0;     /* 点(x,y)が当たりである回数を数えるカウンタの初期値設定 */

  for( n = 0; n < N; n++ )  {  /* 的当てをN回繰り返す */
    x = (double) rand( ) / RAND_MAX;  /* 区間[0,1]上の実数値一様乱数を生成しxに代入 */
    x = a + ( b - a ) * x;            /* 区間[a,b]上の実数値一様乱数に変換 */

    y = (double) rand( ) / RAND_MAX;  /* 区間[0,1]上の実数値一様乱数を生成しyに代入 */
    y = ymax * y;                     /* 区間[0,ymax]上の実数値一様乱数に変換 */

    if( y < f( x ) ) { /* もし点(x,y)が当たりであれば */
      m++;             /* 当たりのカウンタmを1加算 */
      glColor3f(1.0, 0.0, 0.0);	/* 描画する点の色を赤に設定 */
    }
    else {  /* もし点(x,y)がはずれであれば */
      glColor3f(0.0, 0.0, 1.0);	/* 描画する点の色を青に設定 */
    }

    glVertex2d( x, y );       /* グラフ：点(x,y)を頂点座標として設定 */
  }

  glEnd( );  /* 図形描画タイプの設定終了 */

  printf( "%d回のうち点(x,y)があたりである回数は%d回です\n", N, m);
  s = m * ( b - a ) * ymax / (double) N;     /* 定積分の近似値 */
  printf( "定積分の近似値：s = %.15f\n", s );

  /* グラフを描画 */
  glutDisplayFunc( display );

  glutMainLoop( );

  return 0;
}

