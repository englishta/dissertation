/* ���W�n�Ɠ��e�ϊ��֐� */

#include <math.h>     /* ���w�֐��̃w�b�_�t�@�C���̓ǂݍ��� */
#include <GL/freeglut.h>  /* OpenGL/freeGLUT�̃w�b�_�t�@�C���̓ǂݍ��� */

#define W_WIDTH  800  /* ��ʂ̕�(width)[�s�N�Z��] */
#define W_HEIGHT 400  /* ��ʂ̍���(height)[�s�N�Z��] */

/* OpenGL�ł͉~��`���֐����Ȃ��̂Œ��S( xc, yc ), ���ar�̉~��`���֐������� */
void circle( double xc, double yc, double r )  
{
  int i;
  double x, y;

  glBegin( GL_LINE_LOOP ); /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( i = 0; i < 360; i++ ) {  /* �~����̒��_��1�x���݂�360�ݒ� */
      x = xc + r * cos( 2.0 * M_PI * i / 360.0 ); /* ���_��x���W */
      y = yc + r * sin( 2.0 * M_PI * i / 360.0 ); /* ���_��y���W */
      glVertex2d( x, y );                         /* ���_�̍��W(x,y)��ݒ� */
    }

  glEnd();  /* �}�`�`��^�C�v�̐ݒ�I�� */
}

/* �`�悷��}�`���֐����ɋL�q */
void display( void )
{
	glViewport( 20, 20, 400, 200 );
  glColor3f( 1.0, 0.0, 1.0 );  /* �}�`�̐F���}�[���^(�Ԏ�)�ɐݒ� */
  glPointSize( 25 );  /* �_�̑傫����25�~25�s�N�Z���ɐݒ� */

  glBegin( GL_POINTS ); /* �}�`�`��^�C�v�̐ݒ�J�n: �X�̓_ */
    glVertex2f(  80.0, 75.0 );
    glVertex2f( 100.0, 75.0 );  
    glVertex2f( 120.0, 75.0 );  
  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  glColor3f( 0.8, 0.8, 0.8 );  /* �}�`�̐F�𖾂邢�D�F�ɐݒ� */

  glBegin( GL_QUADS ); /* �}�`�`��^�C�v�̐ݒ�J�n: �l�p�`(�h��Ԃ�) */
    /* �l�p�`��4���_���w�� */
    glVertex2f( 20.0, 20.0 );
    glVertex2f( 80.0, 20.0 );
    glVertex2f( 80.0, 50.0 );
    glVertex2f( 20.0, 50.0 );
  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  glColor3f( 1.0, 0.84, 0.0 );  /* �}�`�̐F�����F�ɐݒ� */
  glLineWidth( 5 );  /* ���̑�����5�s�N�Z���ɐݒ� */

  circle( 150.0, 30.0, 20.0 ); /* ����֐����g�p���Ē��S(150,50),���a20�̉~��`��  */

  glFlush( );  /* �R�}���h�o�b�t�@�ɂ��܂��Ă��関���s�̖��߂����s */
}

int main( int argc, char *argv[] )
{
  glutInit( &argc, argv );             /* OpenGL/GLUT���̏����� */
  glutInitDisplayMode ( GLUT_RGBA );   /* �f�B�X�v���C���[�h(�F�̎w��₻�̏����̕��@)�̐ݒ� */
  glutInitWindowSize ( W_WIDTH, W_HEIGHT );   /* ��ʃT�C�Y�̐ݒ� */
  glutInitWindowPosition( 0.0, 0.0 );  /* ���j�^���ォ��(100,100)�s�N�Z���̈ʒu�ɕ\�� */
  glutCreateWindow( argv[0] );         /* main�֐��̈����œn�������s�t�@�C��������ʂ̖��O�Ƃ���*/

  glClearColor ( 1.0, 1.0, 1.0, 0.0 ); /* ��ʂ̔w�i�F�𔒂ɐݒ� */
  glClear( GL_COLOR_BUFFER_BIT );      /* �J���[�o�b�t�@���N���A(�w�i��h��Ԃ�) */

  /* ���[���h���W�n�����K���f�o�C�X���W�n�ւ̓��e�ݒ� */ 
  glMatrixMode( GL_PROJECTION );       /* ���e�ϊ����[�h�ɐݒ� */
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( 0.0, 200.0, 0.0, 100.0, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ�(0<x<200, 0<y<100) */

  glutDisplayFunc( display );          /* display�֐��̎��s���w�� */

  glutMainLoop( );                     /* ���͑҂���Ԃ̖������[�v(��ʂ̕\���𑱂���) */

  return 0;
}

