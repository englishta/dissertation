/* ルンゲ・クッタ法による2元連立1階常微分方程式の数値解法 */
/* 2種ロトカ・ヴォルテラ方程式による生態系のシミュレーション */

#include <stdio.h>
#include <math.h>     /* 数学関数のヘッダファイルの読み込み */
#include <GL/freeglut.h>  /* OpenGL/freeGLUTのヘッダファイルの読み込み */

#define N  2   /* 変数の数(種の数) */

#define W_WIDTH  1200  /* 画面の幅(width)[ピクセル] */
#define W_HEIGHT  400  /* 画面の高さ(height)[ピクセル] */

#define X0  -2.0  /* x軸の左端(最小値) */
#define X1  20.0  /* x軸の右端(最大値) */
#define Y0  -0.2  /* y軸の下端(最小値) */
#define Y1   1.2  /* y軸の上端(最大値) */

typedef struct model_parameter { /* 生態系モデルの係数のための構造体の宣言とtypedefによる別名の宣言 */
  double r;     /* 内的自然増加率 */
  double a[N];  /* 種内競争率, 種間競争率 */
} ModelParameter;  /* 構造体の別名(ModelParameter)を定義 */

double gt[1000], gx0[1000], gx1[1000];  /* グローバル変数(どの関数の中でも使用可能): グラフにプロットするデータを格納 */
int n_time;                             /* グローバル変数(どの関数の中でも使用可能): グラフにプロットするデータ数を格納 */
double x_ss[N];                         /* グローバル変数(どの関数の中でも使用可能):  main関数中で計算した定常状態の値を格納 */

/*====================================================*/
/* i番目の要素x[i]に対する微分方程式f(t, x)の定義     */
/* 種iの個体数密度は配列x[i]を引数として渡す          */
/* 生態系モデルの係数は構造体配列param[i]を引数として渡す */
/*====================================================*/
double f( int i, ModelParameter param[], double t, double x[] )
{
  int j;
  double r;

  r = param[i].r;  /* 内的自然増加率 */
  for( j = 0; j < N; j++ ) {
    r -= param[i].a[j] * x[j];  /* 種内競争率, 種間競争率 */
  }

  r *= x[i];

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
    for( i = 0; i <= (int) x1; i++ ) {  /* 1刻みで0からx1まで */
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

  /* グラフ1(x軸に時間、y軸に種1と種2の個体数密度の値)の投影設定 */ 
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* 正射影変換の範囲設定(X0<x<X1, Y0<y<Y1) */
  glViewport( 20, 20, W_WIDTH - W_HEIGHT - 40, W_HEIGHT - 40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  display_xy_axis( X0, X1, Y0, Y1 );         /* xy軸と目盛線を描画  */
  drawString2D( 12.0, -0.18, "time" );       /* x軸にtimeとラベルを描画 */
  drawString2D( -1.5, 0.50, "x[i]" );       /* y軸にラベルを描画 */
  drawString2D( -0.7, -0.1, "0" );           /* 原点(0,0)に0と描画 */
  drawString2D( -0.7, 0.98, "1" );           /* y軸の目盛に1と描画 */
  drawString2D( 9.5, -0.1, "10" );           /* x軸の目盛に10と描画 */
  drawString2D( 19.5, -0.1, "20" );           /* x軸の目盛に20と描画 */

  /* 変数x0(種1(サメ))の個体数密度の時間変化を赤い線でプロット */
  glColor3f( 1.0, 0.0, 0.0 );    /* 線の色を赤に設定 */
  glLineWidth( 2 );              /* 線の太さを2ピクセルに設定 */
  drawString2D( 2.0, 1.1, "shark x[0]" );   /* 赤い線(サメ)の説明 */

  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( gt[n], gx0[n] );   /* 数値解を頂点座標として設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */

  /* 変数x1(種2(小魚))の個体数密度の時間変化を青い線でプロット */
  glColor3f( 0.0, 0.0, 1.0 );    /* 線の色を青に設定 */
  glLineWidth( 2 );              /* 線の太さを2ピクセルに設定 */
  drawString2D( 7.0, 1.1, "small fish x[1]" );  /* 青い線(小魚)の説明 */

  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( gt[n], gx1[n] );   /* 数値解を頂点座標として設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */

  /* グラフ2(x軸に種1の個体数密度、y軸に種2の個体数密度)の投影設定 */ 
  glMatrixMode( GL_PROJECTION );       /* 投影変換モードに設定 */
  glLoadIdentity( );                   /* 変換行列を単位行列で初期化 */
  glOrtho( Y0, Y1, Y0, Y1, -1.0, 1.0 );  /* 正射影変換の範囲設定(Y0<x<Y1, Y0<y<Y1) */
  glViewport( W_WIDTH - W_HEIGHT, 20, W_HEIGHT - 20, W_HEIGHT - 40 ); /* 正規化デバイス座標系→ウィンドウ座標系への投影設定(部分画面表示) */

  display_xy_axis( -0.2, 1.2, -0.2, 1.2 );  /* xy軸と目盛線を描画  */
  drawString2D( 0.45, -0.2, "x[0]" );       /* x軸にx[0]とラベルを描画 */
  drawString2D( -0.2, 0.5, "x[1]" );        /* y軸にx[1]とラベルを描画 */
  drawString2D( -0.1, -0.1, "0" );          /* 原点(0,0)に0と描画 */
  drawString2D( 0.98, -0.1, "1" );          /* (1,0)の目盛に1と描画 */
  drawString2D( -0.1, 0.98, "1" );          /* (0,1)の目盛に1と描画 */

  glColor3f( 0.0, 0.6, 0.0 );    /* 線の色を濃い緑に設定 */
  glLineWidth( 2 );              /* 線の太さを2ピクセルに設定 */

  glBegin( GL_LINE_STRIP );   /* 図形描画タイプの設定開始: 折れ線で描画 */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( gx0[n], gx1[n] );   /* 数値解を頂点座標として設定 */
    }

  glEnd( );  /* 図形描画タイプの設定終了 */

  /* 定常状態の値を大きい点で表示 */
  glColor3f( 1.0, 0.0, 1.0 );    /* 点の色をマゼンタ(赤紫)に設定 */
  glPointSize( 10 );             /* 点の大きさを10×10ピクセルに設定 */

  glBegin( GL_POINTS );   /* 図形描画タイプの設定開始: 点で描画 */
    glVertex2d( 0.0, 0.0 );   /* 数値解を頂点座標として設定 */
    glVertex2d( x_ss[0], x_ss[1] );   /* 数値解を頂点座標として設定 */
  glEnd( );  /* 図形描画タイプの設定終了 */

  glFlush( );          /* コマンドバッファにたまっている未実行の命令を実行 */
}

int main( int argc, char *argv[] )
{
  int i, n;
  double t, dt, t0, t_end;
  double x[N];  /* 種iの個体数密度 */
  double k1[N], k2[N], k3[N], k4[N], xwork[N];  /* ルンゲ・クッタ法のための変数 */
  double a[N][N], b[N];     /* 定常状態の値を計算するための配列 */
  ModelParameter param[N];  /* 生態系モデルの係数に関する構造体配列の宣言 */

  param[0].r = -3.0;    /* 種1(サメ)の内的自然増加率 */
  param[0].a[0] = 1.0;  /* 種1(サメ)の種内競争率 */
  param[0].a[1] = -10.0; /* 種1(サメ)の種間競争率 */

  param[1].r = 1.5;     /* 種2(小魚)の内的自然増加率 */
  param[1].a[0] = 10.0;  /* 種2(小魚)の種間競争率 */
  param[1].a[1] = 0.0;  /* 種2(小魚)の種内競争率 */

  x[0] = 0.2;  /* 種1(サメ)の個体数密度の初期値 */
  x[1] = 0.8;  /* 種2(小魚)の個体数密度の初期値 */

  dt = 1.0e-3;  /* 時間のきざみ幅の設定*/
  t0 = 0.0;     /* シミュレーションの初期時刻の設定 */
  t_end = X1;   /* シミュレーションの終了時刻の設定 */

  for( i = 0; i < N; i++ ) {
    printf( "i = %d： r = %f a[0] = %f a[1] = %f\n", i, param[i].r, param[i].a[0], param[i].a[1] );
    printf( "初期値 x = %f\n", x[i] );
  }

  /* 連立1次方程式(プリント37ページの式(5.44))の数値解法による定常状態の値の計算 */
  a[0][0] = param[0].a[0];
  a[0][1] = param[0].a[1];
  a[1][0] = param[1].a[0];
  a[1][1] = param[1].a[1];
  b[0] = param[0].r;
  b[1] = param[1].r;

  gauss_elimination_pivot( a, b, x_ss ); /* 連立1次方程式の数値解法による定常状態の値の計算 */

  printf( "--- 定常状態の値 ---\n" );
  for( i = 0; i < N; i++ ) {
    printf( "x_ss[%d] = %f\n", i, x_ss[i] );
  }

  /* ルンゲ・クッタ法による1階常微分方程式の数値解法 */
  n = 0;          /* カウンター */
  n_time = 0;     /* グラフにプロットするデータ数を0に初期化 */
  for( t = t0; t <= t_end; t += dt ) {

    if( n % 100 == 0 ) {  /* 100回に1回グラフにプロット */
      gt[n_time] = t;      /* グラフにプロットする時刻tの値を配列gtに保存 */
      gx0[n_time] = x[0];  /* グラフにプロットするx[0]の値を配列gx0に保存 */
      gx1[n_time] = x[1];  /* グラフにプロットするx[1]の値を配列gx1に保存 */
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

