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

/*���C���֐�***********************************************************/
void main(void)
{
	//��������̐ݒ�[�P�ʁFHz�@�͈́F30.0~]
	const BYTE MainCycle = 60;
	
	Init((BYTE)MainCycle);		//CPU�̏����ݒ�
	//I2C_init(void);	//IXBUS������
	
	//���[�v
	while(1){
		//�O�i
		Mtr_Run_lv(-20000,20000,0,0,0,0);
		LED(1);		//�I�����W��LED�_��
		Wait(1000);
		//��~
		Mtr_Run_lv(0,0,0,0,0,0);
		LED(0);		//����
		Wait(1000);
		//��i		
		Mtr_Run_lv(20000,-20000,0,0,0,0);
		LED(2);		//�΂�LED�_��
		Wait(1000);
		//��~
		Mtr_Run_lv(0,0,0,0,0,0);
		LED(0);		//����
		Wait(1000);
	}
}


#ifdef __cplusplus
void abort(void)
{
	
}
#endif
