/* �V���v�\�������ɂ�鐔�l�ϕ��̌v�Z���x */
#include <stdio.h>
#include <math.h>

/* ��ϕ��֐�f(x)�̒�` */
double f( double x )
{
  double r;

  r = exp( x ); /* ��ϕ��֐�f(x)�̎� */

  return r;
}

int main ( void )
{
  int k, N;
  double s, s_odd, s_even, x, dx, a, b, error, s_exact;

  a = 0.0;  /* �ϕ��͈�[a,b]�̎n�_�̐ݒ� */
  b = 1.0;  /* �ϕ��͈�[a,b]�̏I�_�̐ݒ� */
  N = 100;  /* �ϕ���Ԃ̕�����(����)�̐ݒ� */

  dx = ( b - a ) / (double) N;  /* �ϕ���Ԃ̂����ݕ� */

  printf( "�ϕ���ԁF [a,b] = [%f, %f]\n", a, b );
  printf( "�������F N = %d\n", N );
  printf( "�����ݕ��F dx = %e  log10(dx) = %f\n", dx, log10( dx ) );

  /* ��Ԗڂ̕��_�̒l�̘a�̌v�Z */
  s_odd = 0.0;  /* ��Ԗڂ̕��_�̒l�̘a�̏����l */
  for( k = 0; k <=  N/2-1; k++ ) {
    x = a + ( 2 * k + 1 ) * dx;  /* ��Ԗڂ̕��_ */
    s_odd += f( x );             /* ��Ԗڂ̕��_�̒l�̘a */
  }

  /* �[�_�����������Ԗڂ̕��_�̒l�̘a�̌v�Z */
  s_even = 0.0;  /* �[�_�����������Ԗڂ̕��_�̒l�̘a�̏����l */
  for( k = 1; k <= N/2-1 ; k++ ) {
    x = a + 2 * k * dx;     /* �����Ԗڂ̕��_ */
    s_even += f( x );       /* �[�_�����������Ԗڂ̕��_�̒l�̘a */
  }

  /* �V���v�\�������ɂ�鐔�l�ϕ� */
  s = ( f( a ) + f( b ) + 4.0 * s_odd + 2.0 * s_even ) * dx / 3.0;

  s_exact = M_E - 1.0; /* ��ϕ��̐��m�Ȓl */
  printf( "�ϕ��l�F �V���v�\\������ = %.15e\n               ���m�Ȓl = %.15e\n", s, s_exact );
  error = fabs( s - s_exact );  /* �v�Z�덷 */
  printf( "�v�Z�덷�F ��S = %e  log10(��S) = %f\n", error, log10( error ) );

  return 0;
}

