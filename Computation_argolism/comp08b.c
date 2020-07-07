/* �����Q�E�N�b�^�@�ɂ��3���A��1�K������������̐��l��@ */
/* SIR���f���ɂ�銴���Ǘ��s�̃V�~�����[�V���� */

#include <stdio.h>
#include <math.h>     /* ���w�֐��̃w�b�_�t�@�C���̓ǂݍ��� */
#include <GL/freeglut.h>  /* OpenGL/freeGLUT�̃w�b�_�t�@�C���̓ǂݍ��� */

#define N  3   /* �ϐ��̐�(�������Ґ��A�����Ґ��A�񕜎Ґ�) */

#define W_WIDTH   700  /* ��ʂ̕�(width)[�s�N�Z��] */
#define W_HEIGHT  400  /* ��ʂ̍���(height)[�s�N�Z��] */

#define X0 -10.0  /* x���̍��[(�ŏ��l) */
#define X1  90.0  /* x���̉E�[(�ő�l) */
#define Y0  -0.2  /* y���̉��[(�ŏ��l) */
#define Y1   1.2  /* y���̏�[(�ő�l) */

typedef struct model_parameter { /* SIR���f���̃p�����[�^�̂��߂̍\���̂̐錾��typedef�ɂ��ʖ��̐錾 */
  double beta;    /* ������ */
  double gamma;   /* �񕜗� */
} ModelParameter;  /* �\���̂̕ʖ�(ModelParameter)���` */

double gt[1000], gx0[1000], gx1[1000], gx2[1000];  /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): �O���t�Ƀv���b�g����f�[�^���i�[ */
int n_time;                             /* �O���[�o���ϐ�(�ǂ̊֐��̒��ł��g�p�\): �O���t�Ƀv���b�g����f�[�^�����i�[ */

/*=========================================================*/
/* i�Ԗڂ̗v�fx[i]�ɑ΂������������f(i, t, x)�̒�`       */
/* �e�ϐ��̒l�͔z��x[i]�������Ƃ��ēn��                    */
/* SIR���f���̃p�����[�^�͍\���̕ϐ�param�������Ƃ��ēn��  */
/*=========================================================*/
double f( int i, ModelParameter param, double t, double x[] )
{
  double r;

  if     ( i == 0 ) r = - param.beta * x[0] * x[1];                    /* ��������(x[0])�̔��������� */
  else if( i == 1 ) r = param.beta * x[0] * x[1] - param.gamma * x[1]; /* ������(x[1])�̔��������� */
  else              r = param.gamma * x[1];                            /* �񕜎�(x[2])�̔��������� */

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
    for( i = 0; i <= (int) x1; i += 10 ) {  /* 10���݂�0����x1�܂� */
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

  /* �O���t(x���Ɏ��ԁAy���Ɋe�l���䗦�̒l)�̓��e�ݒ� */ 
  glLoadIdentity( );                   /* �ϊ��s���P�ʍs��ŏ����� */
  glOrtho( X0, X1, Y0, Y1, -1.0, 1.0 );  /* ���ˉe�ϊ��͈̔͐ݒ�(X0<x<X1, Y0<y<Y1) */
  glViewport( 20, 20, W_WIDTH - 40, W_HEIGHT - 40 ); /* ���K���f�o�C�X���W�n���E�B���h�E���W�n�ւ̓��e�ݒ�(������ʕ\��) */

  display_xy_axis( X0, X1, Y0, Y1 );         /* xy���Ɩڐ�����`��  */
  drawString2D( X1/2, -0.18, "time" );       /* x����time�ƃ��x����`�� */
  drawString2D( -3.5, -0.1, "0" );           /* ���_(0,0)��0�ƕ`�� */
  drawString2D( -10.0, 0.5, "x[i]/N" );      /* y���Ƀ��x����`�� */
  drawString2D( -3.5, 0.98, "1" );           /* y���̖ڐ���1�ƕ`�� */
  drawString2D( 18, -0.1, "20" );           /* x���̖ڐ���20�ƕ`�� */
  drawString2D( 38, -0.1, "40" );           /* x���̖ڐ���40�ƕ`�� */
  drawString2D( 58, -0.1, "60" );           /* x���̖ڐ���60�ƕ`�� */
  drawString2D( 78, -0.1, "80" );           /* x���̖ڐ���80�ƕ`�� */

  /* �ϐ�x0(��������)�̐l���䗦�̎��ԕω�����Ńv���b�g */
  glColor3f( 0.0, 0.0, 1.0 );    /* ���̐F��ɐݒ� */
  glLineWidth( 2 );              /* ���̑�����2�s�N�Z���ɐݒ� */
  drawString2D( 2.0, 1.1, "Susceptible x[0]" );   /* ��(��������)�̐��� */

  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( gt[n], gx0[n] );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  /* �ϐ�x1(������)�̐l���䗦�̎��ԕω���Ԑ��Ńv���b�g */
  glColor3f( 1.0, 0.0, 0.0 );    /* ���̐F��Ԃɐݒ� */
  glLineWidth( 2 );              /* ���̑�����2�s�N�Z���ɐݒ� */
  drawString2D( 5.0+X1/3, 1.1, "Infectious x[1]" );  /* �Ԑ�(������)�̐��� */

  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( gt[n], gx1[n] );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  /* �ϐ�x3(�񕜎�)�̐l���䗦�̎��ԕω���ΐ��Ńv���b�g */
  glColor3f( 0.0, 0.6, 0.0 );    /* ���̐F���Â��΂ɐݒ� */
  glLineWidth( 2 );              /* ���̑�����2�s�N�Z���ɐݒ� */
  drawString2D( 5.0+2*X1/3, 1.1, "Recovered x[2]" );  /* �ΐ�(�񕜎�)�̐��� */

  glBegin( GL_LINE_STRIP );   /* �}�`�`��^�C�v�̐ݒ�J�n: �܂���ŕ`�� */

    for( n = 0; n < n_time; n++ ) {
      glVertex2d( gt[n], gx2[n] );   /* ���l���𒸓_���W�Ƃ��Đݒ� */
    }

  glEnd( );  /* �}�`�`��^�C�v�̐ݒ�I�� */

  glFlush( );          /* �R�}���h�o�b�t�@�ɂ��܂��Ă��関���s�̖��߂����s */
}

int main( int argc, char *argv[] )
{
  int i, n;
  double t, dt, t0, t_end;
  double x[N];  /* �ϐ�(�e�l��) */
  double k1[N], k2[N], k3[N], k4[N], xwork[N];  /* �����Q�E�N�b�^�@�̂��߂̕ϐ� */
  double n_tot;  /* ���l�� */
  ModelParameter param;  /* SIR���f���̃p�����[�^�Ɋւ���\���̕ϐ��̐錾 */

  param.beta = 0.005;   /* ������(SIR���f���̃p�����[�^) */
  param.gamma = 0.2;    /* �񕜗�(SIR���f���̃p�����[�^) */

  x[0] = 1000.0;  /* �Ɖu�̂Ȃ��������Ґ��̏����l */
  x[1] = 1.0;     /* �����Ґ��̏����l */
  x[2] = 0.0;     /* �Ɖu�̂���񕜎Ґ��̏����l */
  n_tot = x[0] + x[1] + x[2];  /* ���l��(���l) */

  dt = 1.0e-3;  /* ���Ԃ̂����ݕ��̐ݒ�*/
  t0 = 0.0;     /* �V�~�����[�V�����̏��������̐ݒ� */
  t_end = X1;   /* �V�~�����[�V�����̏I�������̐ݒ� */

  printf( "beta = %f\n", param.beta );
  printf( "gamma = %f (1/gamma = %f)\n", param.gamma, 1.0/param.gamma );
  for( i = 0; i < N; i++ ) {
    printf( "�����l x[%d] = %.1f\n", i, x[i] );

  }

  /* �����Q�E�N�b�^�@�ɂ��1�K������������̐��l��@ */
  n = 0;          /* �J�E���^�[ */
  n_time = 0;     /* �O���t�Ƀv���b�g����f�[�^����0�ɏ����� */
  for( t = t0; t <= t_end; t += dt ) {

    if( n % 200 == 0 ) {  /* 200���1��O���t�Ƀv���b�g */
      gt[n_time] = t;      /* �O���t�Ƀv���b�g���鎞��t�̒l��z��gt�ɕۑ� */
      gx0[n_time] = x[0] / n_tot;  /* �O���t�Ƀv���b�g����x[0]/n_tot�̒l��z��gx0�ɕۑ� */
      gx1[n_time] = x[1] / n_tot;  /* �O���t�Ƀv���b�g����x[1]/n_tot�̒l��z��gx1�ɕۑ� */
      gx2[n_time] = x[2] / n_tot;  /* �O���t�Ƀv���b�g����x[2]/n_tot�̒l��z��gx2�ɕۑ� */
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

