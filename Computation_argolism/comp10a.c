/* ��`�����ɂ�鐔�l�ϕ��̌v�Z���x */
#include <stdio.h>
#include <math.h>

/* ��ϕ��֐�f(x)�̒�` */
double f( double x )
{
  double r;

  r = exp(x); /* ��ϕ��֐�f(x)�̎� */

  return r;
}


int main ( void )
{
  int n, N;
  double s, dx, x, a, b, error, s_exact;

  a = 0.0;  /* �ϕ��͈�[a,b]�̎n�_�̐ݒ� */
  b = 1.0;  /* �ϕ��͈�[a,b]�̏I�_�̐ݒ� */
  N = 100;  /* �ϕ���Ԃ̕������̐ݒ� */

  dx = ( b - a ) / (double) N;  /* �ϕ���Ԃ̂����ݕ� */

  printf( "�ϕ���ԁF [a,b] = [%f, %f]\n", a, b );
  printf( "�������F N = %d\n", N );
  printf( "�����ݕ��F dx = %e  log10(dx) = %f\n", dx, log10( dx ) );

  /* ��`�����ɂ�鐔�l�ϕ�(�z�z�����̎�(7.5)) */
  s = ( f( a ) + f ( b ) ) / 2.0;  /* �ϕ���Ԃ̗��[�ł̒l��s�ɑ�� */
  for( n = 1; n < N; n++ ) {       /* n=1�`N-1�Ԗڂ̔�����ԂɊւ��� */
    x = a + n * dx;     /* n�Ԗڂ̔�����Ԃ�x�̒l */
    s += f( x );        /* �e������Ԃł̊֐�f(x)�̒l��s�ɉ��Z */
  }
  s *= dx;       /* �֐�f(x)�̊e�_�ł̘a�ɔ�����Ԃ̕�dx���|���� */

  s_exact = M_E - 1.0; /* ��ϕ��̐��m�Ȓl */
  printf( "�ϕ��l�F ��`���� = %.15e\n         ���m�Ȓl = %.15e\n", s, s_exact );
  error = fabs( s - s_exact );  /* �v�Z�덷 */
  printf( "�v�Z�덷�F ��S = %e  log10(��S) = %f\n", error, log10( error ) );

  return 0;
}

