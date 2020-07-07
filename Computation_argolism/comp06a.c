/* �I�C���[�@�ɂ��1�K������������̐��l��@ */

#include <stdio.h>
#include <math.h>     /* ���w�֐��̃w�b�_�t�@�C���̓ǂݍ��� */
#include <GL/freeglut.h>  /* OpenGL/freeGLUT�̃w�b�_�t�@�C���̓ǂݍ��� */

#define W_WIDTH  600  /* ��ʂ̕�(width)[�s�N�Z��] */
#define W_HEIGHT 400  /* ��ʂ̍���(height)[�s�N�Z��] */

#define X0  -1.0  /* x���̍��[(�ŏ��l) */
#define X1  11.0  /* x���̉E�[(�ő�l) */
#define Y0  -0.5  /* y���̉��[(�ŏ��l) */
#define Y1   2.0  /* y���̏�[(�ő�l) */

/* ����������f(t, x)�̒�` */
double f( double a, double c, double t, double x )
{
  double r;

  r = a*(c-x)*x;

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
      glVertex2d( i,  0.1 );
    }

    /* y���̖ڐ��� */
    for( i = (int) Y0; i <= (int) Y1; i++ ) {  /* 1���݂�Y0����Y1�܂� */
      glVertex2d( 0.0, i );
      glVertex2d( 0.3, i );  /* ��ʂ̏c����ɉ����Ē����𒲐� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */
}

/* �����������̐��l���̃O���t��`�悷��֐� */
void display( void )
{
  double t, dt, x, x0, t0, t_end;
  double a, c;

  glViewport( 0, 0, W_WIDTH, W_HEIGHT ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(�S��ʕ\��) */

  display_xy_axis( );  /* xy���Ɩڐ�����`��  */

  /* �����������̐��l���̃O���t��`�� */
  a = 1;  /* �p�����[�^�̐ݒ� */
  c = 1;  /* �p�����[�^�̐ݒ� */
  x0 = 0.1;  /* �����l�̐ݒ� */

  printf( "�p�����[�^�F a = %f\n", a );
  printf( "�p�����[�^�F c = %f\n", c );
  printf( "�����l�F x0 = %f\n", x0 );

  /* �I�C���[�@�ɂ��1�K������������̐��l��@ */
  dt = 1.0e-2;  /* ���Ԃ̂����ݕ��̐ݒ�*/
  t0 = 0.0;     /* �V�~�����[�V�����̏��������̐ݒ� */
  t_end = 10.0;  /* �V�~�����[�V�����̏I�������̐ݒ� */

  /* �����������̐��l�����v�Z���Ȃ���܂���ŕ`�� */
  glColor3f( 1.0, 0.0, 0.0 );  /* ���̐F��Ԃɐݒ� */
  glLineWidth( 2 );            /* ���̑�����2�s�N�Z���ɐݒ� */

  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    x = x0;  /* �����l�̐ݒ� */

    for( t = t0; t <= t_end; t += dt ) { /* ����t�̒l��dt���݂�t0����t_end�܂ŕω� */
      glVertex2d( t, x );         /* ���l���𒸓_���W�Ƃ��Đݒ� */
      x += f( a, c, t, x ) * dt;  /* �I�C���[�@ */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  glFlush( );          /* �R�}���h�o�b�t�@�ɂ��܂��Ă��関���s�̖��߂����s */
}

int main( int argc, char *argv[] )
{

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

