/* �[��������p�����~�����΂̌v�Z(��l�[�������̐����֐��͎���̏ꍇ)  */
#include <stdio.h>
#include <math.h>     /* ���w�֐��̃w�b�_�t�@�C���̓ǂݍ��� */
#include <GL/freeglut.h>  /* OpenGL/freeGLUT�̃w�b�_�t�@�C���̓ǂݍ��� */

#define A  48271   /* ���`�����@�̃p�����[�^�F�|���鐔 */
#define C  0       /* ���`�����@�̃p�����[�^�F������ */
#define M  2147483647   /* ���`�����@�̃p�����[�^�F���鐔 (2��31��-1) */

#define N  1000 /* �T���v����(�I���Ẳ�) */
 
#define W_WIDTH   600  /* ��ʂ̕�(width)[�s�N�Z��] */
#define W_HEIGHT  600  /* ��ʂ̍���(height)[�s�N�Z��] */

#define X0  -0.2  /* x���̍��[(�ŏ��l) */
#define X1   1.2  /* x���̉E�[(�ő�l) */
#define Y0  -0.2  /* y���̉��[(�ŏ��l) */
#define Y1   1.2  /* y���̏�[(�ő�l) */

/* �O���[�o���ϐ� (�ǂ̊֐��̒��ł��g�p�\) */
unsigned int X;    /* ���`�����@�Ő��������񕉂̐����l��l�[�������� */

/*====================================================*/
/* ���`�����@�ɂ�鐮���l��l�[�������̐����֐�(����) */
/*====================================================*/
unsigned int myrand( void )
{
  X = ( A * X + C ) % M;

  return X;
}

/*====================================================*/
/* �����l��l�[�������̏����l��ݒ肷��֐�(����)     */
/*====================================================*/
void mysrand( unsigned int x0 )
{
  X = x0;
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
void display_xy_axis( double x0, double x1, double y0, double y1, double dx, double dy )
{
  double r, s;

  glColor3f( 0.0, 0.0, 0.0 );  /* ���̐F�����ɐݒ� */

  glBegin( GL_LINES ); /* �}�`�`��^�C�v�̐ݒ�J�n: �����ŕ`�� */
    /* x�� */
    glVertex2d( x0, 0.0 );
    glVertex2d( x1, 0.0 ); 

    /* y�� */
    glVertex2d( 0.0, y0 );
    glVertex2d( 0.0, y1 );

    /* x���̖ڐ��� */
    for( r = (int) x0; r <= (int) x1; r += dx ) {  /* dx���݂�x0����x1�܂� */
      glVertex2d( r,  0.0 );
      glVertex2d( r,  0.05 );
    }

    /* y���̖ڐ��� */
    s = ( x1 - x0 ) / ( y1 - y0 ); /* ��ʂ̏c����̌v�Z */
    for( r = (int) y0; r <= (int) y1; r += dy ) {  /* dy���݂�y0����y1�܂� */
      glVertex2d( 0.0, r );
      glVertex2d( 0.05 * s, r );  /* ��ʂ̏c����ɉ����Ē����𒲐� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */
}

void display( void )
{
  /* �O���t(x����x�Ay����y�̒l)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( 20, 20, W_WIDTH-40, W_HEIGHT-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  display_xy_axis( X0, X1, Y0, Y1, 0.2, 0.2 );         /* xy���Ɩڐ�����`��  */
  drawString2D(  0.5, -0.15, "x" );      /* x����x�ƃ��x����`�� */
  drawString2D( -0.15, 0.5, "y" );       /* y����y�ƕ`�� */
  drawString2D( -0.1, -0.1, "0" );       /* ���_(0,0)��0�ƕ`�� */
  drawString2D(  1.0, -0.1, "1" );       /* (1,0)��1�ƕ`�� */
  drawString2D( -0.1,  1.0, "1" );       /* (0,1)��1�ƕ`�� */

  glFlush( );          /* �R�}���h�o�b�t�@�ɂ��܂��Ă��関���s�̖��߂����s */
}

/* main�֐� */
int main( int argc, char *argv[] )
{
  int i, m, n;
  double x, y, pi;

  /* �O���t�B�b�N�X�̏����ݒ� */
  glutInit( &argc, argv );             /* OpenGL/GLUT���̏����� */
  glutInitDisplayMode ( GLUT_RGBA );   /* �f�B�X�v���C���[�h(�F�̎w��₻�̏����̕��@)�̐ݒ� */
  glutInitWindowSize ( W_WIDTH, W_HEIGHT );  /* ��ʃT�C�Y�̐ݒ� */
  glutInitWindowPosition( 100, 100 );  /* ���j�^���ォ��(100,100)�s�N�Z���̈ʒu�ɕ\�� */
  glutCreateWindow( argv[0] );         /* main�֐��̈����œn�������s�t�@�C��������ʂ̖��O�Ƃ���*/

  glClearColor ( 1.0, 1.0, 1.0, 0.0 );  /* ��ʂ̔w�i�F�𔒂ɐݒ� */
  glClear( GL_COLOR_BUFFER_BIT ); /* �J���[�o�b�t�@���N���A(�w�i��h��Ԃ�) */

  /* ���[���h���W�n�����K���f�o�C�X���W�n�ւ̓��e�ݒ� */ 
  glMatrixMode( GL_PROJECTION );       /* ���e�ϊ����[�h�ɐݒ� */

  /* �O���t(x����x�Ay����y)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( 20, 20, W_WIDTH-40, W_HEIGHT-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  printf( "\n---<< ������p���ĉ~�����΂��v�Z���� >>---\n" );

  glPointSize( 3 );      /* �_�̑傫����3�~3�s�N�Z���ɐݒ� */
  glBegin( GL_POINTS );  /* �}�`�`��^�C�v�̐ݒ�J�n: �_�ŕ`�� */

  mysrand( 1 );  /* �����l�����̏����l(����)��ݒ� */
  m = 0;         /* �_(x,y)��4���~�̓����ɓ������񐔂𐔂���J�E���^�̏����l�ݒ� */

  for( n = 0; n < N; n++ )  {  /* �I���Ă�N��J��Ԃ� */
    x = (double) myrand( ) / M;  /* ���[0,1)��̎����l�����𐶐���x�ɑ�� */
    y = (double) myrand( ) / M;  /* ���[0,1)��̎����l�����𐶐���y�ɑ�� */

    if( x * x + y * y < 1.0 ) { /* �����_(x,y)��4���~�̓����ɓ���� */
      m++;    /* ������̃J�E���^m��1���Z */
      glColor3f(1.0, 0.0, 0.0);	/* �`�悷��_�̐F��Ԃɐݒ� */
    }
    else {  /* �����_(x,y)��4���~�̊O�ɂ���� */
      glColor3f(0.0, 0.0, 1.0);	/* �`�悷��_�̐F��ɐݒ� */
    }

    glVertex2d( x, y );       /* �O���t�F�_(x,y)�𒸓_���W�Ƃ��Đݒ� */
  }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  printf( "%d��̂����_(x,y)��4���~�̓����ɓ������񐔂�%d��ł�\n", N, m);
  pi = 4.0 * m / (double) N;  /* �~�����΂̋ߎ��l */
  printf( "�~�����΂̋ߎ��l�F4*%d/\%d = %.15f\n", m, N, pi );
  printf( "�~�����΂̐��m�Ȓl�F�� = %.15f\n", M_PI );

  /* �O���t��`�� */
  glutDisplayFunc( display );

  glutMainLoop( );

  return 0;
}

