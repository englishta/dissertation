/* �e�[���[�W�J�ɂ��֐��ߎ��ƃO���t�`�� */

#include <math.h>     /* ���w�֐��̃w�b�_�t�@�C���̓ǂݍ��� */
#include <GL/freeglut.h>  /* OpenGL/freeGLUT�̃w�b�_�t�@�C���̓ǂݍ��� */

#define W_WIDTH  800  /* ��ʂ̕�(width)[�s�N�Z��] */
#define W_HEIGHT 400  /* ��ʂ̍���(height)[�s�N�Z��] */

#define X0  -10  /* x���̍��[(�ŏ��l) */
#define X1   10  /* x���̉E�[(�ő�l) */
#define Y0   -3  /* y���̉��[(�ŏ��l) */
#define Y1    3  /* y���̏�[(�ő�l) */

#define M   0  /* �e�[���[�W�J�̓W�J����((2M+1)���܂�) */

/* �e�[���[�W�J�ɂ���(2m+1)���܂ł�sin(x)�֐��̋ߎ��l */
double Taylor_exp( double x, int m )
{
  int i, n;
  double a, y;

  y = 0.0;
  for( n = 0; n <= m; n++ ) {
    /* a=(2n+1)!=1�~2�~...�~(2n+1)�̌v�Z */
    a = 1.0;
    for( i = 1; i <= 2*n+1; i++ ) {
      a *= (double) i;
    }
   /* ��(2n+1)���̌v�Z */
    y += pow( -1.0, n ) * pow( x, 2*n+1 ) / a;
  }

  return y;
}

/* xy���Ɩڐ�����`�悷��֐� */
void display_xy_axis( void )
{
  int i;

  glColor3f( 0.0, 0.0, 0.0 );  /* ���̐F�����ɐݒ� */

  glBegin( GL_LINES ); /* �}�`�`��^�C�v�̐ݒ�J�n: �����ŕ`�� */
    /* x�� */
    glVertex2f( X0, 0.0 );
    glVertex2f( X1, 0.0 ); 

    /* y�� */
    glVertex2f( 0.0, Y0 );
    glVertex2f( 0.0, Y1 );

    /* x���̖ڐ��� */
    for( i = (int) X0; i <= (int) X1; i++ ) {  /* 1���݂�X0����X1�܂� */
      glVertex2f( i,  0.0 );
      glVertex2f( i,  0.1 );
    }

    /* y���̖ڐ��� */
    for( i = (int) Y0; i <= (int) Y1; i++ ) {  /* 1���݂�Y0����Y1�܂� */
      glVertex2f( 0.0, i );
      glVertex2f( 0.1 * W_WIDTH / W_HEIGHT, i );  /* ��ʂ̏c����ɉ����Ē����𒲐� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */
}

/* sin(x)�̋Ȑ��ƃe�[���[�W�J�ɂ��ߎ��Ȑ���`�悷��֐� */
void plot_sin( void )
{
  double x, y, dx;

  dx = 0.1;   /* �Ȑ����v���b�g���鍏�ݕ� */

  /* sin(x)�̋Ȑ���܂���ŕ`�� */
  glColor3f( 1.0, 0.0, 0.0 );  /* ���̐F��Ԃɐݒ� */

  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( x = X0; x <= X1; x += dx ) {  /* x�̒l��dx���݂�X0����X1�܂ŕω� */
      y = sin( x );
      glVertex2f( x, y );     /* sin(x)��̒��_���W��ݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  /* �e�[���[�W�J�ɂ��ߎ��Ȑ���܂���ŕ`�� */
  glColor3f( 0.0, 0.0, 1.0 );  /* ���̐F��ɐݒ� */

  glBegin( GL_LINE_STRIP );    /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( x = X0; x <= X1; x += dx ) {  /* x�̒l��dx���݂�X0����X1�܂ŕω� */
      y = Taylor_exp( x, M );  /* ��(2M+1)���܂ł̃e�[���[�W�J�ɂ��ߎ��l�̌v�Z */
      glVertex2f( x, y );      /* �ߎ��Ȑ���̒��_���W��ݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */
}

void display( void )
{
  glViewport( 0, 0, W_WIDTH, W_HEIGHT ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(�S��ʕ\��) */

  display_xy_axis( );  /* xy���Ɩڐ�����`��  */

  plot_sin( );         /* sin(x)�̋Ȑ��ƃe�[���[�W�J�ɂ��ߎ��Ȑ���`�� */

  glFlush( );          /* �R�}���h�o�b�t�@�ɂ��܂��Ă��関���s�̖��߂����s */
}

int main( int argc, char *argv[] )
{
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

