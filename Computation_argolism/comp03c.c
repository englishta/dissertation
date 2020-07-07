/* テーラー展開による関数近似とグラフ描画 */

#include <math.h>     /* 数学関数のヘッダファイルの読み込み */
#include <GL/freeglut.h>  /* OpenGL/freeGLUTのヘッダファイルの読み込み */

#define W_WIDTH  800  /* 画面の幅(width)[ピクセル] */
#define W_HEIGHT 400  /* 画面の高さ(height)[ピクセル] */

#define X0  -10  /* x軸の左端(最小値) */
#define X1   10  /* x軸の右端(最大値) */
#define Y0   -3  /* y軸の下端(最小値) */
#define Y1    3  /* y軸の上端(最大値) */

#define M   0  /* テーラー展開の展開次数((2M+1)次まで) */

/* テーラー展開による第(2m+1)項までのsin(x)関数の近似値 */
double Taylor_exp( double x, int m )
{
  int i, n;
  double a, y;

  y = 0.0;
  for( n = 0; n <= m; n++ ) {
    /* a=(2n+1)!=1×2×...×(2n+1)の計算 */
    a = 1.0;
    for( i = 1; i <= 2*n+1; i++ ) {
      a *= (double) i;
    }
   /* 第(2n+1)項の計算 */
    y += pow( -1.0, n ) * pow( x, 2*n+1 ) / a;
  }

  return y;
}

/* xy軸と目盛線を描画する関数 */
void display_xy_axis( void )
{
  int i;

  glColor3f( 0.0, 0.0, 0.0 );  /* 線の色を黒に設定 */

  glBegin( GL_LINES ); /* 図形描画タイプの設定開始: 線分で描画 */
    /* x軸 */
    glVertex2f( X0, 0.0 );
    glVertex2f( X1, 0.0 ); 

    /* y軸 */
    glVertex2f( 0.0, Y0 );
    glVertex2f( 0.0, Y1 );

    /* x軸の目盛線 */
    for( i = (int) X0; i <= (int) X1; i++ ) {  /* 1刻みでX0からX1まで */
      glVertex2f( i,  0.0 );
      glVertex2f( i,  0.1 );
    }

    /* y軸の目盛線 */
    for( i = (int) Y0; i <= (int) Y1; i++ ) {  /* 1刻みでY0からY1まで */
      glVertex2f( 0.0, i );
      glVertex2f( 0.1 * W_WIDTH / W_HEIGHT, i );  /* 画面の縦横比に応じて長さを調節 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */
}

/* sin(x)の曲線とテーラー展開による近似曲線を描画する関数 */
void plot_sin( void )
{
  double x, y, dx;

  dx = 0.1;   /* 曲線をプロットする刻み幅 */

  /* sin(x)の曲線を折れ線で描画 */
  glColor3f( 1.0, 0.0, 0.0 );  /* 線の色を赤に設定 */

  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( x = X0; x <= X1; x += dx ) {  /* xの値をdx刻みでX0からX1まで変化 */
      y = sin( x );
      glVertex2f( x, y );     /* sin(x)上の頂点座標を設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */

  /* テーラー展開による近似曲線を折れ線で描画 */
  glColor3f( 0.0, 0.0, 1.0 );  /* 線の色を青に設定 */

  glBegin( GL_LINE_STRIP );    /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( x = X0; x <= X1; x += dx ) {  /* xの値をdx刻みでX0からX1まで変化 */
      y = Taylor_exp( x, M );  /* 第(2M+1)次までのテーラー展開による近似値の計算 */
      glVertex2f( x, y );      /* 近似曲線上の頂点座標を設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */
}

void display( void )
{
  glViewport( 0, 0, W_WIDTH, W_HEIGHT ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(全画面表示) */

  display_xy_axis( );  /* xy軸と目盛線を描画  */

  plot_sin( );         /* sin(x)の曲線とテーラー展開による近似曲線を描画 */

  glFlush( );          /* コマンドバッファにたまっている未実行の命令を実行 */
}

int main( int argc, char *argv[] )
{
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

