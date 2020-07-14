/* 擬似乱数を用いた円周率πの計算(一様擬似乱数の生成関数は自作の場合)  */
#include <stdio.h>
#include <math.h>     /* 数学関数のヘッダファイルの読み込み */
#include <GL/freeglut.h>  /* OpenGL/freeGLUTのヘッダファイルの読み込み */

#define A  48271   /* 線形合同法のパラメータ：掛ける数 */
#define C  0       /* 線形合同法のパラメータ：足す数 */
#define M  2147483647   /* 線形合同法のパラメータ：割る数 (2の31乗-1) */

#define N  1000 /* サンプル数(的当ての回数) */
 
#define W_WIDTH   600  /* 画面の幅(width)[ピクセル] */
#define W_HEIGHT  600  /* 画面の高さ(height)[ピクセル] */

#define X0  -0.2  /* x軸の左端(最小値) */
#define X1   1.2  /* x軸の右端(最大値) */
#define Y0  -0.2  /* y軸の下端(最小値) */
#define Y1   1.2  /* y軸の上端(最大値) */

/* グローバル変数 (どの関数の中でも使用可能) */
unsigned int X;    /* 線形合同法で生成される非負の整数値一様擬似乱数列 */

/*====================================================*/
/* 線形合同法による整数値一様擬似乱数の生成関数(自作) */
/*====================================================*/
unsigned int myrand( void )
{
  X = ( A * X + C ) % M;

  return X;
}

/*====================================================*/
/* 整数値一様擬似乱数の初期値を設定する関数(自作)     */
/*====================================================*/
void mysrand( unsigned int x0 )
{
  X = x0;
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
      glVertex2d( r,  0.05 );
    }

    /* y軸の目盛線 */
    s = ( x1 - x0 ) / ( y1 - y0 ); /* 画面の縦横比の計算 */
    for( r = (int) y0; r <= (int) y1; r += dy ) {  /* dy刻みでy0からy1まで */
      glVertex2d( 0.0, r );
      glVertex2d( 0.05 * s, r );  /* 画面の縦横比に応じて長さを調節 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */
}

void display( void )
{
  /* グラフ(x軸にx、y軸にyの値)の投影設定 */ 
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* 正射影変換の範囲設定 */
  glViewport( 20, 20, W_WIDTH-40, W_HEIGHT-40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  display_xy_axis( X0, X1, Y0, Y1, 0.2, 0.2 );         /* xy軸と目盛線を描画  */
  drawString2D(  0.5, -0.15, "x" );      /* x軸にxとラベルを描画 */
  drawString2D( -0.15, 0.5, "y" );       /* y軸にyと描画 */
  drawString2D( -0.1, -0.1, "0" );       /* 原点(0,0)に0と描画 */
  drawString2D(  1.0, -0.1, "1" );       /* (1,0)に1と描画 */
  drawString2D( -0.1,  1.0, "1" );       /* (0,1)に1と描画 */

  glFlush( );          /* コマンドバッファにたまっている未実行の命令を実行 */
}

/* main関数 */
int main( int argc, char *argv[] )
{
  int i, m, n;
  double x, y, pi;

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

  printf( "\n---<< 乱数を用いて円周率πを計算する >>---\n" );

  glPointSize( 3 );      /* 点の大きさを3×3ピクセルに設定 */
  glBegin( GL_POINTS );  /* 図形描画タイプの設定開始: 点で描画 */

  mysrand( 1 );  /* 整数値乱数の初期値(初項)を設定 */
  m = 0;         /* 点(x,y)が4分円の内部に入った回数を数えるカウンタの初期値設定 */

  for( n = 0; n < N; n++ )  {  /* 的当てをN回繰り返す */
    x = (double) myrand( ) / M;  /* 区間[0,1)上の実数値乱数を生成しxに代入 */
    y = (double) myrand( ) / M;  /* 区間[0,1)上の実数値乱数を生成しyに代入 */

    if( x * x + y * y < 1.0 ) { /* もし点(x,y)が4分円の内部に入れば */
      m++;    /* 当たりのカウンタmを1加算 */
      glColor3f(1.0, 0.0, 0.0);	/* 描画する点の色を赤に設定 */
    }
    else {  /* もし点(x,y)が4分円の外にあれば */
      glColor3f(0.0, 0.0, 1.0);	/* 描画する点の色を青に設定 */
    }

    glVertex2d( x, y );       /* グラフ：点(x,y)を頂点座標として設定 */
  }

  glEnd( );  /* 図形描画タイプの設定終了 */

  printf( "%d回のうち点(x,y)が4分円の内部に入った回数は%d回です\n", N, m);
  pi = 4.0 * m / (double) N;  /* 円周率πの近似値 */
  printf( "円周率πの近似値：4*%d/\%d = %.15f\n", m, N, pi );
  printf( "円周率πの正確な値：π = %.15f\n", M_PI );

  /* グラフを描画 */
  glutDisplayFunc( display );

  glutMainLoop( );

  return 0;
}

