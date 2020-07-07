/* �I�C���[�@�ɂ��1�K������������̐��l��@�̌v�Z���x */
#include <stdio.h>
#include <math.h>

/* ����������f(t, x)�̒�` */
double f( double a, double c, double t, double x )
{
  double r;

  r = a * ( c - x ) * x;

  return r;
}

/* �����������̌������̒�` */
double f_exact( double a, double c, double t, double x0 )
{
  double r;

  r = c*x0/(x0 +(c-x0)*exp(-a*c*t));

  return r;
}

int main ( void )
{
  double t, dt, x, x0, t0, t_end, dx;
  double a, c;

  a = 7.0;  /* �p�����[�^�̐ݒ� */
  c = 1.0;  /* �p�����[�^�̐ݒ� */
  x0 = 0.1;  /* �����l�̐ݒ� */

  printf( "�p�����[�^�F a = %f\n", a );
  printf( "�p�����[�^�F c = %f\n", c );
  printf( "�����l�F x0 = %f\n", x0 );

  /* �I�C���[�@�ɂ��1�K������������̐��l��@ */
  dt = 1.0e-10;  /* ���Ԃ̂����ݕ��̐ݒ�*/
  t0 = 0.0;     /* �V�~�����[�V�����̏��������̐ݒ� */
  t_end = 1.0;  /* �V�~�����[�V�����̏I�������̐ݒ� */

  x = x0;  /* �����l�̐ݒ� */
  for( t = t0; t <= t_end; t += dt ) {  /* ����t�̒l��dt���݂�t0����t_end�܂ŕω� */
    x += f( a, c, t, x ) * dt;  /* �I�C���[�@ */
  }

  dx = fabs( f_exact( a, c, t, x0 ) - x );  /* �v�Z�덷 */
  printf( "���Ԃ̂����ݕ��F dt = %e  log10(dt) = %f\n", dt, log10( dt ) );
  printf( "�v�Z�덷�F dx = %e  log10(dx) = %f\n", dx, log10( dx ) );

  return 0;
}

