/* ルンゲ・クッタ法による3元連立1階常微分方程式の数値解法 */
/* SIRモデルによる感染症流行のシミュレーション */

#include <stdio.h>
#include <math.h>     /* 数学関数のヘッダファイルの読み込み */
#include <GL/freeglut.h>  /* OpenGL/freeGLUTのヘッダファイルの読み込み */

#define N  3   /* 変数の数(未感染者数、感染者数、回復者数) */

#define W_WIDTH   700  /* 画面の幅(width)[ピクセル] */
#define W_HEIGHT  400  /* 画面の高さ(height)[ピクセル] */

#define X0 -10.0  /* x軸の左端(最小値) */
#define X1  90.0  /* x軸の右端(最大値) */
#define Y0  -0.2  /* y軸の下端(最小値) */
#define Y1   1.2  /* y軸の上端(最大値) */

typedef struct model_parameter { /* SIRモデルのパラメータのための構造体の宣言とtypedefによる別名の宣言 */
  double beta;    /* 感染率 */
  double gamma;   /* 回復率 */
} ModelParameter;  /* 構造体の別名(ModelParameter)を定義 */

double gt[1000], gx0[1000], gx1[1000], gx2[1000];  /* グローバル変数(どの関数の中でも使用可能): グラフにプロットするデータを格納 */
int n_time;                             /* グローバル変数(どの関数の中でも使用可能): グラフにプロットするデータ数を格納 */

/*=========================================================*/
/* i番目の要素x[i]に対する微分方程式f(i, t, x)の定義       */
/* 各変数の値は配列x[i]を引数として渡す                    */
/* SIRモデルのパラメータは構造体変数paramを引数として渡す  */
/*=========================================================*/
double f( int i, ModelParameter param, double t, double x[] )
{
  double r;

  if     ( i == 0 ) r = - param.beta * x[0] * x[1];                    /* 未感染者(x[0])の微分方程式 */
  else if( i == 1 ) r = param.beta * x[0] * x[1] - param.gamma * x[1]; /* 感染者(x[1])の微分方程式 */
  else              r = param.gamma * x[1];                            /* 回復者(x[2])の微分方程式 */

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
void display_xy_axis( double x0, double x1, double y0, double y1 )
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
    for( i = 0; i <= (int) x1; i += 10 ) {  /* 10刻みで0からx1まで */
      glVertex2d( i,  0.0 );
      glVertex2d( i,  0.05 );
    }

    /* y軸の目盛線 */
    s = ( x1 - x0 ) / ( y1 - y0 ); /* 画面の縦横比の計算 */
    for( i = (int) y0; i <= (int) y1; i++ ) {  /* 1刻みでy0からy1まで */
      glVertex2d( 0.0, i );
      glVertex2d( 0.05 * s, i );  /* 画面の縦横比に応じて長さを調節 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */
}

void display( void )
{
  int n;

  /* ワールド座標系→正規化デバイス座標系への投影設定 */ 
  glMatrixMode( GL_PROJECTION );       /* 投影変換モードに設定 */

  /* グラフ(x軸に時間、y軸に各人口比率の値)の投影設定 */ 
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* 正射影変換の範囲設定(X0<x<X1, Y0<y<Y1) */
  glViewport( 20, 20, W_WIDTH - 40, W_HEIGHT - 40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  display_xy_axis( X0, X1, Y0, Y1 );         /* xy軸と目盛線を描画  */
  drawString2D( X1/2, -0.18, "time" );       /* x軸にtimeとラベルを描画 */
  drawString2D( -3.5, -0.1, "0" );           /* 原点(0,0)に0と描画 */
  drawString2D( -10.0, 0.5, "x[i]/N" );      /* y軸にラベルを描画 */
  drawString2D( -3.5, 0.98, "1" );           /* y軸の目盛に1と描画 */
  drawString2D( 18, -0.1, "20" );           /* x軸の目盛に20と描画 */
  drawString2D( 38, -0.1, "40" );           /* x軸の目盛に40と描画 */
  drawString2D( 58, -0.1, "60" );           /* x軸の目盛に60と描画 */
  drawString2D( 78, -0.1, "80" );           /* x軸の目盛に80と描画 */

  /* 変数x0(未感染者)の人口比率の時間変化を青線でプロット */
  glColor3f( 0.0, 0.0, 1.0 );    /* 線の色を青に設定 */
  glLineWidth( 2 );              /* 線の太さを2ピクセルに設定 */
  drawString2D( 2.0, 1.1, "Susceptible x[0]" );   /* 青線(未感染者)の説明 */

  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( gt[n], gx0[n] );   /* 数値解を頂点座標として設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */

  /* 変数x1(感染者)の人口比率の時間変化を赤線でプロット */
  glColor3f( 1.0, 0.0, 0.0 );    /* 線の色を赤に設定 */
  glLineWidth( 2 );              /* 線の太さを2ピクセルに設定 */
  drawString2D( 5.0+X1/3, 1.1, "Infectious x[1]" );  /* 赤線(感染者)の説明 */

  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( gt[n], gx1[n] );   /* 数値解を頂点座標として設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */

  /* 変数x3(回復者)の人口比率の時間変化を緑線でプロット */
  glColor3f( 0.0, 0.6, 0.0 );    /* 線の色を暗い緑に設定 */
  glLineWidth( 2 );              /* 線の太さを2ピクセルに設定 */
  drawString2D( 5.0+2*X1/3, 1.1, "Recovered x[2]" );  /* 緑線(回復者)の説明 */

  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( gt[n], gx2[n] );   /* 数値解を頂点座標として設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */

  glFlush( );          /* コマンドバッファにたまっている未実行の命令を実行 */
}

int main( int argc, char *argv[] )
{
  int i, n;
  double t, dt, t0, t_end;
  double x[N];  /* 変数(各人口) */
  double k1[N], k2[N], k3[N], k4[N], xwork[N];  /* ルンゲ・クッタ法のための変数 */
  double n_tot;  /* 総人口 */
  ModelParameter param;  /* SIRモデルのパラメータに関する構造体変数の宣言 */

  param.beta = 0.005;   /* 感染率(SIRモデルのパラメータ) */
  param.gamma = 0.2;    /* 回復率(SIRモデルのパラメータ) */

  x[0] = 1000.0;  /* 免疫のない未感染者数の初期値 */
  x[1] = 1.0;     /* 感染者数の初期値 */
  x[2] = 0.0;     /* 免疫のある回復者数の初期値 */
  n_tot = x[0] + x[1] + x[2];  /* 総人口(一定値) */

  dt = 1.0e-3;  /* 時間のきざみ幅の設定*/
  t0 = 0.0;     /* シミュレーションの初期時刻の設定 */
  t_end = X1;   /* シミュレーションの終了時刻の設定 */

  printf( "beta = %f\n", param.beta );
  printf( "gamma = %f (1/gamma = %f)\n", param.gamma, 1.0/param.gamma );
  for( i = 0; i < N; i++ ) {
    printf( "初期値 x[%d] = %.1f\n", i, x[i] );

  }

  /* ルンゲ・クッタ法による1階常微分方程式の数値解法 */
  n = 0;          /* カウンター */
  n_time = 0;     /* グラフにプロットするデータ数を0に初期化 */
  for( t = t0; t <= t_end; t += dt ) {

    if( n % 200 == 0 ) {  /* 200回に1回グラフにプロット */
      gt[n_time] = t;      /* グラフにプロットする時刻tの値を配列gtに保存 */
      gx0[n_time] = x[0] / n_tot;  /* グラフにプロットするx[0]/n_totの値を配列gx0に保存 */
      gx1[n_time] = x[1] / n_tot;  /* グラフにプロットするx[1]/n_totの値を配列gx1に保存 */
      gx2[n_time] = x[2] / n_tot;  /* グラフにプロットするx[2]/n_totの値を配列gx2に保存 */
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

  /* グラフと解の位置を描画 */
  glutInit( &argc, argv );             /* OpenGL/GLUT環境の初期化 */
  glutInitDisplayMode ( GLUT_RGBA );   /* ディスプレイモード(色の指定やその処理の方法)の設定 */
  glutInitWindowSize ( W_WIDTH, W_HEIGHT );  /* 画面サイズの設定 */
  glutInitWindowPosition( 100, 100 );  /* モニタ左上から(100,100)ピクセルの位置に表示 */
  glutCreateWindow( argv[0] );         /* main関数の引数で渡される実行ファイル名を画面の名前とする*/

  glClearColor ( 1.0, 1.0, 1.0, 0.0 );  /* 画面の背景色を白に設定 */
  glClear( GL_COLOR_BUFFER_BIT ); /* カラーバッファをクリア(背景を塗りつぶす) */

  glutDisplayFunc( display );

  glutMainLoop( );

  return 0;
}

