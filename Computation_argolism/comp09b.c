/* �����Q�E�N�b�^�@�ɂ��2�K������������̐��l��@ */
/* �t�@���E�f���E�|�[���������ƋɌ��O�� */

#include <stdio.h>
#include <math.h>     /* ���w�֐��̃w�b�_�t�@�C���̓ǂݍ��� */
#include <GL/freeglut.h>  /* OpenGL/freeGLUT�̃w�b�_�t�@�C���̓ǂݍ��� */
 
#define N  2   /* �ϐ��̐� */
 
#define W_WIDTH  1000  /* ��ʂ̕�(width)[�s�N�Z��] */
#define W_HEIGHT  600  /* ��ʂ̍���(height)[�s�N�Z��] */

#define X0  -8.0  /* x���̍��[(�ŏ��l) */
#define X1 100.0  /* x���̉E�[(�ő�l) */
#define Y0  -5.0  /* y���̉��[(�ŏ��l) */
#define Y1   5.0  /* y���̏�[(�ő�l) */

struct plot_data {     /* �O���t�Ƀv���b�g����f�[�^�p�̍\���̂̐錾 */
  double t;     /* ����t�̒l��ۑ����郁���o */
  double x0;    /* x[0]�̒l��ۑ����郁���o */
  double x1;    /* x[1]�̒l��ۑ����郁���o */
} data[2000];          /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): �O���t�Ƀv���b�g����f�[�^���i�[ */
 
int n_time;            /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): �O���t�Ƀv���b�g����f�[�^�����i�[ */

/*====================================================*/
/* �t�@���E�f���E�|�[���������@�@�@�@�@�@�@�@�@�@�@�@ */
/*====================================================*/
double f( int i, double mu, double t, double x[] )
{
  double r;

  if( i == 0 ) r = x[1];  /* i=0: ������f0 */
  else         r = mu * ( 1.0 -  x[0] * x[0] ) * x[1] - x[0];  /* i=1: ������f1 */

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
    for( i = (int) x0; i <= (int) x1; i++ ) {  /* 1���݂�x0����x1�܂� */
      glVertex2d( i,  0.0 );
      glVertex2d( i,  0.2 );
    }

    /* y���̖ڐ��� */
    s = ( x1 - x0 ) / ( y1 - y0 ); /* ��ʂ̏c����̌v�Z */
    for( i = (int) y0; i <= (int) y1; i++ ) {  /* 1���݂�y0����y1�܂� */
      glVertex2d( 0.0, i );
      glVertex2d( 0.1 * s, i );  /* ��ʂ̏c����ɉ����Ē����𒲐� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */
}

void display( void )
{
  /* ���[���h���W�n�����K���f�o�C�X���W�n�ւ̓��e�ݒ� */ 
  glMatrixMode( GL_PROJECTION );       /* ���e�ϊ����[�h�ɐݒ� */

  /* �O���t1(x���Ɏ��ԁAy����x0�̒l)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( 20, W_HEIGHT/2+20, W_WIDTH-W_HEIGHT/2-40, W_HEIGHT/2-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  display_xy_axis( X0, X1, Y0, Y1 );         /* xy���Ɩڐ�����`��  */
  drawString2D(  3.0,  4.0, "x[0]=x" );      /* y����x[0]�ƕ`�� */
  drawString2D( 2*X1/3, -1.0, "time" );      /* x����time�ƃ��x����`�� */
  drawString2D( -2.8, -0.8, "0" );           /* ���_(0,0)��0�ƕ`�� */
  drawString2D( 48.0, -0.8, "50" );          /* x���̖ڐ���50��`�� */
  drawString2D( 97.0, -0.8, "100" );         /* x���̖ڐ���100��`�� */
  drawString2D( -4.8, -3.2, "-3" );          /* y���̖ڐ���-3��`�� */
  drawString2D( -2.8,  2.8, "3" );           /* y���̖ڐ���3��`�� */

  /* �O���t2(x���Ɏ��ԁAy����x1�̒l)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( 20, 20, W_WIDTH-W_HEIGHT/2-40, W_HEIGHT/2-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  display_xy_axis( X0, X1, Y0, Y1 );         /* xy���Ɩڐ�����`��  */
  drawString2D(  3.0,  4.0, "x[1]=dx/dt" );  /* y����x[1]�ƕ`�� */
  drawString2D( 2*X1/3, -1.0, "time" );      /* x����time�ƃ��x����`�� */
  drawString2D( -2.8, -0.8, "0" );           /* ���_(0,0)��0�ƕ`�� */
  drawString2D( 48.0, -0.8, "50" );          /* x���̖ڐ���50��`�� */
  drawString2D( 97.0, -0.8, "100" );         /* x���̖ڐ���100��`�� */
  drawString2D( -4.8, -3.2, "-3" );          /* y���̖ڐ���-3��`�� */
  drawString2D( -2.8,  2.8, "3" );           /* y���̖ڐ���3��`�� */

  /* �O���t3(x����x0�Ay����x1)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( Y0, Y1, Y0, Y1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( W_WIDTH-W_HEIGHT/2+20, W_HEIGHT/2+20, W_HEIGHT/2-40, W_HEIGHT/2-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  display_xy_axis( Y0, Y1, Y0, Y1 );  /* xy���Ɩڐ�����`��  */
  drawString2D( 3.5, -1.2, "x[0]" );        /* x����x[0]�ƃ��x����`�� */
  drawString2D( -1.8, 4.0, "x[1]" );        /* y����x[1]�ƃ��x����`�� */
  drawString2D( -0.5, -0.8, "0" );          /* ���_(0,0)��0�ƕ`�� */

  glFlush( );          /* �R�}���h�o�b�t�@�ɂ��܂��Ă��関���s�̖��߂����s */
}

/* �O���t�ɕ`�悷��f�[�^��ݒ� */
void graph( void )
{
  int n;

  /* ���[���h���W�n�����K���f�o�C�X���W�n�ւ̓��e�ݒ� */ 
  glMatrixMode( GL_PROJECTION );       /* ���e�ϊ����[�h�ɐݒ� */

  /* �O���t1(x���Ɏ��ԁAy����x0�̒l)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( 20, W_HEIGHT/2+20, W_WIDTH-W_HEIGHT/2-40, W_HEIGHT/2-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */
  /* �ϐ�x0�̎��ԕω�����Ńv���b�g */
  glLineWidth( 2 );            /* ���̑�����2�s�N�Z���ɐݒ� */
  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( data[n].t, data[n].x0 );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  /* �O���t2(x���Ɏ��ԁAy����x1�̒l)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( 20, 20, W_WIDTH-W_HEIGHT/2-40, W_HEIGHT/2-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  /* �ϐ�x1�̎��ԕω�����Ńv���b�g */
  glLineWidth( 2 );            /* ���̑�����2�s�N�Z���ɐݒ� */
  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( data[n].t, data[n].x1 );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  /* �O���t3(x����x0�Ay����x1)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( Y0, Y1, Y0, Y1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( W_WIDTH-W_HEIGHT/2+20, W_HEIGHT/2+20, W_HEIGHT/2-40, W_HEIGHT/2-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  /* (x0,x1)�̎��ԕω�����Ńv���b�g */
  glLineWidth( 2 );            /* ���̑�����2�s�N�Z���ɐݒ� */
  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( data[n].x0, data[n].x1 );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  /* �����l��傫���_�ŕ\�� */
  glPointSize( 10 );             /* �_�̑傫����10�~10�s�N�Z���ɐݒ� */

  glBegin( GL_POINTS );   /* �}�`�`��^�C�v�̐ݒ�J�n: �_�ŕ`�� */
    glVertex2d( data[0].x0, data[0].x1 );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */
}

int main( int argc, char *argv[] )
{
  int i, m, n;
  double t, dt, t0, t_end;
  double x[N];  /* �ϐ� */
  double mu;  /* �t�@���E�f���E�|�[���������̃p�����[�^ */
  double k1[N], k2[N], k3[N], k4[N], xwork[N];  /* �����Q�E�N�b�^�@�̂��߂̕ϐ� */

  /* �O���t�B�b�N�X�̏����ݒ� */
  glutInit( &argc, argv );             /* OpenGL/GLUT���̏����� */
  glutInitDisplayMode ( GLUT_RGBA );   /* �f�B�X�v���C���[�h(�F�̎w��₻�̏����̕��@)�̐ݒ� */
  glutInitWindowSize ( W_WIDTH, W_HEIGHT );  /* ��ʃT�C�Y�̐ݒ� */
  glutInitWindowPosition( 100, 100 );  /* ���j�^���ォ��(100,100)�s�N�Z���̈ʒu�ɕ\�� */
  glutCreateWindow( argv[0] );         /* main�֐��̈����œn�������s�t�@�C��������ʂ̖��O�Ƃ���*/

  glClearColor ( 1.0, 1.0, 1.0, 0.0 );  /* ��ʂ̔w�i�F�𔒂ɐݒ� */
  glClear( GL_COLOR_BUFFER_BIT ); /* �J���[�o�b�t�@���N���A(�w�i��h��Ԃ�) */

  mu = 2.0;    /* �t�@���E�f���E�|�[���������̃p�����[�^�̐ݒ� */

  dt = 1.0e-3;     /* ���Ԃ̂����ݕ��̐ݒ�*/
  t0 = 0.0;        /* �V�~�����[�V�����̏��������̐ݒ� */
  t_end = X1;      /* �V�~�����[�V�����̏I�������̐ݒ� */

  for( m = 0; m < 3; m++ ) {  /* �����l��ς��ăV�~�����[�V������3��J��Ԃ� */

    /* 1��ځA2��ځA3��ڂ̃V�~�����[�V�����Őݒ��ς��� */
    if( m == 0 ) {      /* 1��ڂ̃V�~�����[�V�����̏ꍇ */
      x[0] = 3.5;  /* �����l�̐ݒ� */
      x[1] = 3.0;  /* �����l�̐ݒ� */
      glColor3f( 1.0, 0.0, 0.0 );    /* �`�悷����̐F��Ԃɐݒ� */
    }
    else if( m == 1 ) { /* 2��ڂ̃V�~�����[�V�����̏ꍇ */
      x[0] =  1.0; /* �����l�̐ݒ� */
      x[1] = -2.0; /* �����l�̐ݒ� */
      glColor3f( 0.0, 0.0, 1.0 );    /* �`�悷����̐F��ɐݒ� */
    }
    else {              /* 3��ڂ̃V�~�����[�V�����̏ꍇ */
      x[0] = -1.0; /* �����l�̐ݒ� */
      x[1] = -1.0; /* �����l�̐ݒ� */
      glColor3f( 0.0, 0.7, 0.0 );    /* �`�悷����̐F��Z���΂ɐݒ� */
    }

    /* �����Q�E�N�b�^�@�ɂ��A��1�K������������̐��l��@ */
    n = 0;         /* �J�E���^�[ */
    n_time = 0;    /* �O���t�Ƀv���b�g����f�[�^����0�ɏ����� */
    for( t = t0; t <= t_end; t += dt ) {

      if( n % 100 == 0 ) {  /* 100���1��O���t�Ƀv���b�g */
        data[n_time].t = t;      /* �O���t�Ƀv���b�g���鎞��t�̒l���\���̔z��data�̃����ot�ɕۑ� */
        data[n_time].x0 = x[0];  /* �O���t�Ƀv���b�g����x[0]�̒l���\���̔z��data�̃����ox0�ɕۑ� */
        data[n_time].x1 = x[1];  /* �O���t�Ƀv���b�g����x[1]�̒l���\���̔z��data�̃����ox1�ɕۑ� */
        n_time++;                /* �O���t�Ƀv���b�g����f�[�^����1���Z */
      }
      n++;  /* �J�E���^�[��1���Z */

      /* �����Q�E�N�b�^�@��1�i�ځF�S�Ă�k1[i](�n�_�ł̌X��)�̌v�Z */
      for( i = 0; i < N; i++ ) k1[i] = f( i, mu, t, x ) * dt;

      /* k2[i]�̂��߂̒��_1(xwork[i])�̌v�Z  */
      for( i = 0; i < N; i++ ) xwork[i] = x[i] + 0.5 * k1[i];

      /* �����Q�E�N�b�^�@��2�i�ځF�S�Ă�k2[i](���_1�ł̌X��)�̌v�Z */
      for( i = 0; i < N; i++ ) k2[i] = f( i, mu, t + 0.5 * dt, xwork ) * dt;

      /* k3[i]�̂��߂̒��_2(xwork[i])�̌v�Z  */
      for( i = 0; i < N; i++ ) xwork[i] = x[i] + 0.5 * k2[i];

      /* �����Q�E�N�b�^�@��3�i�ځF�S�Ă�k3[i](���_2�ł̌X��)�̌v�Z */
      for( i = 0; i < N; i++ ) k3[i] = f( i, mu, t + 0.5 * dt, xwork ) * dt;

      /* k4[i]�̂��߂̏I�_(xwork[i])�̌v�Z  */
      for( i = 0; i < N; i++ ) xwork[i] = x[i] + k3[i];

      /* �����Q�E�N�b�^�@��4�i�ځF�S�Ă�k4[i](�I�_�ł̌X��)�̌v�Z */
      for( i = 0; i < N; i++ ) k4[i] = f( i, mu, t + dt, xwork ) * dt;

      /* �����Q�E�N�b�^�@ */
      for( i = 0; i < N; i++ ) x[i] += ( k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i] ) / 6.0;

    }

    /* �O���t�ɕ`�悷��f�[�^��ݒ� */
    graph( );

  }

  /* �O���t��`�� */
  glutDisplayFunc( display );

  glutMainLoop( );

  return 0;
}

