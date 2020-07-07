/* �ŋ}�~���@�ɂ��œK�� */

#include <stdio.h>
#include <math.h>     /* ���w�֐��̃w�b�_�t�@�C���̓ǂݍ��� */
#include <GL/freeglut.h>  /* OpenGL/freeGLUT�̃w�b�_�t�@�C���̓ǂݍ��� */

#define W_WIDTH  600  /* ��ʂ̕�(width)[�s�N�Z��] */
#define W_HEIGHT 400  /* ��ʂ̍���(height)[�s�N�Z��] */

double gx[500], gy[500];   /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): �O���t�`��̂��߂̃f�[�^�ۑ��p�ϐ� */
int n_step;                /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): �ŋ}�~���@�̌J��Ԃ��� */
double gx0, gx1, gy0, gy1; /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): �O���t�`��͈̔�(gx0,gy0)�`(gx1,gy1)�̒l */

/* �]���֐�f(x[])�̒�` */
double f( double x[] )
{
  double r;

  r = x[0]*x[0] +x[0]*x[1] + 2*x[1]*x[1] - exp(-3*x[1]*x[1]);

  return r;
}

/* �]���֐�f�̓_x[]�ɂ�������z�x�N�g��dx[]�̌v�Z */
void df( double x[], double dx[] )
{
  dx[0] = 2*x[0] + x[1];  /* df(x[])/dx[0] */
  dx[1] = x[0] + 4*x[1] + 6 * x[1] * exp(-3*x[1]*x[1]);  /* df(x[])/dx[1] */

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

void display( void )
{
  int k;

  glViewport( 0, 0, W_WIDTH, W_HEIGHT ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(�S��ʕ\��) */

  display_xy_axis( );  /* xy���Ɩڐ�����`��  */

  /* �ŋ}�~���@�̏����l(gx[0], gy[0])��傫�ȓ_�Ńv���b�g */
  glPointSize( 8 );            /* �_�̑傫����8�~8�s�N�Z���ɐݒ� */
  glColor3f( 0.0, 0.0, 1.0 );  /* �_�̐F��ɐݒ� */

  glBegin( GL_POINTS );   /* �}�`�`��^�C�v�̐ݒ�J�n: �_�ŕ`�� */
    glVertex2d( gx[0], gy[0] );     /* �����l�̍��W��ݒ� */
  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  glColor3f( 1.0, 0.0, 0.0 );  /* �_�̐F��Ԃɐݒ� */

  glBegin( GL_POINTS );   /* �}�`�`��^�C�v�̐ݒ�J�n: �_�ŕ`�� */

    for( k = 1; k <= n_step; k++ ) {
      glVertex2d( gx[k], gy[k] );     /* �e�X�e�b�v�̒l�̍��W��ݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  /* �ŋ}�~���@�̊e�X�e�b�v�̒l(gx[k], gy[k])����Ōq���� */
  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( k = 0; k <= n_step; k++ ) {
      glVertex2d( gx[k], gy[k] );     /* �e�X�e�b�v�̒l�̍��W��ݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  glFlush( );          /* �R�}���h�o�b�t�@�ɂ��܂��Ă��関���s�̖��߂����s */
}

int main( int argc, char *argv[] )
{
  int k, n_max;
  double x[2], dx[2];
  double alpha, delta;
  double x_min, x_max, y_min, y_max;

  delta = 1.0e-6;  /* �ŋ}�~���@�̎�������l */
  alpha = 2.0e-1;  /* �ŋ}�~���@�̃X�e�b�v���̒����l */
  n_max = 300;     /* �J��Ԃ��̍ő��(���S�΍�) */

  /* �����l�̐ݒ� */
  k = 0;
  x[0] = 8.0;
  x[1] = -5.0;

  gx[k] = x[0];  /* �O���t�`��̂��߂̃f�[�^�ۑ� */
  gy[k] = x[1];  /* �O���t�`��̂��߂̃f�[�^�ۑ� */

  df( x, dx );  /* ���z�x�N�g��dx[]�̌v�Z */
  printf( "%d���: F( %.15f, %.15f ) = %e\n", k, x[0], x[1], f(x) );

  while( sqrt( dx[0] * dx[0] + dx[1] * dx[1] ) > delta && k < n_max ) {

    k++;
    x[0] -= alpha * dx[0];  /* ���̓_�Ɉړ� */
    x[1] -= alpha * dx[1];  /* ���̓_�Ɉړ� */
    printf( "%d���: F( %.15f, %.15f ) = %e\n", k, x[0], x[1], f(x) );

    gx[k] = x[0];  /* �O���t�`��̂��߂̃f�[�^�ۑ� */
    gy[k] = x[1];  /* �O���t�`��̂��߂̃f�[�^�ۑ� */

    df( x, dx );  /* ���z�x�N�g��dx[]�̌v�Z */
  }

  n_step = k;  /* �ŋ}�~���@�̌J��Ԃ��񐔂�n_step�ɕۑ� */

  /* �ŋ}�~���@�̊e�X�e�b�v�̒l(gx[k], gy[k])�̍ŏ��l�ƍő�l�����߂� */
  x_min = gx[0];
  x_max = gx[0];
  y_min = gy[0];
  y_max = gy[0];
  for( k = 1; k <= n_step; k++ ) {
    if( gx[k] < x_min )       x_min = gx[k];
    else if( gx[k] > x_max )  x_max = gx[k];
    if( gy[k] < y_min )       y_min = gy[k];
    else if( gy[k] > y_max )  y_max = gy[k];
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
  glMatrixMode( GL_PROJECTION );         /* ���e�ϊ����[�h�ɐݒ� */
  glLoadIdentity( );                     /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( gx0, gx1, gy0, gy1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ�(gx0<x<gx1, gy0<y<gy1) */

  glutDisplayFunc( display );

  glutMainLoop( );

  return 0;
}

