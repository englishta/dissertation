/* �j���[�g���E���t�\���@�ɂ��f(x)=0�̉� */

#include <stdio.h>
#include <math.h>     /* ���w�֐��̃w�b�_�t�@�C���̓ǂݍ��� */
#include <GL/freeglut.h>  /* OpenGL/freeGLUT�̃w�b�_�t�@�C���̓ǂݍ��� */

#define W_WIDTH  600  /* ��ʂ̕�(width)[�s�N�Z��] */
#define W_HEIGHT 400  /* ��ʂ̍���(height)[�s�N�Z��] */

#define X0  -3  /* x���̍��[(�ŏ��l) */
#define X1   6  /* x���̉E�[(�ő�l) */
#define Y0  -5  /* y���̉��[(�ŏ��l) */
#define Y1  20  /* y���̏�[(�ő�l) */

double x_solution;  /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): main�֐��̒��ŋ��߂����̒l��ۑ� */

/* �֐�f(x)�̒�` */
double f( double x )
{
  double r;

  r = exp(0.5*x) - 2.0*x;

  return r;
}

/* f(x)��x�Ŕ��������֐��̒�` */
double df( double x )
{
  double r;

  r = 0.5 * exp(0.5*x) - 2.0;

  return r;
}

/* xy���Ɩڐ�����`�悷��֐� */
void display_xy_axis( void )
{
  int i;

  glColor3f( 0.0, 0.0, 0.0 );  /* ���̐F�����ɐݒ� */

  glBegin( GL_LINES ); /* �}�`�`��^�C�v�̐ݒ�J�n: �����ŕ`�� */
    /* x�� */
    glVertex2d( X0, 0.0 );
    glVertex2d( X1, 0.0 ); 

    /* y�� */
    glVertex2d( 0.0, Y0 );
    glVertex2d( 0.0, Y1 );

    /* x���̖ڐ��� */
    for( i = (int) X0; i <= (int) X1; i++ ) {  /* 1���݂�X0����X1�܂� */
      glVertex2d( i,  0.0 );
      glVertex2d( i,  0.5 );
    }

    /* y���̖ڐ��� */
    for( i = (int) Y0; i <= (int) Y1; i++ ) {  /* 1���݂�Y0����Y1�܂� */
      glVertex2d( 0.0, i );
      glVertex2d( 0.1, i );  /* ��ʂ̏c����ɉ����Ē����𒲐� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */
}

/* �֐�f(x)�̃O���t��`�悷��֐� */
void plot_f( void )
{
  double x, y, dx;

  dx = 0.1;   /* �Ȑ����v���b�g���鍏�ݕ� */

  /* f(x)�̋Ȑ���܂���ŕ`�� */
  glColor3f( 1.0, 0.0, 0.0 );  /* ���̐F��Ԃɐݒ� */
  glLineWidth( 3 );            /* ���̑�����3�s�N�Z���ɐݒ� */

  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( x = X0; x <= X1; x += dx ) {  /* x�̒l��dx���݂�X0����X1�܂ŕω� */
      y = f( x );
      glVertex2d( x, y );     /* f(x)��̒��_���W��ݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */
}

void display( void )
{
  glViewport( 0, 0, W_WIDTH, W_HEIGHT ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(�S��ʕ\��) */

  display_xy_axis( );  /* xy���Ɩڐ�����`��  */

  plot_f( );           /* �֐�f(x)�̃O���t��`�� */

  /* f(x)=0�̉��̈ʒu��傫�ȓ_�ŕ`�� */
  glColor3f( 0.0, 0.0, 1.0 );  /* �_�̐F��ɐݒ� */
  glPointSize( 15 );           /* �_�̑傫����15�~15�s�N�Z���ɐݒ� */

  glBegin( GL_POINTS );   /* �}�`�`��^�C�v�̐ݒ�J�n: �_�ŕ`�� */
    glVertex2d( x_solution, f( x_solution ) );     /* �_�̍��W��ݒ� */
  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  glFlush( );          /* �R�}���h�o�b�t�@�ɂ��܂��Ă��関���s�̖��߂����s */
}

int main( int argc, char *argv[] )
{
  int n;
  double x, dx, eps;

  eps = 1.0e-10; /* �I������l */
  dx = 1.0;

  n = 0;
  x = 2;  /* ���̏����l */
  printf( "�����l: x = %.15e f(x) = %.15e\n", x, f(x) );
  while( fabs(dx) > eps) {  /* �I���������(��������������������while�����p��) */
    dx = f( x ) / df( x );
    x -= dx;  /* ���̕␳ */
    n++;
    printf( "%d���: x = %.15e  dx = %.15e  f(x) = %.15e\n", n, x, dx, f(x) );
  }
  x_solution = x;    /* �ŏI�I�ȉ��̒l���O���[�o���ϐ��ɑ�� */
  printf( "\n�ŏI�I��f(x)=0�̉�\n" );
  printf( "x = %.15e  f(x) = %.15e\n", x_solution, f( x_solution ) );

  /* �O���t�Ɖ��̈ʒu��`�� */
  glutInit( &argc, argv );             /* OpenGL/GLUT���̏����� */
  glutInitDisplayMode ( GLUT_RGBA );   /* �f�B�X�v���C���[�h(�F�̎w��₻�̏����̕��@)�̐ݒ� */
  glutInitWindowSize ( W_WIDTH, W_HEIGHT );  /* ��ʃT�C�Y�̐ݒ� */
  glutInitWindowPosition( 100, 100 );  /* ���j�^���ォ��(100,100)�s�N�Z���̈ʒu�ɕ\�� */
  glutCreateWindow( argv[0] );         /* main�֐��̈����œn�������s�t�@�C��������ʂ̖��O�Ƃ���*/

  glClearColor ( 1.0, 1.0, 1.0, 0.0 );  /* ��ʂ̔w�i�F�𔒂ɐݒ� */
  glClear( GL_COLOR_BUFFER_BIT ); /* �J���[�o�b�t�@���N���A(�w�i��h��Ԃ�) */

  /* ���[���h���W�n�����K���f�o�C�X���W�n�ւ̓��e�ݒ� */ 
  glMatrixMode( GL_PROJECTION );       /* ���e�ϊ����[�h�ɐݒ� */
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ�(X0<x<X1, Y0<y<Y1) */

  glutDisplayFunc( display );

  glutMainLoop( );

  return 0;
}

