/* 座標系と投影変換関数 */

#include <math.h>     /* 数学関数のヘッダファイルの読み込み */
#include <GL/freeglut.h>  /* OpenGL/freeGLUTのヘッダファイルの読み込み */

#define W_WIDTH  800  /* 画面の幅(width)[ピクセル] */
#define W_HEIGHT 400  /* 画面の高さ(height)[ピクセル] */

/* OpenGLでは円を描く関数がないので中心( xc, yc ), 半径rの円を描く関数を自作 */
void circle( double xc, double yc, double r )  
{
  int i;
  double x, y;

  glBegin( GL_LINE_LOOP ); /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( i = 0; i < 360; i++ ) {  /* 円周上の頂点を1度刻みで360個設定 */
      x = xc + r * cos( 2.0 * M_PI * i / 360.0 ); /* 頂点のx座標 */
      y = yc + r * sin( 2.0 * M_PI * i / 360.0 ); /* 頂点のy座標 */
      glVertex2d( x, y );                         /* 頂点の座標(x,y)を設定 */
    }

  glEnd();  /* 図形描画タイプの設定終了 */
}

/* 描画する図形を関数内に記述 */
void display( void )
{
	glViewport( 20, 20, 400, 200 );
  glColor3f( 1.0, 0.0, 1.0 );  /* 図形の色をマゼンタ(赤紫)に設定 */
  glPointSize( 25 );  /* 点の大きさを25×25ピクセルに設定 */

  glBegin( GL_POINTS ); /* 図形描画タイプの設定開始: 個々の点 */
    glVertex2f(  80.0, 75.0 );
    glVertex2f( 100.0, 75.0 );  
    glVertex2f( 120.0, 75.0 );  
  glEnd( );  /* 図形描画タイプの設定終了 */

  glColor3f( 0.8, 0.8, 0.8 );  /* 図形の色を明るい灰色に設定 */

  glBegin( GL_QUADS ); /* 図形描画タイプの設定開始: 四角形(塗りつぶし) */
    /* 四角形の4頂点を指定 */
    glVertex2f( 20.0, 20.0 );
    glVertex2f( 80.0, 20.0 );
    glVertex2f( 80.0, 50.0 );
    glVertex2f( 20.0, 50.0 );
  glEnd( );  /* 図形描画タイプの設定終了 */

  glColor3f( 1.0, 0.84, 0.0 );  /* 図形の色を金色に設定 */
  glLineWidth( 5 );  /* 線の太さを5ピクセルに設定 */

  circle( 150.0, 30.0, 20.0 ); /* 自作関数を使用して中心(150,50),半径20の円を描画  */

  glFlush( );  /* コマンドバッファにたまっている未実行の命令を実行 */
}

int main( int argc, char *argv[] )
{
  glutInit( &argc, argv );             /* OpenGL/GLUT環境の初期化 */
  glutInitDisplayMode ( GLUT_RGBA );   /* ディスプレイモード(色の指定やその処理の方法)の設定 */
  glutInitWindowSize ( W_WIDTH, W_HEIGHT );   /* 画面サイズの設定 */
  glutInitWindowPosition( 0.0, 0.0 );  /* モニタ左上から(100,100)ピクセルの位置に表示 */
  glutCreateWindow( argv[0] );         /* main関数の引数で渡される実行ファイル名を画面の名前とする*/

  glClearColor ( 1.0, 1.0, 1.0, 0.0 ); /* 画面の背景色を白に設定 */
  glClear( GL_COLOR_BUFFER_BIT );      /* カラーバッファをクリア(背景を塗りつぶす) */

  /* ワールド座標系→正規化デバイス座標系への投影設定 */ 
  glMatrixMode( GL_PROJECTION );       /* 投影変換モードに設定 */
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( 0.0, 200.0, 0.0, 100.0, -1.0, 1.0 );  /* 正射影変換の範囲設定(0<x<200, 0<y<100) */

  glutDisplayFunc( display );          /* display関数の実行を指示 */

  glutMainLoop( );                     /* 入力待ち状態の無限ループ(画面の表示を続ける) */

  return 0;
}

