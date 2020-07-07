/* �����Q�E�N�b�^�@�ɂ��3���A��1�K������������̐��l��@ */
/* ���[�����c�������ƃJ�I�X */

#include <stdio.h>
#include <math.h>     /* ���w�֐��̃w�b�_�t�@�C���̓ǂݍ��� */
#include <GL/freeglut.h>  /* OpenGL/freeGLUT�̃w�b�_�t�@�C���̓ǂݍ��� */
 
#define N  3   /* �ϐ��̐� */
 
#define W_WIDTH  1000  /* ��ʂ̕�(width)[�s�N�Z��] */
#define W_HEIGHT  700  /* ��ʂ̍���(height)[�s�N�Z��] */

#define T_0    -2.0  /* ���Ԏ��̍��[(�ŏ��l) */
#define T_1    20.0  /* ���Ԏ��̉E�[(�ő�l) */
#define X0_0  -60.0  /* x0���̉��[(�ŏ��l) */
#define X0_1   60.0  /* x0���̏�[(�ő�l) */
#define X1_0  -80.0  /* x1���̉��[(�ŏ��l) */
#define X1_1   80.0  /* x1���̏�[(�ő�l) */
#define X2_0  -20.0  /* x2���̉��[(�ŏ��l) */
#define X2_1  150.0  /* x2���̏�[(�ő�l) */

typedef struct model_parameter { /* ���[�����c�������̌W���̂��߂̍\���̂̐錾��typedef�ɂ��ʖ��̐錾 */
  double a;
} ModelParameter;  /* �\���̂̕ʖ�(ModelParameter)���` */

struct plot_data {  /* �O���t�Ƀv���b�g����f�[�^�p�̍\���̂̐錾 */
  double t;     /* ����t�̒l��ۑ����郁���o */
  double x0;    /* x[0]�̒l��ۑ����郁���o */
  double x1;    /* x[1]�̒l��ۑ����郁���o */
  double x2;    /* x[2]�̒l��ۑ����郁���o */
} data[3000];       /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): �O���t�Ƀv���b�g����f�[�^���i�[ */
 
int n_time;         /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): �O���t�Ƀv���b�g����f�[�^�����i�[ */

/*====================================================*/
/* ���[�����c������                                   */
/*====================================================*/
double f( int i, ModelParameter param[], double t, double x[] )
{
  double r;

  if     ( i == 0 ) r = - param[0].a * ( x[0] - x[1] );  /* ������f0 */
  else if( i == 1 ) r = - x[0] * x[2] + param[1].a * x[0] - x[1];  /* ������f1 */
  else              r = x[0] * x[1] - param[2].a * x[2];  /* ������f2 */

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
void display_xy_axis( double x0, double x1, int ix, double y0, double y1 )
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
    for( i = (int) x0; i <= (int) x1; i += ix ) {  /* ix���݂�x0����x1�܂� */
      glVertex2d( i,  0.0 );
      glVertex2d( i,  5.0 );
    }

    /* y���̖ڐ��� */
    s = ( x1 - x0 ) / ( y1 - y0 ); /* ��ʂ̏c����̌v�Z */
    for( i = (int) y0; i <= (int) y1; i += 10 ) {  /* 10���݂�y0����y1�܂� */
      glVertex2d( 0.0, i );
      glVertex2d( 1.0 * s, i );  /* ��ʂ̏c����ɉ����Ē����𒲐� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */
}

void display( void )
{
  /* ���[���h���W�n�����K���f�o�C�X���W�n�ւ̓��e�ݒ� */ 
  glMatrixMode( GL_PROJECTION );       /* ���e�ϊ����[�h�ɐݒ� */

  /* �O���t1(x���Ɏ��ԁAy����x0�̒l)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( T_0, T_1, X0_0, X0_1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( 20, 2*W_HEIGHT/3+20, W_WIDTH-W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  display_xy_axis( T_0, T_1, 2, X0_0, X0_1 );   /* xy���Ɩڐ�����`��  */
  drawString2D( 2*T_1/3, -12.0, "time" );    /* x����time�ƃ��x����`�� */
  drawString2D( -1.5,  X0_1/2, "x[0]" );     /* y����x[0]�ƕ`�� */
  drawString2D( -0.5, -12.0, "0" );          /* ���_(0,0)��0�ƕ`�� */
  drawString2D(  9.6, -12.0, "10" );         /* x���̖ڐ���10��`�� */
  drawString2D( 19.6, -12.0, "20" );         /* x���̖ڐ���20��`�� */

  /* �O���t2(x���Ɏ��ԁAy����x1�̒l)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( T_0, T_1, X1_0, X1_1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( 20, W_HEIGHT/3+20, W_WIDTH-W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  display_xy_axis( T_0, T_1, 2, X1_0, X1_1 );   /* xy���Ɩڐ�����`��  */
  drawString2D( 2*T_1/3, -18.0, "time" );    /* x����time�ƃ��x����`�� */
  drawString2D( -1.5,  X1_1/2, "x[1]" );     /* y����x[1]�ƕ`�� */
  drawString2D( -0.5, -18.0, "0" );          /* ���_(0,0)��0�ƕ`�� */
  drawString2D(  9.6, -18.0, "10" );         /* x���̖ڐ���10��`�� */
  drawString2D( 19.6, -18.0, "20" );         /* x���̖ڐ���20��`�� */

  /* �O���t3(x���Ɏ��ԁAy����x2�̒l)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( T_0, T_1, X2_0, X2_1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( 20, 20, W_WIDTH-W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  display_xy_axis( T_0, T_1, 2, X2_0, X2_1 );   /* xy���Ɩڐ�����`��  */
  drawString2D( 2*T_1/3, -18.0, "time" );    /* x����time�ƃ��x����`�� */
  drawString2D( -1.5,  X2_1/2, "x[2]" );     /* y����x[2]�ƕ`�� */
  drawString2D( -0.5, -18.0, "0" );          /* ���_(0,0)��0�ƕ`�� */
  drawString2D(  9.6, -18.0, "10" );         /* x���̖ڐ���10��`�� */
  drawString2D( 19.6, -18.0, "20" );         /* x���̖ڐ���20��`�� */

  /* �O���t4(x����x0�Ay����x1)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( X0_0, X0_1, X1_0, X1_1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( W_WIDTH-W_HEIGHT/3+20, W_HEIGHT/3+20, W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  display_xy_axis( X0_0, X0_1, 10, X1_0, X1_1 );  /* xy���Ɩڐ�����`��  */
  drawString2D( X0_1-20.0, -20.0, "x[0]" );   /* x����x[0]�ƃ��x����`�� */
  drawString2D( -28.0, X1_1-20.0, "x[1]" );   /* y����x[1]�ƃ��x����`�� */
  drawString2D( -10.0, -18.0, "0" );          /* ���_(0,0)��0�ƕ`�� */

  /* �O���t5(x����x0�Ay����x2)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( X0_0, X0_1, X2_0, X2_1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( W_WIDTH-W_HEIGHT/3+20, 20, W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  display_xy_axis( X0_0, X0_1, 10, X2_0, X2_1 );  /* xy���Ɩڐ�����`��  */
  drawString2D( X0_1-20.0, -20.0, "x[0]" );   /* x����x[0]�ƃ��x����`�� */
  drawString2D( -28.0, X2_1-20.0, "x[2]" );   /* y����x[2]�ƃ��x����`�� */
  drawString2D( -10.0, -18.0, "0" );          /* ���_(0,0)��0�ƕ`�� */

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
  glOrtho( T_0, T_1, X0_0, X0_1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( 20, 2*W_HEIGHT/3+20, W_WIDTH-W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  /* �ϐ�x0�̎��ԕω�����Ńv���b�g */
  glLineWidth( 2 );            /* ���̑�����2�s�N�Z���ɐݒ� */
  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( data[n].t, data[n].x0 );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  /* �O���t2(x���Ɏ��ԁAy����x1�̒l)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( T_0, T_1, X1_0, X1_1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( 20, W_HEIGHT/3+20, W_WIDTH-W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  /* �ϐ�x1�̎��ԕω�����Ńv���b�g */
  glLineWidth( 2 );            /* ���̑�����2�s�N�Z���ɐݒ� */
  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( data[n].t, data[n].x1 );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  /* �O���t3(x���Ɏ��ԁAy����x2�̒l)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( T_0, T_1, X2_0, X2_1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( 20, 20, W_WIDTH-W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  /* �ϐ�x1�̎��ԕω�����Ńv���b�g */
  glLineWidth( 2 );            /* ���̑�����2�s�N�Z���ɐݒ� */
  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( data[n].t, data[n].x2 );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  /* �O���t4(x����x0�Ay����x1)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( X0_0, X0_1, X1_0, X1_1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( W_WIDTH-W_HEIGHT/3+20, W_HEIGHT/3+20, W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  /* (x0,x1)�̎��ԕω�����Ńv���b�g */
  glLineWidth( 1 );            /* ���̑�����1�s�N�Z���ɐݒ� */
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

  /* �O���t5(x����x0�Ay����x2)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( X0_0, X0_1, X2_0, X2_1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ� */
  glViewport( W_WIDTH-W_HEIGHT/3+20, 20, W_HEIGHT/3-40, W_HEIGHT/3-40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  /* (x0,x2)�̎��ԕω�����Ńv���b�g */
  glLineWidth( 1 );            /* ���̑�����1�s�N�Z���ɐݒ� */
  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( data[n].x0, data[n].x2 );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  /* �����l��傫���_�ŕ\�� */
  glPointSize( 10 );             /* �_�̑傫����10�~10�s�N�Z���ɐݒ� */

  glBegin( GL_POINTS );   /* �}�`�`��^�C�v�̐ݒ�J�n: �_�ŕ`�� */
    glVertex2d( data[0].x0, data[0].x2 );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

}

int main( int argc, char *argv[] )
{
  int i, m, n;
  double t, dt, t0, t_end;
  double x[N];  /* �ϐ� */
  ModelParameter param[N];  /* ���[�����c�������̃p�����[�^ */
  double k1[N], k2[N], k3[N], k4[N], xwork[N];  /* �����Q�E�N�b�^�@�̂��߂̕ϐ� */

  /* �O���t�B�b�N�X�̏����ݒ� */
  glutInit( &argc, argv );             /* OpenGL/GLUT���̏����� */
  glutInitDisplayMode ( GLUT_RGBA );   /* �f�B�X�v���C���[�h(�F�̎w��₻�̏����̕��@)�̐ݒ� */
  glutInitWindowSize ( W_WIDTH, W_HEIGHT );  /* ��ʃT�C�Y�̐ݒ� */
  glutInitWindowPosition( 100, 100 );  /* ���j�^���ォ��(100,100)�s�N�Z���̈ʒu�ɕ\�� */
  glutCreateWindow( argv[0] );         /* main�֐��̈����œn�������s�t�@�C��������ʂ̖��O�Ƃ���*/

  glClearColor ( 1.0, 1.0, 1.0, 0.0 );  /* ��ʂ̔w�i�F�𔒂ɐݒ� */
  glClear( GL_COLOR_BUFFER_BIT ); /* �J���[�o�b�t�@���N���A(�w�i��h��Ԃ�) */

  param[0].a = 10.0;    /* �p�����[�^�̐ݒ� */
  param[1].a = 80.0;    /* �p�����[�^�̐ݒ� */
  param[2].a = 8.0 / 3.0;    /* �p�����[�^�̐ݒ� */

  dt = 1.0e-4;  /* ���Ԃ̂����ݕ��̐ݒ�*/
  t0 = 0.0;     /* �V�~�����[�V�����̏��������̐ݒ� */
  t_end = T_1;  /* �V�~�����[�V�����̏I�������̐ݒ� */

  for( m = 0; m < 2; m++ ) {  /* �����l��ς��ăV�~�����[�V������2��J��Ԃ� */

    /* 1��ڂ�2��ڂ̃V�~�����[�V�����Őݒ��ς��� */
    if( m == 0 ) { /* 1��ڂ̃V�~�����[�V�����̏ꍇ */
      x[0] = -2.0;    /* �����l�̐ݒ�A */
      x[1] = 10.0;    /* �����l�̐ݒ�A */
      x[2] =  7.0;    /* �����l�̐ݒ�A */
      glColor3f( 1.0, 0.0, 0.0 );    /* �`�悷����̐F��Ԃɐݒ� */
    }
    else {         /* 2��ڂ̃V�~�����[�V�����̏ꍇ */
      x[0] = -2.001;  /* �����l�̐ݒ�B */
      x[1] = 10.0;    /* �����l�̐ݒ�B */
      x[2] =  7.0;    /* �����l�̐ݒ�B */
      glColor3f( 0.0, 0.0, 1.0 );    /* �`�悷����̐F��ɐݒ� */
    }

    /* �����Q�E�N�b�^�@�ɂ��A��1�K������������̐��l��@ */
    n = 0;          /* �J�E���^�[ */
    n_time = 0;     /* �O���t�Ƀv���b�g����f�[�^����0�ɏ����� */
    for( t = t0; t <= t_end; t += dt ) {

      if( n % 100 == 0 ) {  /* 100���1��O���t�Ƀv���b�g */
        data[n_time].t = t;      /* �O���t�Ƀv���b�g���鎞��t�̒l���\���̔z��data�̃����ot�ɕۑ� */
        data[n_time].x0 = x[0];  /* �O���t�Ƀv���b�g����x[0]�̒l���\���̔z��data�̃����ox0�ɕۑ� */
        data[n_time].x1 = x[1];  /* �O���t�Ƀv���b�g����x[1]�̒l���\���̔z��data�̃����ox1�ɕۑ� */
        data[n_time].x2 = x[2];  /* �O���t�Ƀv���b�g����x[2]�̒l���\���̔z��data�̃����ox2�ɕۑ� */
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

    /* �O���t�ɕ`�悷��f�[�^��ݒ� */
    graph( );

  }

  /* �O���t��`�� */
  glutDisplayFunc( display );

  glutMainLoop( );

  return 0;
}

