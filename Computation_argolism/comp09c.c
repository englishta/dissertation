/* ルンゲ・クッタ法による3元連立1階常微分方程式の数値解法 */
/* ローレンツ方程式とカオス */

#include <stdio.h>
#include <math.h>     /* 数学関数のヘッダファイルの読み込み */
#include <GL/freeglut.h>  /* OpenGL/freeGLUTのヘッダファイルの読み込み */
 
#define N  3   /* 変数の数 */
 
#define W_WIDTH  1000  /* 画面の幅(width)[ピクセル] */
#define W_HEIGHT  700  /* 画面の高さ(height)[ピクセル] */

#define T_0    -2.0  /* 時間軸の左端(最小値) */
#define T_1    20.0  /* 時間軸の右端(最大値) */
#define X0_0  -60.0  /* x0軸の下端(最小値) */
#define X0_1   60.0  /* x0軸の上端(最大値) */
#define X1_0  -80.0  /* x1軸の下端(最小値) */
#define X1_1   80.0  /* x1軸の上端(最大値) */
#define X2_0  -20.0  /* x2軸の下端(最小値) */
#define X2_1  150.0  /* x2軸の上端(最大値) */

typedef struct model_parameter { /* ローレンツ方程式の係数のための構造体の宣言とtypedefによる別名の宣言 */
  double a;
} ModelParameter;  /* 構造体の別名(ModelParameter)を定義 */

struct plot_data {  /* グラフにプロットするデータ用の構造体の宣言 */
  double t;     /* 時刻tの値を保存するメンバ */
  double x0;    /* x[0]の値を保存するメンバ */
  double x1;    /* x[1]の値を保存するメンバ */
  double x2;    /* x[2]の値を保存するメンバ */
} data[3000];       /* グローバル変数(どの関数の中でも使用可能): グラフにプロットするデータを格納 */
 
int n_time;         /* グローバル変数(どの関数の中でも使用可能): グラフにプロットするデータ数を格納 */

/*====================================================*/
/* ローレンツ方程式                                   */
/*====================================================*/
double f( int i, ModelParameter param[], double t, double x[] )
{
  double r;

  if     ( i == 0 ) r = - param[0].a * ( x[0] - x[1] );  /* 方程式f0 */
  else if( i == 1 ) r = - x[0] * x[2] + param[1].a * x[0] - x[1];  /* 方程式f1 */
  else              r = x[0] * x[1] - param[2].a * x[2];  /* 方程式f2 */

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
void display_xy_axis( double x0, double x1, int ix, double y0, double y1 )
{
  int i;
  double s;

  glColor3f( 0.0, 0.0, 0.0 );  /* 線の色を黒に設定 */
  glLineWidth( 1 );            /* 線の太さを1ピクセルに設定 */

  glBegin( GL_LINES ); /* 図形描画タイプの設定開始: 線分で描画 */
    /* x軸 */
    glVertex2d( x0, 0.0 );
    glVertex2d( x1, 0.0 ); 

    /* y軸 */
    glVertex2d( 0.0, y0 );
    glVertex2d( 0.0, y1 );

    /* x軸の目盛線 */
    for( i = (int) x0; i <= (int) x1; i += ix ) {  /* ix刻みでx0からx1まで */
      glVertex2d( i,  0.0 );
      glVertex2d( i,  5.0 );
    }

    /* y軸の目盛線 */
    s = ( x1 - x0 ) / ( y1 - y0 ); /* 画面の縦横比の計算 */
    for( i = (int) y0; i <= (int) y1; i += 10 ) {  /* 10刻みでy0からy1まで */
      glVertex2d( 0.0, i );
      glVertex2d( 1.0 * s, i );  /* 画面の縦横比に応じて長さを調節 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */
}

void display( void )
{
  /* ワールド座標系→正規化デバイス座標系への投影設定 */ 
  glMatrixMode( GL_PROJECTION );       /* 投影変換モードに設定 */

  /* グラフ1(x軸に時間、y軸にx0の値)の投影設定 */ 
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( T_0, T_1, X0_0, X0_1, -1.0, 1.0 );  /* 正射影変換の範囲設定 */
  glViewport( 20, 2*W_HEIGHT/3+20, W_WIDTH-W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  display_xy_axis( T_0, T_1, 2, X0_0, X0_1 );   /* xy軸と目盛線を描画  */
  drawString2D( 2*T_1/3, -12.0, "time" );    /* x軸にtimeとラベルを描画 */
  drawString2D( -1.5,  X0_1/2, "x[0]" );     /* y軸にx[0]と描画 */
  drawString2D( -0.5, -12.0, "0" );          /* 原点(0,0)に0と描画 */
  drawString2D(  9.6, -12.0, "10" );         /* x軸の目盛に10を描画 */
  drawString2D( 19.6, -12.0, "20" );         /* x軸の目盛に20を描画 */

  /* グラフ2(x軸に時間、y軸にx1の値)の投影設定 */ 
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( T_0, T_1, X1_0, X1_1, -1.0, 1.0 );  /* 正射影変換の範囲設定 */
  glViewport( 20, W_HEIGHT/3+20, W_WIDTH-W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  display_xy_axis( T_0, T_1, 2, X1_0, X1_1 );   /* xy軸と目盛線を描画  */
  drawString2D( 2*T_1/3, -18.0, "time" );    /* x軸にtimeとラベルを描画 */
  drawString2D( -1.5,  X1_1/2, "x[1]" );     /* y軸にx[1]と描画 */
  drawString2D( -0.5, -18.0, "0" );          /* 原点(0,0)に0と描画 */
  drawString2D(  9.6, -18.0, "10" );         /* x軸の目盛に10を描画 */
  drawString2D( 19.6, -18.0, "20" );         /* x軸の目盛に20を描画 */

  /* グラフ3(x軸に時間、y軸にx2の値)の投影設定 */ 
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( T_0, T_1, X2_0, X2_1, -1.0, 1.0 );  /* 正射影変換の範囲設定 */
  glViewport( 20, 20, W_WIDTH-W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  display_xy_axis( T_0, T_1, 2, X2_0, X2_1 );   /* xy軸と目盛線を描画  */
  drawString2D( 2*T_1/3, -18.0, "time" );    /* x軸にtimeとラベルを描画 */
  drawString2D( -1.5,  X2_1/2, "x[2]" );     /* y軸にx[2]と描画 */
  drawString2D( -0.5, -18.0, "0" );          /* 原点(0,0)に0と描画 */
  drawString2D(  9.6, -18.0, "10" );         /* x軸の目盛に10を描画 */
  drawString2D( 19.6, -18.0, "20" );         /* x軸の目盛に20を描画 */

  /* グラフ4(x軸にx0、y軸にx1)の投影設定 */ 
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( X0_0, X0_1, X1_0, X1_1, -1.0, 1.0 );  /* 正射影変換の範囲設定 */
  glViewport( W_WIDTH-W_HEIGHT/3+20, W_HEIGHT/3+20, W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  display_xy_axis( X0_0, X0_1, 10, X1_0, X1_1 );  /* xy軸と目盛線を描画  */
  drawString2D( X0_1-20.0, -20.0, "x[0]" );   /* x軸にx[0]とラベルを描画 */
  drawString2D( -28.0, X1_1-20.0, "x[1]" );   /* y軸にx[1]とラベルを描画 */
  drawString2D( -10.0, -18.0, "0" );          /* 原点(0,0)に0と描画 */

  /* グラフ5(x軸にx0、y軸にx2)の投影設定 */ 
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( X0_0, X0_1, X2_0, X2_1, -1.0, 1.0 );  /* 正射影変換の範囲設定 */
  glViewport( W_WIDTH-W_HEIGHT/3+20, 20, W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  display_xy_axis( X0_0, X0_1, 10, X2_0, X2_1 );  /* xy軸と目盛線を描画  */
  drawString2D( X0_1-20.0, -20.0, "x[0]" );   /* x軸にx[0]とラベルを描画 */
  drawString2D( -28.0, X2_1-20.0, "x[2]" );   /* y軸にx[2]とラベルを描画 */
  drawString2D( -10.0, -18.0, "0" );          /* 原点(0,0)に0と描画 */

  glFlush( );          /* コマンドバッファにたまっている未実行の命令を実行 */
}

/* グラフに描画するデータを設定 */
void graph( void )
{
  int n;

  /* ワールド座標系→正規化デバイス座標系への投影設定 */ 
  glMatrixMode( GL_PROJECTION );       /* 投影変換モードに設定 */

  /* グラフ1(x軸に時間、y軸にx0の値)の投影設定 */ 
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( T_0, T_1, X0_0, X0_1, -1.0, 1.0 );  /* 正射影変換の範囲設定 */
  glViewport( 20, 2*W_HEIGHT/3+20, W_WIDTH-W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  /* 変数x0の時間変化を線でプロット */
  glLineWidth( 2 );            /* 線の太さを2ピクセルに設定 */
  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( data[n].t, data[n].x0 );   /* 数値解を頂点座標として設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */

  /* グラフ2(x軸に時間、y軸にx1の値)の投影設定 */ 
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( T_0, T_1, X1_0, X1_1, -1.0, 1.0 );  /* 正射影変換の範囲設定 */
  glViewport( 20, W_HEIGHT/3+20, W_WIDTH-W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  /* 変数x1の時間変化を線でプロット */
  glLineWidth( 2 );            /* 線の太さを2ピクセルに設定 */
  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( data[n].t, data[n].x1 );   /* 数値解を頂点座標として設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */

  /* グラフ3(x軸に時間、y軸にx2の値)の投影設定 */ 
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( T_0, T_1, X2_0, X2_1, -1.0, 1.0 );  /* 正射影変換の範囲設定 */
  glViewport( 20, 20, W_WIDTH-W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  /* 変数x1の時間変化を線でプロット */
  glLineWidth( 2 );            /* 線の太さを2ピクセルに設定 */
  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( data[n].t, data[n].x2 );   /* 数値解を頂点座標として設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */

  /* グラフ4(x軸にx0、y軸にx1)の投影設定 */ 
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( X0_0, X0_1, X1_0, X1_1, -1.0, 1.0 );  /* 正射影変換の範囲設定 */
  glViewport( W_WIDTH-W_HEIGHT/3+20, W_HEIGHT/3+20, W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  /* (x0,x1)の時間変化を線でプロット */
  glLineWidth( 1 );            /* 線の太さを1ピクセルに設定 */
  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( data[n].x0, data[n].x1 );   /* 数値解を頂点座標として設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */

  /* 初期値を大きい点で表示 */
  glPointSize( 10 );             /* 点の大きさを10×10ピクセルに設定 */

  glBegin( GL_POINTS );   /* 図形描画タイプの設定開始: 点で描画 */
    glVertex2d( data[0].x0, data[0].x1 );   /* 数値解を頂点座標として設定 */
  glEnd( );  /* 図形描画タイプの設定終了 */

  /* グラフ5(x軸にx0、y軸にx2)の投影設定 */ 
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( X0_0, X0_1, X2_0, X2_1, -1.0, 1.0 );  /* 正射影変換の範囲設定 */
  glViewport( W_WIDTH-W_HEIGHT/3+20, 20, W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  /* (x0,x2)の時間変化を線でプロット */
  glLineWidth( 1 );            /* 線の太さを1ピクセルに設定 */
  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( data[n].x0, data[n].x2 );   /* 数値解を頂点座標として設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */

  /* 初期値を大きい点で表示 */
  glPointSize( 10 );             /* 点の大きさを10×10ピクセルに設定 */

  glBegin( GL_POINTS );   /* 図形描画タイプの設定開始: 点で描画 */
    glVertex2d( data[0].x0, data[0].x2 );   /* 数値解を頂点座標として設定 */
  glEnd( );  /* 図形描画タイプの設定終了 */

}

int main( int argc, char *argv[] )
{
  int i, m, n;
  double t, dt, t0, t_end;
  double x[N];  /* 変数 */
  ModelParameter param[N];  /* ローレンツ方程式のパラメータ */
  double k1[N], k2[N], k3[N], k4[N], xwork[N];  /* ルンゲ・クッタ法のための変数 */

  /* グラフィックスの初期設定 */
  glutInit( &argc, argv );             /* OpenGL/GLUT環境の初期化 */
  glutInitDisplayMode ( GLUT_RGBA );   /* ディスプレイモード(色の指定やその処理の方法)の設定 */
  glutInitWindowSize ( W_WIDTH, W_HEIGHT );  /* 画面サイズの設定 */
  glutInitWindowPosition( 100, 100 );  /* モニタ左上から(100,100)ピクセルの位置に表示 */
  glutCreateWindow( argv[0] );         /* main関数の引数で渡される実行ファイル名を画面の名前とする*/

  glClearColor ( 1.0, 1.0, 1.0, 0.0 );  /* 画面の背景色を白に設定 */
  glClear( GL_COLOR_BUFFER_BIT ); /* カラーバッファをクリア(背景を塗りつぶす) */

  param[0].a = 10.0;    /* パラメータの設定 */
  param[1].a = 80.0;    /* パラメータの設定 */
  param[2].a = 8.0 / 3.0;    /* パラメータの設定 */

  dt = 1.0e-4;  /* 時間のきざみ幅の設定*/
  t0 = 0.0;     /* シミュレーションの初期時刻の設定 */
  t_end = T_1;  /* シミュレーションの終了時刻の設定 */

  for( m = 0; m < 2; m++ ) {  /* 初期値を変えてシミュレーションを2回繰り返す */

    /* 1回目と2回目のシミュレーションで設定を変える */
    if( m == 0 ) { /* 1回目のシミュレーションの場合 */
      x[0] = -2.0;    /* 初期値の設定A */
      x[1] = 10.0;    /* 初期値の設定A */
      x[2] =  7.0;    /* 初期値の設定A */
      glColor3f( 1.0, 0.0, 0.0 );    /* 描画する線の色を赤に設定 */
    }
    else {         /* 2回目のシミュレーションの場合 */
      x[0] = -2.001;  /* 初期値の設定B */
      x[1] = 10.0;    /* 初期値の設定B */
      x[2] =  7.0;    /* 初期値の設定B */
      glColor3f( 0.0, 0.0, 1.0 );    /* 描画する線の色を青に設定 */
    }

    /* ルンゲ・クッタ法による連立1階常微分方程式の数値解法 */
    n = 0;          /* カウンター */
    n_time = 0;     /* グラフにプロットするデータ数を0に初期化 */
    for( t = t0; t <= t_end; t += dt ) {

      if( n % 100 == 0 ) {  /* 100回に1回グラフにプロット */
        data[n_time].t = t;      /* グラフにプロットする時刻tの値を構造体配列dataのメンバtに保存 */
        data[n_time].x0 = x[0];  /* グラフにプロットするx[0]の値を構造体配列dataのメンバx0に保存 */
        data[n_time].x1 = x[1];  /* グラフにプロットするx[1]の値を構造体配列dataのメンバx1に保存 */
        data[n_time].x2 = x[2];  /* グラフにプロットするx[2]の値を構造体配列dataのメンバx2に保存 */
        n_time++;            /* グラフにプロットするデータ数を1加算 */
      }
      n++;  /* カウンターを1加算 */

      /* ルンゲ・クッタ法の1段目：全てのk1[i](始点での傾き)の計算 */
      for( i = 0; i < N; i++ ) k1[i] = f( i, param, t, x ) * dt;

      /* k2[i]のための中点1(xwork[i])の計算  */
      for( i = 0; i < N; i++ ) xwork[i] = x[i] + 0.5 * k1[i];

      /* ルンゲ・クッタ法の2段目：全てのk2[i](中点1での傾き)の計算 */
      for( i = 0; i < N; i++ ) k2[i] = f( i, param, t + 0.5 * dt, xwork ) * dt;

      /* k3[i]のための中点2(xwork[i])の計算  */
      for( i = 0; i < N; i++ ) xwork[i] = x[i] + 0.5 * k2[i];

      /* ルンゲ・クッタ法の3段目：全てのk3[i](中点2での傾き)の計算 */
      for( i = 0; i < N; i++ ) k3[i] = f( i, param, t + 0.5 * dt, xwork ) * dt;

      /* k4[i]のための終点(xwork[i])の計算  */
      for( i = 0; i < N; i++ ) xwork[i] = x[i] + k3[i];

      /* ルンゲ・クッタ法の4段目：全てのk4[i](終点での傾き)の計算 */
      for( i = 0; i < N; i++ ) k4[i] = f( i, param, t + dt, xwork ) * dt;

      /* ルンゲ・クッタ法 */
      for( i = 0; i < N; i++ ) x[i] += ( k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i] ) / 6.0;

    }

    /* グラフに描画するデータを設定 */
    graph( );

  }

  /* グラフを描画 */
  glutDisplayFunc( display );

  glutMainLoop( );

  return 0;
}

