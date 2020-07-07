/* �����Q�E�N�b�^�@�ɂ��2���A��1�K������������̐��l��@ */
/* 2�탍�g�J�E���H���e���������ɂ�鐶�Ԍn�̃V�~�����[�V���� */

#include <stdio.h>
#include <math.h>     /* ���w�֐��̃w�b�_�t�@�C���̓ǂݍ��� */
#include <GL/freeglut.h>  /* OpenGL/freeGLUT�̃w�b�_�t�@�C���̓ǂݍ��� */

#define N  2   /* �ϐ��̐�(��̐�) */

#define W_WIDTH  1200  /* ��ʂ̕�(width)[�s�N�Z��] */
#define W_HEIGHT  400  /* ��ʂ̍���(height)[�s�N�Z��] */

#define X0  -2.0  /* x���̍��[(�ŏ��l) */
#define X1  20.0  /* x���̉E�[(�ő�l) */
#define Y0  -0.2  /* y���̉��[(�ŏ��l) */
#define Y1   1.2  /* y���̏�[(�ő�l) */

typedef struct model_parameter { /* ���Ԍn���f���̌W���̂��߂̍\���̂̐錾��typedef�ɂ��ʖ��̐錾 */
  double r;     /* ���I���R������ */
  double a[N];  /* ���������, ��ԋ����� */
} ModelParameter;  /* �\���̂̕ʖ�(ModelParameter)���` */

double gt[1000], gx0[1000], gx1[1000];  /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): �O���t�Ƀv���b�g����f�[�^���i�[ */
int n_time;                             /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): �O���t�Ƀv���b�g����f�[�^�����i�[ */
double x_ss[N];                         /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\):  main�֐����Ōv�Z��������Ԃ̒l���i�[ */

/*====================================================*/
/* i�Ԗڂ̗v�fx[i]�ɑ΂������������f(t, x)�̒�`     */
/* ��i�̌̐����x�͔z��x[i]�������Ƃ��ēn��          */
/* ���Ԍn���f���̌W���͍\���̔z��param[i]�������Ƃ��ēn�� */
/*====================================================*/
double f( int i, ModelParameter param[], double t, double x[] )
{
  int j;
  double r;

  r = param[i].r;  /* ���I���R������ */
  for( j = 0; j < N; j++ ) {
    r -= param[i].a[j] * x[j];  /* ���������, ��ԋ����� */
  }

  r *= x[i];

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

/* �������`�悷��֐� */
void drawString2D( double x, double y, char *str )
{
  glRasterPos2d( x, y );   /* ������̐擪�̕`��ʒu��(x,y)�ɐݒ� */

  while( *str != '\0' ) {  /* �������I���R�[�h�łȂ���� */
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *str );  /* 24�|�C���g��Times Roman�r�b�g�}�b�v�t�H���g��1�������`�� */
    str++;  /* 1��������ɐi�߂� */
  }
}

/* xy���Ɩڐ�����`�悷��֐� */
void display_xy_axis( double x0, double x1, double y0, double y1 )
{
  int i;
  double s;

  glColor3f( 0.0, 0.0, 0.0 );  /* ���̐F�����ɐݒ� */
  glLineWidth( 1 );            /* ���̑�����1�s�N�Z���ɐݒ� */

  glBegin( GL_LINES ); /* �}�`�`��^�C�v�̐ݒ�J�n: �����ŕ`�� */
    /* x�� */
    glVertex2d( x0, 0.0 );
    glVertex2d( x1, 0.0 ); 

    /* y�� */
    glVertex2d( 0.0, y0 );
    glVertex2d( 0.0, y1 );

    /* x���̖ڐ��� */
    for( i = 0; i <= (int) x1; i++ ) {  /* 1���݂�0����x1�܂� */
      glVertex2d( i,  0.0 );
      glVertex2d( i,  0.05 );
    }

    /* y���̖ڐ��� */
    s = ( x1 - x0 ) / ( y1 - y0 ); /* ��ʂ̏c����̌v�Z */
    for( i = (int) y0; i <= (int) y1; i++ ) {  /* 1���݂�y0����y1�܂� */
      glVertex2d( 0.0, i );
      glVertex2d( 0.05 * s, i );  /* ��ʂ̏c����ɉ����Ē����𒲐� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */
}

void display( void )
{
  int n;

  /* ���[���h���W�n�����K���f�o�C�X���W�n�ւ̓��e�ݒ� */ 
  glMatrixMode( GL_PROJECTION );       /* ���e�ϊ����[�h�ɐݒ� */

  /* �O���t1(x���Ɏ��ԁAy���Ɏ�1�Ǝ�2�̌̐����x�̒l)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ�(X0<x<X1, Y0<y<Y1) */
  glViewport( 20, 20, W_WIDTH - W_HEIGHT - 40, W_HEIGHT - 40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  display_xy_axis( X0, X1, Y0, Y1 );         /* xy���Ɩڐ�����`��  */
  drawString2D( 12.0, -0.18, "time" );       /* x����time�ƃ��x����`�� */
  drawString2D( -1.5, 0.50, "x[i]" );       /* y���Ƀ��x����`�� */
  drawString2D( -0.7, -0.1, "0" );           /* ���_(0,0)��0�ƕ`�� */
  drawString2D( -0.7, 0.98, "1" );           /* y���̖ڐ���1�ƕ`�� */
  drawString2D( 9.5, -0.1, "10" );           /* x���̖ڐ���10�ƕ`�� */
  drawString2D( 19.5, -0.1, "20" );           /* x���̖ڐ���20�ƕ`�� */

  /* �ϐ�x0(��1(�T��))�̌̐����x�̎��ԕω���Ԃ����Ńv���b�g */
  glColor3f( 1.0, 0.0, 0.0 );    /* ���̐F��Ԃɐݒ� */
  glLineWidth( 2 );              /* ���̑�����2�s�N�Z���ɐݒ� */
  drawString2D( 2.0, 1.1, "shark x[0]" );   /* �Ԃ���(�T��)�̐��� */

  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( gt[n], gx0[n] );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  /* �ϐ�x1(��2(����))�̌̐����x�̎��ԕω�������Ńv���b�g */
  glColor3f( 0.0, 0.0, 1.0 );    /* ���̐F��ɐݒ� */
  glLineWidth( 2 );              /* ���̑�����2�s�N�Z���ɐݒ� */
  drawString2D( 7.0, 1.1, "small fish x[1]" );  /* ����(����)�̐��� */

  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( gt[n], gx1[n] );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  /* �O���t2(x���Ɏ�1�̌̐����x�Ay���Ɏ�2�̌̐����x)�̓��e�ݒ� */ 
  glMatrixMode( GL_PROJECTION );       /* ���e�ϊ����[�h�ɐݒ� */
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( Y0, Y1, Y0, Y1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ�(Y0<x<Y1, Y0<y<Y1) */
  glViewport( W_WIDTH - W_HEIGHT, 20, W_HEIGHT - 20, W_HEIGHT - 40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  display_xy_axis( -0.2, 1.2, -0.2, 1.2 );  /* xy���Ɩڐ�����`��  */
  drawString2D( 0.45, -0.2, "x[0]" );       /* x����x[0]�ƃ��x����`�� */
  drawString2D( -0.2, 0.5, "x[1]" );        /* y����x[1]�ƃ��x����`�� */
  drawString2D( -0.1, -0.1, "0" );          /* ���_(0,0)��0�ƕ`�� */
  drawString2D( 0.98, -0.1, "1" );          /* (1,0)�̖ڐ���1�ƕ`�� */
  drawString2D( -0.1, 0.98, "1" );          /* (0,1)�̖ڐ���1�ƕ`�� */

  glColor3f( 0.0, 0.6, 0.0 );    /* ���̐F��Z���΂ɐݒ� */
  glLineWidth( 2 );              /* ���̑�����2�s�N�Z���ɐݒ� */

  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( gx0[n], gx1[n] );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  /* ����Ԃ̒l��傫���_�ŕ\�� */
  glColor3f( 1.0, 0.0, 1.0 );    /* �_�̐F���}�[���^(�Ԏ�)�ɐݒ� */
  glPointSize( 10 );             /* �_�̑傫����10�~10�s�N�Z���ɐݒ� */

  glBegin( GL_POINTS );   /* �}�`�`��^�C�v�̐ݒ�J�n: �_�ŕ`�� */
    glVertex2d( 0.0, 0.0 );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
    glVertex2d( x_ss[0], x_ss[1] );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  glFlush( );          /* �R�}���h�o�b�t�@�ɂ��܂��Ă��関���s�̖��߂����s */
}

int main( int argc, char *argv[] )
{
  int i, n;
  double t, dt, t0, t_end;
  double x[N];  /* ��i�̌̐����x */
  double k1[N], k2[N], k3[N], k4[N], xwork[N];  /* �����Q�E�N�b�^�@�̂��߂̕ϐ� */
  double a[N][N], b[N];     /* ����Ԃ̒l���v�Z���邽�߂̔z�� */
  ModelParameter param[N];  /* ���Ԍn���f���̌W���Ɋւ���\���̔z��̐錾 */

  param[0].r = -3.0;    /* ��1(�T��)�̓��I���R������ */
  param[0].a[0] = 1.0;  /* ��1(�T��)�̎�������� */
  param[0].a[1] = -10.0; /* ��1(�T��)�̎�ԋ����� */

  param[1].r = 1.5;     /* ��2(����)�̓��I���R������ */
  param[1].a[0] = 10.0;  /* ��2(����)�̎�ԋ����� */
  param[1].a[1] = 0.0;  /* ��2(����)�̎�������� */

  x[0] = 0.2;  /* ��1(�T��)�̌̐����x�̏����l */
  x[1] = 0.8;  /* ��2(����)�̌̐����x�̏����l */

  dt = 1.0e-3;  /* ���Ԃ̂����ݕ��̐ݒ�*/
  t0 = 0.0;     /* �V�~�����[�V�����̏��������̐ݒ� */
  t_end = X1;   /* �V�~�����[�V�����̏I�������̐ݒ� */

  for( i = 0; i < N; i++ ) {
    printf( "i = %d�F r = %f a[0] = %f a[1] = %f\n", i, param[i].r, param[i].a[0], param[i].a[1] );
    printf( "�����l x = %f\n", x[i] );
  }

  /* �A��1��������(�v�����g37�y�[�W�̎�(5.44))�̐��l��@�ɂ�����Ԃ̒l�̌v�Z */
  a[0][0] = param[0].a[0];
  a[0][1] = param[0].a[1];
  a[1][0] = param[1].a[0];
  a[1][1] = param[1].a[1];
  b[0] = param[0].r;
  b[1] = param[1].r;

  gauss_elimination_pivot( a, b, x_ss ); /* �A��1���������̐��l��@�ɂ�����Ԃ̒l�̌v�Z */

  printf( "--- ����Ԃ̒l ---\n" );
  for( i = 0; i < N; i++ ) {
    printf( "x_ss[%d] = %f\n", i, x_ss[i] );
  }

  /* �����Q�E�N�b�^�@�ɂ��1�K������������̐��l��@ */
  n = 0;          /* �J�E���^�[ */
  n_time = 0;     /* �O���t�Ƀv���b�g����f�[�^����0�ɏ����� */
  for( t = t0; t <= t_end; t += dt ) {

    if( n % 100 == 0 ) {  /* 100���1��O���t�Ƀv���b�g */
      gt[n_time] = t;      /* �O���t�Ƀv���b�g���鎞��t�̒l��z��gt�ɕۑ� */
      gx0[n_time] = x[0];  /* �O���t�Ƀv���b�g����x[0]�̒l��z��gx0�ɕۑ� */
      gx1[n_time] = x[1];  /* �O���t�Ƀv���b�g����x[1]�̒l��z��gx1�ɕۑ� */
      n_time++;            /* �O���t�Ƀv���b�g����f�[�^����1���Z */
    }
    n++;  /* �J�E���^�[��1���Z */

    /* �����Q�E�N�b�^�@��1�i�ځF�S�Ă�k1[i](�n�_�ł̌X��)�̌v�Z */
    for( i = 0; i < N; i++ ) k1[i] = f( i, param, t, x ) * dt;

    /* k2[i]�̂��߂̒��_1(xwork[i])�̌v�Z  */
    for( i = 0; i < N; i++ ) xwork[i] = x[i] + 0.5 * k1[i];

    /* �����Q�E�N�b�^�@��2�i�ځF�S�Ă�k2[i](���_1�ł̌X��)�̌v�Z */
    for( i = 0; i < N; i++ ) k2[i] = f( i, param, t + 0.5 * dt, xwork ) * dt;

    /* k3[i]�̂��߂̒��_2(xwork[i])�̌v�Z  */
    for( i = 0; i < N; i++ ) xwork[i] = x[i] + 0.5 * k2[i];

    /* �����Q�E�N�b�^�@��3�i�ځF�S�Ă�k3[i](���_2�ł̌X��)�̌v�Z */
    for( i = 0; i < N; i++ ) k3[i] = f( i, param, t + 0.5 * dt, xwork ) * dt;

    /* k4[i]�̂��߂̏I�_(xwork[i])�̌v�Z  */
    for( i = 0; i < N; i++ ) xwork[i] = x[i] + k3[i];

    /* �����Q�E�N�b�^�@��4�i�ځF�S�Ă�k4[i](�I�_�ł̌X��)�̌v�Z */
    for( i = 0; i < N; i++ ) k4[i] = f( i, param, t + dt, xwork ) * dt;

    /* �����Q�E�N�b�^�@ */
    for( i = 0; i < N; i++ ) x[i] += ( k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i] ) / 6.0;
  }

  /* �O���t�Ɖ��̈ʒu��`�� */
  glutInit( &argc, argv );             /* OpenGL/GLUT���̏����� */
  glutInitDisplayMode ( GLUT_RGBA );   /* �f�B�X�v���C���[�h(�F�̎w��₻�̏����̕��@)�̐ݒ� */
  glutInitWindowSize ( W_WIDTH, W_HEIGHT );  /* ��ʃT�C�Y�̐ݒ� */
  glutInitWindowPosition( 100, 100 );  /* ���j�^���ォ��(100,100)�s�N�Z���̈ʒu�ɕ\�� */
  glutCreateWindow( argv[0] );         /* main�֐��̈����œn�������s�t�@�C��������ʂ̖��O�Ƃ���*/

  glClearColor ( 1.0, 1.0, 1.0, 0.0 );  /* ��ʂ̔w�i�F�𔒂ɐݒ� */
  glClear( GL_COLOR_BUFFER_BIT ); /* �J���[�o�b�t�@���N���A(�w�i��h��Ԃ�) */

  glutDisplayFunc( display );

  glutMainLoop( );

  return 0;
}

