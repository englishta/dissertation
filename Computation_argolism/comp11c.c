/* �[��������p�������l�ϕ��@ */
#include <stdio.h>
#include <math.h>     /* ���w�֐��̃w�b�_�t�@�C���̓ǂݍ��� */
#include <stdlib.h>   /* �����𔭐�������֐�rand�Asrand�𗘗p���邽�߂ɕK�v�ȃw�b�_�t�@�C�� */
#include <GL/freeglut.h>  /* OpenGL/freeGLUT�̃w�b�_�t�@�C���̓ǂݍ��� */
 
#define N  10000 /* �T���v����(�I���Ẳ�) */

#define W_WIDTH   800  /* ��ʂ̕�(width)[�s�N�Z��] */
#define W_HEIGHT  600  /* ��ʂ̍���(height)[�s�N�Z��] */

#define X0  -1.0  /* x���̍��[(�ŏ��l) */
#define X1   7.0  /* x���̉E�[(�ő�l) */
#define Y0  -0.5  /* y���̉��[(�ŏ��l) */
#define Y1   5.0  /* y���̏�[(�ő�l) */

/* ��ϕ��֐�f(x)�̒�` */
double f( double x )
{
  double r;

  r = 4.0 * exp( - x / 5.0 );  /* ��ϕ��֐�f(x)�̎� */

  return r;
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
      glVertex2d( r,  0.1 );
    }

    /* y���̖ڐ��� */
    s = ( x1 - x0 ) / ( y1 - y0 ); /* ��ʂ̏c����̌v�Z */
    for( r = (int) y0; r <= (int) y1; r += dy ) {  /* dy���݂�y0����y1�܂� */
      glVertex2d( 0.0, r );
      glVertex2d( 0.1 * s, r );  /* ��ʂ̏c����ɉ����Ē����𒲐� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */
}

void display( void )
{
  double x;

  /* �O���t(x����x�Ay����y�̒l)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( 20, 20, W_WIDTH-40, W_HEIGHT-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  display_xy_axis( X0, X1, Y0, Y1, 1.0, 1.0 );         /* xy���Ɩڐ�����`��  */
  drawString2D( X1/2, Y0/2, "x" );           /* x����x�ƃ��x����`�� */
  drawString2D( X0/2, Y1/2, "y" );           /* y����y�ƕ`�� */
  drawString2D( X0/2, Y0/2, "0" );           /* ���_(0,0)��0�ƕ`�� */

  glColor3f( 0.0, 0.0, 0.0 );  /* ���̐F�����ɐݒ� */
  glBegin( GL_LINE_STRIP ); /* �}�`�`��^�C�v�̐ݒ�J�n: �����ŕ`�� */
    for( x = X0; x <= X1; x += 0.05 )  {  /* �֐�y=f(x)�̕`�� */
      glVertex2d( x, f(x) );
    }
  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  glFlush( );          /* �R�}���h�o�b�t�@�ɂ��܂��Ă��関���s�̖��߂����s */
}

/* main�֐� */
int main( int argc, char *argv[] )
{
  int m, n;
  double a, b, x, y, ymax, s;

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

  glPointSize( 3 );       /* �_�̑傫����3�~3�s�N�Z���ɐݒ� */
  glBegin( GL_POINTS );   /* �}�`�`��^�C�v�̐ݒ�J�n: �_�ŕ`�� */

  a = 1.0;     /* �ϕ����[a,b]�̎n�_�̐ݒ� */
  b = 5.0;     /* �ϕ����[a,b]�̏I�_�̐ݒ� */
  ymax = 4.0;  /* �I���Ă̍��������͈̔͂�[0,ymax] */

  printf( "---<< �[��������p�������l�ϕ��@ >>---\n" );
  printf( "�ϕ��͈́F[a, b] = [%f, %f]\n", a, b );
  printf( "ymax = %f\n\n", ymax );

  srand(1);  /* �����l�����̏����l(����)��ݒ� */
  m = 0;     /* �_(x,y)��������ł���񐔂𐔂���J�E���^�̏����l�ݒ� */

  for( n = 0; n < N; n++ )  {  /* �I���Ă�N��J��Ԃ� */
    x = (double) rand( ) / RAND_MAX;  /* ���[0,1]��̎����l��l�����𐶐���x�ɑ�� */
    x = a + ( b - a ) * x;            /* ���[a,b]��̎����l��l�����ɕϊ� */

    y = (double) rand( ) / RAND_MAX;  /* ���[0,1]��̎����l��l�����𐶐���y�ɑ�� */
    y = ymax * y;                     /* ���[0,ymax]��̎����l��l�����ɕϊ� */

    if( y < f( x ) ) { /* �����_(x,y)��������ł���� */
      m++;             /* ������̃J�E���^m��1���Z */
      glColor3f(1.0, 0.0, 0.0);	/* �`�悷��_�̐F��Ԃɐݒ� */
    }
    else {  /* �����_(x,y)���͂���ł���� */
      glColor3f(0.0, 0.0, 1.0);	/* �`�悷��_�̐F��ɐݒ� */
    }

    glVertex2d( x, y );       /* �O���t�F�_(x,y)�𒸓_���W�Ƃ��Đݒ� */
  }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  printf( "%d��̂����_(x,y)��������ł���񐔂�%d��ł�\n", N, m);
  s = m * ( b - a ) * ymax / (double) N;     /* ��ϕ��̋ߎ��l */
  printf( "��ϕ��̋ߎ��l�Fs = %.15f\n", s );

  /* �O���t��`�� */
  glutDisplayFunc( display );

  glutMainLoop( );

  return 0;
}

