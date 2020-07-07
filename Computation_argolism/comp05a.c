/* �ŏ�2��@�ɂ��t�B�b�e�B���O */

#include <stdio.h>
#include <math.h>     /* ���w�֐��̃w�b�_�t�@�C���̓ǂݍ��� */
#include <GL/freeglut.h>  /* OpenGL/freeGLUT�̃w�b�_�t�@�C���̓ǂݍ��� */

#define N  2    /* �t�B�b�e�B���O�p�����[�^�̌� = �W���s��̎��� */

#define W_WIDTH  600  /* ��ʂ̕�(width)[�s�N�Z��] */
#define W_HEIGHT 400  /* ��ʂ̍���(height)[�s�N�Z��] */

double x[100], y[100];     /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): �t�@�C������ǂݍ��񂾃f�[�^(x,y)���i�[ */
int n_data;                /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): �t�@�C������ǂݍ��񂾃f�[�^�̌� */
double a, b;               /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): �ŏ�2��@�Ō��߂��p�����[�^�̒l */
double gx0, gx1, gy0, gy1; /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): �O���t�`��͈̔�(gx0,gy0)�`(gx1,gy1)�̒l */

/* �t�B�b�e�B���O�֐�f(x,a,b)�̒�` */
double f( double arg_x, double arg_a, double arg_b )
{
  double r;

  r = arg_a * arg_x + arg_b;

  return r;
}

/*==========================================================*/
/*  �A��1���������̐��l��@�F�K�E�X�����@(�s�{�b�g�I������) */
/*==========================================================*/
void gauss_elimination_pivot( double arg_a[][N], double arg_b[], double arg_x[] )
{
  int i, j, k, m;
  double p_max, w;

  for( k = 0; k < N; k++ ) {

    /* �s�{�b�g�I�� */
    /* �Ίp�v�f�̐�Βl���ő�ƂȂ����(m)��T�� */
    m = k;
    p_max = fabs( arg_a[k][k] );
    for( i = k+1; i < N; i++ ) { 
      if( fabs( arg_a[i][k] ) > p_max ) {
        m = i;
        p_max = fabs( arg_a[i][k] );
      }
    }

    /* ��k�s(k�Ԗڂ̕�����)�Ƒ�m�s(m�Ԗڂ̕�����)����ꊷ���� */
    for( i = k; i < N; i++ ) {
      w = arg_a[k][i];
      arg_a[k][i] = arg_a[m][i];
      arg_a[m][i] = w;
    }
    w = arg_b[k];
    arg_b[k] = arg_b[m];
    arg_b[m] = w;

    /* �W���s��a�ƌW���x�N�g��b�̒u������ */
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

  /* �ϐ�x�̌��� */
  for( i = N-1; i >= 0; i-- ) {
    arg_x[i] = arg_b[i];
    for( j = i+1; j < N; j++ ) {
      arg_x[i] -= arg_a[i][j] * arg_x[j];
    }
  }

  return;
}

/* xy���Ɩڐ�����`�悷��֐� */
void display_xy_axis( void )
{
  int i;

  glColor3f( 0.0, 0.0, 0.0 );  /* ���̐F�����ɐݒ� */

  glBegin( GL_LINES ); /* �}�`�`��^�C�v�̐ݒ�J�n: �����ŕ`�� */
    /* x�� */
    glVertex2d( gx0, 0.0 );
    glVertex2d( gx1, 0.0 ); 

    /* y�� */
    glVertex2d( 0.0, gy0 );
    glVertex2d( 0.0, gy1 );

    /* x���̖ڐ��� */
    for( i = (int) gx0; i <= (int) gx1; i++ ) {  /* 1���݂�gx0����gx1�܂� */
      glVertex2d( i,  0.0 );
      glVertex2d( i,  0.5 );
    }

    /* y���̖ڐ��� */
    for( i = (int) gy0; i <= (int) gy1; i++ ) {  /* 1���݂�gy0����gy1�܂� */
      glVertex2d( 0.0, i );
      glVertex2d( 0.1, i );
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */
}

/* �O���t��`�悷��֐� */
void plot_graph( void )
{
  int i;
  double gx, gy, dx;

  /* �f�[�^(x[i], y[i])��傫�ȓ_�ŕ`�� */
  glColor3f( 1.0, 0.0, 0.0 );  /* �_�̐F��Ԃɐݒ� */
  glPointSize( 10 );           /* �_�̑傫����10�~10�s�N�Z���ɐݒ� */

  glBegin( GL_POINTS );   /* �}�`�`��^�C�v�̐ݒ�J�n: �_�ŕ`�� */

    for( i = 0; i < n_data; i++ ) {
      glVertex2d( x[i], y[i] );     /* �e�f�[�^�_�̍��W��ݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  /* �t�B�b�e�B���O�Ȑ���܂���ŕ`�� */
  glColor3f( 0.0, 0.0, 1.0 );  /* ���̐F��ɐݒ� */
  glLineWidth( 3 );            /* ���̑�����3�s�N�Z���ɐݒ� */
  dx = 0.1;   /* �t�B�b�e�B���O�Ȑ����v���b�g���鍏�ݕ� */

  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( gx = gx0; gx <= gx1; gx += dx ) {  /* gx�̒l��dx���݂�gx0����gx1�܂ŕω� */
      gy = f( gx, a, b );       /* y���W�̒l���v�Z */
      glVertex2d( gx, gy );     /* �t�B�b�e�B���O�Ȑ���̒��_���W��ݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */
}

void display( void )
{
  glViewport( 0, 0, W_WIDTH, W_HEIGHT ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(�S��ʕ\��) */

  display_xy_axis( );  /* xy���Ɩڐ�����`��  */
  plot_graph( );       /* �O���t��`�� */

  glFlush( );          /* �R�}���h�o�b�t�@�ɂ��܂��Ă��関���s�̖��߂����s */
}

int main( int argc, char *argv[] )
{
  int i;
  double p[N][N];   /* �W���s��p */
  double q[N], x_sol[N];  /* �W���x�N�g��q, ���x�N�g��x_sol */
  double x_min, x_max, y_min, y_max;
  FILE *fp;

  /* �t�@�C������f�[�^(x,y)��ǂލ��� */
  fp = fopen( "comp05aData.txt", "r" );

  if( fp == NULL ) {  /* ���S�΍�F���̓t�@�C���̃I�[�v���Ɏ��s�����ꍇ */
    printf( "���̓t�@�C���̃I�[�v���Ɏ��s���܂���\n" );
    return 0;
  }

  /* �f�[�^��z��x[i], y[i]�Ɋi�[���Ȃ���ǂݍ��� */
  i = 0;
  while( fscanf( fp, "%lf %lf", &x[i], &y[i] ) != EOF ) {
    i++;
  }

  fclose( fp );

  n_data = i;  /* �f�[�^�̌���n_data�ɕۑ� */

  /* �A��1���������̌W���s��p[N][N]�ƌW���x�N�g��q[N]�̌v�Z */
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

  /* �A��1���������̐��l��@���K�E�X�����@(�s�{�b�g�I������)�ŉ��� */
  gauss_elimination_pivot( p, q, x_sol );

  /* �ŏ�2��@�ł̌��� */
  a = x_sol[0];
  b = x_sol[1];
  printf( "%d�̃f�[�^�ɑ΂���ŏ�2��@: y = a x + b\na = %f\nb = %f\n", n_data, a, b );

  /* �f�[�^(x[i], y[i])�̍ŏ��l�ƍő�l�����߂� */
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

  /* �O���t�`��͈̔�(gx0,gy0)�`(gx1,gy1)�̒l�������傫�߂ɐݒ� */
  gx0 = x_min - ( x_max - x_min ) / 4.0; 
  gx1 = x_max + ( x_max - x_min ) / 4.0; 
  gy0 = y_min - ( y_max - y_min ) / 4.0; 
  gy1 = y_max + ( y_max - y_min ) / 4.0; 

  /* �O���t�Ɖ��̈ʒu��`�� */
  glutInit( &argc, argv );             /* OpenGL/GLUT���̏����� */
  glutInitDisplayMode ( GLUT_RGBA );   /* �f�B�X�v���C���[�h(�F�̎w��₻�̏����̕��@)�̐ݒ� */
  glutInitWindowSize ( W_WIDTH, W_HEIGHT );  /* ��ʃT�C�Y�̐ݒ� */
  glutInitWindowPosition( 100, 100 );  /* ���j�^���ォ��(100,100)�s�N�Z���̈ʒu�ɕ\�� */
  glutCreateWindow( argv[0] );         /* main�֐��̈����œn�������s�t�@�C��������ʂ̖��O�Ƃ���*/

  glClearColor ( 1.0, 1.0, 1.0, 0.0 );  /* ��ʂ̔w�i�F�𔒂ɐݒ� */
  glClear( GL_COLOR_BUFFER_BIT );       /* �J���[�o�b�t�@���N���A(�w�i��h��Ԃ�) */

  /* ���[���h���W�n�����K���f�o�C�X���W�n�ւ̓��e�ݒ� */ 
  glMatrixMode( GL_PROJECTION );       /* ���e�ϊ����[�h�ɐݒ� */
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( gx0, gx1, gy0, gy1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ�(gx0<x<gx1, gy0<y<gy1) */

  glutDisplayFunc( display );

  glutMainLoop( );

  return 0;
}

