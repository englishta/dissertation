#ifdef __cplusplus
extern "C" {
void abort(void);
#endif
void main(void);
#ifdef __cplusplus
}
#endif

/*�C���N���[�h***********************************************************/
#include<36064s.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "vs-wrc003lv.h"

/*�}�N��***********************************************************/

/*�O���[�o���ϐ�***********************************************************/
int cnt = 0;
int black_cnt=0;
int judge = 0;
/*���C���֐�***********************************************************/
void main(void)
{
	//��������̐ݒ�[�P�ʁFHz�@�͈́F30.0~]
	const BYTE MainCycle = 60;
	
	Init((BYTE)MainCycle);		//CPU�̏����ݒ�
	//I2C_init(void);	//IXBUS������
	
	//���[�v
	
	while(1){
		const int border = 90;
		int right = AdRead(0);
		int left = AdRead(1);
		
		if(right > border){
			Mtr_Run_lv(10000, -10000,0,0,0,0);
			Wait(100);
			LED(1);
		}
		else if(left > border){
			Mtr_Run_lv(-10000, 10000,0,0,0,0);
			Wait(100);
			LED(2);
		}else{
			LED(3);
			Mtr_Run_lv(0, 0,0,0,0,0);
			Wait(100);
			Mtr_Run_lv(-10000, -10000,0,0,0,0);
			Wait(100);
		}
			
	}

}
#ifdef __cplusplus
void abort(void)
{
	
}
#endif